/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "algorithm.h"
#include "coverage.h"
#include "globals.h"
#include "padkit/debug.h"
#include "padkit/streq.h"
#include "padkit/timestamp.h"
#include "testrequirements.h"

static char*            extended_fname  = NULL;
static GWModelArray     models[1]       = {NOT_A_GWMODEL_ARRAY};
static TestRequirements requirements[1] = {NOT_TEST_REQUIREMENTS};
static PathArray        testPaths[1]    = {NOT_A_PATH_ARRAY};

PathArray               pathStack[2];
Path                    path_at_hand[2];

static void free_extended_fname(void) {
    DEBUG_ABORT_IF(extended_fname == NULL)
    free(extended_fname);
}

static void free_models(void) {
    DEBUG_ABORT_UNLESS(isValid_gwma(models))
    free_gwma(models);
}

static void free_pathStacks(void) {
    DEBUG_ABORT_UNLESS(isValid_patha(pathStack))
    free_patha(pathStack);

    DEBUG_ABORT_UNLESS(isValid_patha(pathStack + 1))
    free_patha(pathStack + 1);
}

static void free_paths(void) {
    DEBUG_ABORT_UNLESS(isValid_path(path_at_hand))
    free_path(path_at_hand);

    DEBUG_ABORT_UNLESS(isValid_path(path_at_hand + 1))
    free_path(path_at_hand + 1);
}

static void free_requirements(void) {
    DEBUG_ABORT_UNLESS(isValid_tr(requirements))
    free_tr(requirements);
}

static void free_testPaths(void) {
    DEBUG_ABORT_UNLESS(isValid_patha(testPaths))
    free_patha(testPaths);
}

static int countDigits(size_t number) {
    int nDigits = 0;
    do { number /= 10; nDigits++; } while (number > 0);
    return nDigits;
}

static void showCannotOpenFile(char const* const filename) {
    fprintf(
        stderr,
        "\n"
        "ERROR: Cannot open JSON file => %s\n"
        "\n",
        filename
    );
}

static void showUnknownAlgorithm(char const* const algo_str) {
    fprintf(
        stderr,
        "\n"
        "ERROR: Unknown test path generation algorithm => %s\n"
        "\n",
        algo_str
    );
}

static void showUnknownCoverage(char const* const cov_str) {
    fprintf(
        stderr,
        "\n"
        "ERROR: Unknown coverage criterion => %s\n"
        "\n",
        cov_str
    );
}

static void showUsage(void) {
    fputs(
        "\n"
        "Usage: gwplus <algorithm> <coverage-criterion> <GraphWalker-JSON-file> <output-JSON-file> [-v]\n"
        "\n"
        "  <algorithm>: ("ALGO_NAIVE_STR"|"ALGO_RANDOM_STR"|"ALGO_APPROX_STR"|"ALGO_MINFLOW_STR"|"ALGO_CPOSTMAN_STR")\n"
        "   "ALGO_NAIVE_STR" => "ALGO_NAIVE_DESC"\n"
        "   "ALGO_RANDOM_STR" => "ALGO_RANDOM_DESC"\n"
        "   "ALGO_APPROX_STR" => "ALGO_APPROX_DESC"\n"
        "   "ALGO_MINFLOW_STR" => "ALGO_MINFLOW_DESC"\n"
        "   "ALGO_CPOSTMAN_STR" => "ALGO_CPOSTMAN_DESC"\n"
        "\n"
        "  <coverage-criterion>: ("COV_NC_STR"|"COV_EC_STR"|"COV_EPC_STR"|"COV_PPC_STR")\n"
        "   "COV_NC_STR" => "COV_NC_DESC"\n"
        "   "COV_EC_STR" => "COV_EC_DESC"\n"
        "   "COV_EPC_STR" => "COV_EPC_DESC"\n"
        "   "COV_PPC_STR" => "COV_PPC_DESC"\n"
        "\n"
        "  -v: Verbose (prints test requirements and verbose messages)\n"
        "\n"
        "  WARNING: If test requirements cannot be met in one test path, there will be multiple output files, e.g.:\n"
        "              001_output.json, 002_output.json, etc.\n"
        "\n",
        stderr
    );
}

static void dump_path(Path const* const path) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ASSERT(isValid_gwma(models))

    Chunk const* const vertex_names = models->chunks + GWMA_CHUNK_VERTEX_NAMES;
    Chunk const* const edge_names   = models->chunks + GWMA_CHUNK_EDGE_NAMES;

    GWEdge const* prev_edge = NULL;
    for (uint32_t i = 0; i < path->len; i++) {
        uint32_t const e_id = path->array[i];
        DEBUG_ASSERT(e_id < models->size_edges)

        GWEdge const* const edge = models->edges + e_id;
        DEBUG_ASSERT(isValid_gwedge(edge))

        if (!isValid_gwedge(prev_edge) || prev_edge->target != edge->source) {
            char const* const v_name = get_chunk(vertex_names, edge->source);
            DEBUG_ERROR_IF(v_name == NULL)

            printf("{\"currentElementName\":\"%s\"}\n", v_name);
        }

        char const* const e_name = get_chunk(edge_names, e_id);
        DEBUG_ERROR_IF(e_name == NULL)

        printf("{\"currentElementName\":\"%s\"}\n", e_name);

        char const* const v_name = get_chunk(vertex_names, edge->target);
        DEBUG_ERROR_IF(v_name == NULL)

        printf("{\"currentElementName\":\"%s\"}\n", v_name);

        prev_edge = edge;
    }

    printf("\nPATH LENGTH = %"PRIu32" edges\n\n", path->len);
}

static void dump_patha(PathArray const* const paths) {
    DEBUG_ASSERT(isValid_patha(paths))
    DEBUG_ASSERT(isValid_gwma(models))

    if (paths->size == 0) return;

    puts("#####################");
    uint64_t total_edges = 0;
    for (uint32_t p_id = 0; p_id < paths->size; p_id++) {
        Path const* const path = paths->array + p_id;
        DEBUG_ASSERT(isValid_path(path))

        total_edges += path->len;

        dump_path(path);
        puts("#####################");
    }

    printf("\nTOTAL LENGTH = %"PRIu64" edges\n\n", total_edges);
}

#define ARGV_ALGO_STR   1
#define ARGV_COV_STR    2
#define ARGV_IFILENAME  3
#define ARGV_OFILENAME  4
#define ARGV_VERBOSE    5
#define VERBOSE_MSG(...) if (verbose) { printf("[%s] - ", get_timestamp()); printf(__VA_ARGS__); puts(""); }
int main(int argc, char* argv[]) {
    char const* const cov_strs[COV_LAST + 1]    = COV_STRINGS;
    char const* const algo_strs[ALGO_LAST + 1]  = ALGO_STRINGS;
    bool const verbose                          = (argc > 5 && STR_EQ_CONST(argv[ARGV_VERBOSE], "-v"));

    VERBOSE_MSG("Verbose enabled.")

    if (argc < 5) {
        showUsage();
        return EXIT_SUCCESS;
    }

    /* Determine algorithm */
    int algo_id = ALGO_LAST;
    while (!STR_EQ_CONST(argv[ARGV_ALGO_STR], algo_strs[algo_id])) {
        if (--algo_id >= 0) continue;

        showUnknownAlgorithm(argv[ARGV_ALGO_STR]);
        showUsage();
        return EXIT_FAILURE;
    }
    VERBOSE_MSG("Algorithm = %s", algo_strs[algo_id])

    /* Determine coverage criterion */
    int cov_id = COV_LAST;
    while (!STR_EQ_CONST(argv[ARGV_COV_STR], cov_strs[cov_id])) {
        if (--cov_id >= 0) continue;

        showUnknownCoverage(argv[ARGV_COV_STR]);
        showUsage();
        return EXIT_FAILURE;
    }
    VERBOSE_MSG("Coverage Criterion = %s", cov_strs[cov_id])

    /* Open <GraphWalker-JSON-file> to read */
    VERBOSE_MSG("Loading %s...", argv[ARGV_IFILENAME])
    FILE* jsonFile = fopen(argv[ARGV_IFILENAME], "r");
    if (jsonFile == NULL) {
        showCannotOpenFile(argv[ARGV_IFILENAME]);
        return EXIT_FAILURE;
    }

    /* Load GraphWalker models (models is a static variable) */
    constructEmpty_gwma(models, GWMA_DEFAULT_PARAMETERS);
    DEBUG_ASSERT(atexit(free_models) == 0)
    NDEBUG_EXECUTE(atexit(free_models))
    fillUsingJSON_gwma(models, jsonFile);

    uint32_t const count_unique_vertices = countUniqueVertices_gwma(models);
    uint32_t const count_unique_edges    = countUniqueEdges_gwma(models);

    VERBOSE_MSG("       # Vertices = %"PRIu32"", models->size_vertices)
    VERBOSE_MSG("# Unique Vertices = %"PRIu32"", count_unique_vertices)
    VERBOSE_MSG("          # Edges = %"PRIu32"", models->size_edges)
    VERBOSE_MSG("   # Unique Edges = %"PRIu32"", count_unique_edges)

    /* Close <GraphWalker-JSON-file> */
    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))
    VERBOSE_MSG("%s Loaded", argv[ARGV_IFILENAME])

    /* Initialize two path stacks for test generation */
    constructEmpty_patha(pathStack, count_unique_edges);
    constructEmpty_patha(pathStack + 1, count_unique_edges);
    DEBUG_ASSERT(atexit(free_pathStacks) == 0)
    NDEBUG_EXECUTE(atexit(free_pathStacks))

    /* Initialize some paths for test generation */
    constructEmpty_path(path_at_hand, count_unique_edges, PATH_DEFAULT_FLAGS);
    constructEmpty_path(path_at_hand + 1, count_unique_edges, PATH_DEFAULT_FLAGS);
    DEBUG_ASSERT(atexit(free_paths) == 0)
    NDEBUG_EXECUTE(atexit(free_paths))

    /* Generate test requirements (requirements is a static variable) */
    VERBOSE_MSG("Generating test requirements...")
    construct_tr(requirements, models, cov_id);
    DEBUG_ASSERT(atexit(free_requirements) == 0)
    NDEBUG_EXECUTE(atexit(free_requirements))
    if (verbose) {
        puts("\nTEST REQUIREMENTS = \n");
        dump_patha(requirements->paths);
    }

    /* Generate test paths */
    VERBOSE_MSG("Generating test paths...")
    constructEmpty_patha(testPaths, requirements->paths->size);
    DEBUG_ASSERT(atexit(free_testPaths) == 0)
    NDEBUG_EXECUTE(atexit(free_testPaths))
    generateTests(testPaths, requirements, algo_id);

    if (testPaths->size == 0) {
        fputs("\nERROR: Could NOT generate any test paths!\n\n", stderr);
        return EXIT_FAILURE;
    } else if (testPaths->size == 1) {
        Path const* const testPath = testPaths->array;
        DEBUG_ASSERT(isValid_path(testPath))

        jsonFile = fopen(argv[ARGV_OFILENAME], "w");
        if (jsonFile == NULL) {
            showCannotOpenFile(argv[ARGV_OFILENAME]);
            return EXIT_FAILURE;
        }

        if (verbose) {
            puts("\nTestPath =");
            dump_path(testPath);
        }
        writeJSON_gwma(models, jsonFile, testPath->array, testPath->len);

        DEBUG_ASSERT(fclose(jsonFile) == 0)
        NDEBUG_EXECUTE(fclose(jsonFile))

        return EXIT_SUCCESS;
    } else {
        fputs("\nWARNING: One test path is not enough to meet test requirements.\n\n", stderr);

        size_t const ofilename_len = strlen(argv[ARGV_OFILENAME]);
        int const p_id_max_digit_count = countDigits(testPaths->size);
        extended_fname = calloc((size_t)p_id_max_digit_count + 1 + ofilename_len, sizeof(char));
        DEBUG_ERROR_IF(extended_fname == NULL)
        DEBUG_ASSERT(atexit(free_extended_fname) == 0)
        NDEBUG_EXECUTE(atexit(free_extended_fname))

        uint32_t p_id = 0;
        while (p_id < testPaths->size) {
            Path const* const testPath = testPaths->array + p_id++;
            DEBUG_ASSERT(isValid_path(testPath))

            int const filler_count = p_id_max_digit_count - countDigits(p_id);
            sprintf(extended_fname, "%0*u_%s", filler_count, p_id, argv[ARGV_OFILENAME]);

            jsonFile = fopen(extended_fname, "w");
            if (jsonFile == NULL) {
                showCannotOpenFile(extended_fname);
                return EXIT_FAILURE;
            }

            if (verbose) {
                printf("\nTestPath_%0*u =\n", filler_count, p_id);
                dump_path(testPath);
            }
            writeJSON_gwma(models, jsonFile, testPath->array, testPath->len);

            DEBUG_ASSERT(fclose(jsonFile) == 0)
            NDEBUG_EXECUTE(fclose(jsonFile))
        }

        VERBOSE_MSG("# Test Paths = %"PRIu32, testPaths->size)
        return EXIT_SUCCESS;
    }
}
#undef ARGV_COV_STR
#undef ARGV_ALGO_STR
#undef ARGV_IFILENAME
#undef ARGV_OFILENAME
#undef ARGV_VERBOSE
#undef VERBOSE_MSG
