#include "gwmodel.h"
#include "padkit/debug.h"

int main(int argc, char* argv[]) {
    GWModel gwm[1];
    FILE* jsonFile = fopen("examples/model001.json", "r");
    if (jsonFile == NULL) {
        fprintf(stderr, "Could NOT open examples/model001.json\n");
        return EXIT_FAILURE;
    }

    printf("sizeof(gwm) = %zu bytes\n", sizeof(gwm));

    constructFromJSON_gwm(gwm, jsonFile);

    fclose(jsonFile);

    return EXIT_SUCCESS;
}
