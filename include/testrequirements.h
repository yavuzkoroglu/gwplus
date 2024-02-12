#ifndef TESTREQUIREMENTS_H
    #define TESTREQUIREMENTS_H
    #include "gwmodel.h"
    #include "hyperpath.h"

    #define NOT_TEST_REQUIREMENTS ((TestRequirements){NULL, {NOT_A_PATH_ARRAY}, {NOT_A_HP_ARRAY}})

    typedef struct TestRequirementsBody {
        GWModelArray const* models;
        PathArray           paths[1];
        HyperPathArray      hyperPaths[1];
    } TestRequirements;

    void construct_tr(TestRequirements* const tr, GWModelArray const* const models, int const cov_criterion);

    void free_tr(TestRequirements* const tr);

    bool isValid_tr(TestRequirements const* const tr);
#endif
