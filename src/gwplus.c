/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Yavuz Koroglu
 */
#include "path.h"
#include "padkit/debug.h"
#include "padkit/streq.h"

int main(int argc, char* argv[]) {
    GWModelArray gwma[1];
    PathArray primePaths[1];

    FILE* jsonFile = fopen(argv[1], "r");
    if (jsonFile == NULL) {
        fprintf(stderr, "Could NOT open %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    constructFromJSON_gwma(gwma, 1, jsonFile);
    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))

    GWModel const* const gwm = gwma->array;
    Chunk const* const chunk_vertex_names = gwm->chunks + GWM_CHUNK_VERTEX_NAMES;

    puts("");

    printf("sizeof(GWModelArray) = %zu bytes\n", sizeof(GWModelArray));
    printf("sizeof(GWModel) = %zu bytes\n", sizeof(GWModel));

    puts("");

    printf("# MODELS = %zu\n", gwma->size);
    printf("# Vertices = %u\n", gwm->size_vertices);
    printf("s = %u\n", get_s_id_gwm(gwm));
    printf("# t = %u\n", gwm->sz_t);

    puts("");

    constructEmpty_patha(primePaths, PATH_ARRAY_DEFAULT_INITIAL_CAP);
    primePathsFromGWModel_patha(primePaths, gwm);

    puts("PrimePaths = ");
    for (
        Path* primePath = primePaths->array;
        primePath < primePaths->array + primePaths->size;
        primePath++
    ) {
        DEBUG_ASSERT(isValid_path(primePath))

        printf("  [ ");
        uint32_t i = 0;
        while (i < primePath->len - 1) {
            uint32_t const v_id = primePath->array[i];
            DEBUG_ASSERT(v_id < gwm->size_vertices)

            char const* const name = get_chunk(chunk_vertex_names, v_id);
            DEBUG_ERROR_IF(name == NULL)

            printf("%s, ", name);
            i++;
        }
        if (i < primePath->len) {
            uint32_t const v_id = primePath->array[i];
            DEBUG_ASSERT(v_id < gwm->size_vertices)

            char const* const name = get_chunk(chunk_vertex_names, v_id);
            DEBUG_ERROR_IF(name == NULL)

            printf("%s ", name);
        }

        puts("]");
    }

    puts("");

    return EXIT_SUCCESS;
}
