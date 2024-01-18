#include "gwmodel.h"
#include "padkit/debug.h"

int main(int argc, char* argv[]) {
    GWModelArray gwma[1];
    FILE* jsonFile = fopen("examples/model001.json", "r");
    if (jsonFile == NULL) {
        fprintf(stderr, "Could NOT open examples/model001.json\n");
        return EXIT_FAILURE;
    }

    printf("sizeof(gwma) = %zu bytes\n", sizeof(gwma));

    constructFromJSON_gwma(gwma, 1, jsonFile);

    printf("# MODELS = %zu\n", gwma->size);
    printf("# Vertices = %u\n", gwma->array[0].size_vertices);
    printf("s = %u\n", get_s_id_gwm(gwma->array));
    printf("# t = %u\n", gwma->array[0].sz_t);

    fclose(jsonFile);

    return EXIT_SUCCESS;
}
