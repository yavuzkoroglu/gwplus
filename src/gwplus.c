/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Yavuz Koroglu
 */
#include "coverage.h"
#include "padkit/debug.h"
#include "padkit/streq.h"
#include "superpath.h"

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
        "ERROR: Unknown coverage criterion => %s\n"
        "\n",
        cov_str
    );
}

static void showUsage(void) {
    fputs(
        "\n"
        "Usage: gwplus <coverage-criterion> <GraphWalker-JSON-file>\n"
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
    static char const* const cov_strs[COV_LAST + 1] = COV_STRINGS;

    if (argc < 3) {
        showUsage();
        return EXIT_SUCCESS;
    }

    char const* const cov_str   = argv[1];
    char const* const filename  = argv[2];

    int cov_id = COV_LAST;
    while (!STR_EQ_CONST(cov_str, cov_strs[cov_id])) {
        cov_id--;
        if (cov_id < 0) {
            showUnknownCoverage(cov_str);
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

        free_tr(requirements);
    }

    free_gwma(models);

    return EXIT_SUCCESS;
}
