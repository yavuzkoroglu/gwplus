/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Yavuz Koroglu
 */
#include "algorithm.h"
#include "coverage.h"
#include "padkit/debug.h"
#include "padkit/streq.h"

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
        "Usage: gwplus <coverage-criterion> <algorithm> <GraphWalker-JSON-file>\n"
        "\n"
        "  <algorithm>: (naive|random|approx|minflow)\n"
        "   "ALGO_NAIVE_STR" => "ALGO_NAIVE_DESC"\n"
        "   "ALGO_RANDOM_STR" => "ALGO_RANDOM_DESC"\n"
        "   "ALGO_APPROX_STR" => "ALGO_APPROX_DESC"\n"
        "   "ALGO_MINFLOW_STR" => "ALGO_MINFLOW_DESC"\n"
        "\n"
        "  <coverage-criterion>: ("COV_NC_STR"|"COV_EC_STR"|"COV_EPC_STR"|"COV_PPC_STR")\n"
        "   "COV_NC_STR" => "COV_NC_DESC"\n"
        "   "COV_EC_STR" => "COV_EC_DESC"\n"
        "   "COV_EPC_STR" => "COV_EPC_DESC"\n"
        "   "COV_PPC_STR" => "COV_PPC_DESC"\n"
        "\n",
        stderr
    );
}

int main(int argc, char* argv[]) {
    static char const* const cov_strs[COV_LAST + 1]     = COV_STRINGS;
    static char const* const algo_strs[ALGO_LAST + 1]   = ALGO_STRINGS;

    if (argc < 4) {
        showUsage();
        return EXIT_SUCCESS;
    }

    char const* const cov_str   = argv[1];
    char const* const algo_str  = argv[2];
    char const* const filename  = argv[3];

    int cov_id = COV_LAST;
    while (!STR_EQ_CONST(cov_str, cov_strs[cov_id])) {
        cov_id--;
        if (cov_id < 0) {
            showUnknownCoverage(cov_str);
            showUsage();
            return EXIT_FAILURE;
        }
    }

    int algo_id = ALGO_LAST;
    while (!STR_EQ_CONST(algo_str, algo_strs[algo_id])) {
        algo_id--;
        if (algo_id < 0) {
            showUnknownAlgorithm(algo_str);
            showUsage();
            return EXIT_FAILURE;
        }
    }

    FILE* jsonFile = fopen(filename, "r");
    if (jsonFile == NULL) {
        showCannotOpenFile(filename);
        return EXIT_FAILURE;
    }

    GWModelArray models[1];
    constructFromJSON_gwma(models, GWM_ARRAY_RECOMMENDED_INITIAL_CAP, jsonFile);

    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))

    GWModel* const first_model  = models->array;
    GWModel* const last_model   = first_model + models->size - 1;
    for (GWModel* model = first_model; model <= last_model; model++) {
        DEBUG_ASSERT(isValid_gwm(model))

        TestRequirements requirements[1];
        construct_tr(requirements, model, cov_id);

        dump_tr(requirements);

        PathArray* const testPaths = generateTestsFrom(requirements, algo_id);
        DEBUG_ASSERT(isValid_patha(testPaths))

        puts("TEST_PATHS = ");
        dump_patha(testPaths, model->chunks + GWM_CHUNK_VERTEX_NAMES);

        free_patha(testPaths);
        free(testPaths);
        free_tr(requirements);
    }

    free_gwma(models);

    return EXIT_SUCCESS;
}
