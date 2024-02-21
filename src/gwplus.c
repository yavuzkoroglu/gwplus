/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "gwmodel.h"
#include "hpathgraph.h"
#include "padkit/debug.h"
#include "padkit/streq.h"
#include "padkit/timestamp.h"

static void showCannotOpenFile(char const* const filename) {
    fprintf(
        stderr,
        "\n"
        "ERROR: Cannot open JSON file => %s\n"
        "\n",
        filename
    );
}

static void showUnknownCoverage(char const* const cov_str) {
    fprintf(
        stderr,
        "\n"
        "ERROR: Unknown coverage criterion => %s\n",
        cov_str
    );
}

static void showUsage(void) {
    fputs(
        "\n"
        "Usage: gwplus (prime|<k>) <GraphWalker-JSON-file> <output-JSON-file> [-v]\n"
        "\n"
        "  prime: Prime Path Coverage\n"
        "    <k>: A positive integer\n"
        "           k=1 => Edge Coverage\n"
        "           k=2 => Edge Pair Coverage\n"
        "           k=N => All Edge Paths Up To Length N\n"
        "\n"
        "     -v: Verbose (prints verbose messages)\n"
        "\n",
        stderr
    );
}

#define ARGV_COV_STR 1
#define ARGV_IFILENM 2
#define ARGV_OFILENM 3
#define ARGV_VERBOSE 4
#define VERBOSE_MSG(...) if (verbose) { printf("[%s] - ", get_timestamp()); printf(__VA_ARGS__); puts(""); }
int main(int argc, char* argv[]) {
    if (argc < 4) {
        showUsage();
        return EXIT_SUCCESS;
    }

    bool const verbose = (argc > 4 && STR_EQ_CONST(argv[ARGV_VERBOSE], "-v"));
    VERBOSE_MSG("Verbose enabled.")

    int32_t k;
    if (STR_EQ_CONST(argv[ARGV_COV_STR], "prime")) {
        k = 0;
        VERBOSE_MSG("Coverage Criterion = Prime Path Coverage")
    } else {
        if (sscanf(argv[ARGV_COV_STR], "%"PRId32, &k) != 1 || k < 1) {
            showUnknownCoverage(argv[ARGV_COV_STR]);
            showUsage();
            return EXIT_FAILURE;
        }

        VERBOSE_MSG("Coverage Criterion = All Edge Paths Up To Length %d", k)
    }

    GWModelArray gwma[1];
    constructEmpty_gwma(gwma, GWMA_DEFAULT_PARAMETERS);

    /* Open <GraphWalker-JSON-file> to read */
    VERBOSE_MSG("Loading %s...", argv[ARGV_IFILENM])
    FILE* const jsonFile = fopen(argv[ARGV_IFILENM], "r");
    if (jsonFile == NULL) {
        showCannotOpenFile(argv[ARGV_IFILENM]);
        return EXIT_FAILURE;
    }

    fillUsingJSON_gwma(gwma, jsonFile);

    /* Close <GraphWalker-JSON-file> */
    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))

    SimpleGraph graph[1];
    construct_sgi_gwma(graph, gwma);

    if (gwma->s_type == GWMA_START_ELEMENT_TYPE_EDGE) {
        VERBOSE_MSG("Starting Element is an EDGE")
    } else {
        VERBOSE_MSG("Starting Element is a VERTEX")
    }

    VERBOSE_MSG("         # Vertices = %"PRIu32, gwma->size_vertices)
    VERBOSE_MSG("            # Edges = %"PRIu32, graph->countVertices(gwma))
    VERBOSE_MSG("       # Edge Pairs = %"PRIu32, graph->countEdges(gwma))

    VertexPathArray requirements[1];
    if (k == 0) {
        constructAllPrimePaths_vpa(requirements, graph);
    } else {
        constructAllUpToKPaths_vpa(requirements, graph, (uint32_t)k);
        eliminateSubPaths_vpa(requirements);
    }
    VERBOSE_MSG("# Test Requirements = %"PRIu32, requirements->size)

    VertexPathGraph vpgraph[1];
    construct_vpg(vpgraph, graph, requirements);

    SimpleGraph pathGraph[1];
    construct_sgi_vpg(pathGraph, vpgraph);

    VERBOSE_MSG("   # Direct Splices = %"PRIu32, pathGraph->countEdges(vpgraph))

    HyperPathGraph hpgraph[1];
    constructAcyclic_hpg(hpgraph, pathGraph);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    VERBOSE_MSG("       # HyperPaths = %"PRIu32, hyperPathGraph->countVertices(hpgraph))
    if (hyperPathGraph->countVertices(hpgraph) > 2) {
        fputs(
            "\n"
            "ERROR: The GraphWalker model is NOT well-formed.\n"
            "\n",
            stderr
        );
        return EXIT_FAILURE;
    }

    VertexPathArray testPaths[1];
    constructTestPaths_hpg(testPaths, hpgraph);

    VERBOSE_MSG("        # TestPaths = %"PRIu32, testPaths->size)

    VertexPath const* const testPath = testPaths->array;
    DEBUG_ASSERT(isValid_vpath(testPath))

    VERBOSE_MSG(" LengthOf(TestPath) = %"PRIu32, testPath->len)

    /* Set the predefined edge path. */
    gwma->cap_predefinedEdgePath = 0;
    gwma->len_predefinedEdgePath = testPath->len;
    gwma->predefinedEdgePath     = testPath->array;

    /* Open <output-JSON-file> to dump */
    VERBOSE_MSG("Dumping the final model to %s...", argv[ARGV_OFILENM])
    FILE* const output = fopen(argv[ARGV_OFILENM], "w");
    if (output == NULL) {
        showCannotOpenFile(argv[ARGV_OFILENM]);
        return EXIT_FAILURE;
    }

    graph->dump(gwma, output);

    DEBUG_ASSERT(fclose(output) == 0)
    NDEBUG_EXECUTE(fclose(output))

    free_vpa(testPaths);
    free_hpg(hpgraph);
    free_vpg(vpgraph);
    free_vpa(requirements);
    free_gwma(gwma);

    VERBOSE_MSG("Finished")
}
#undef ARGV_COV_STR
#undef ARGV_IFILENM
#undef ARGV_OFILENM
#undef ARGV_VERBOSE
#undef VERBOSE_MSG
