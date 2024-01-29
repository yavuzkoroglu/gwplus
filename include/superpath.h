/**
 * @file superpath.h
 * @brief Defines Connection, ConnectionArray, SuperPath, SuperPathArray, TestRequirements and related functions.
 * @author Yavuz Koroglu
 */
#ifndef SUPERPATH_H
    #define SUPERPATH_H
    #include "gwmodel.h"
    #include "path.h"

    typedef struct ConnectionBody {
        uint32_t    sourcePath_id;
        uint32_t    sinkPath_id;
        uint32_t    overlap_start_id;
        Path        connection[1];
    } Connection;

    void free_con(Connection* const connection);

    bool isValid_con(Connection const* const connection);

    #define CON_ARRAY_RECOMMENDED_INITIAL_CAP 8

    #define NOT_A_CON_ARRAY  (ConnectionArray){ 0, 0, NULL }

    typedef struct ConnectionArrayBody {
        uint32_t    size;
        uint32_t    cap;
        Connection* array;
    } ConnectionArray;

    void constructEmpty_cona(ConnectionArray* const connections, uint32_t const initial_cap);

    void free_cona(ConnectionArray* const connections);

    bool isValid_cona(ConnectionArray const* const connections);

    typedef struct SuperPathBody {
        Path            pathOfPaths[1];
        ConnectionArray connections[1];
    } SuperPath;

    void free_sp(SuperPath* const superPath);

    bool isValid_sp(SuperPath const* const superPath);

    #define SP_ARRAY_RECOMMENDED_INITIAL_CAP 64

    #define NOT_A_SP_ARRAY  (SuperPathArray){ 0, 0, NULL }

    typedef struct SuperPathArrayBody {
        uint32_t    size;
        uint32_t    cap;
        SuperPath*  array;
    } SuperPathArray;

    void constructEmpty_spa(SuperPathArray* const superPaths, uint32_t const initial_cap);

    void free_spa(SuperPathArray* const superPaths);

    bool isValid_spa(SuperPathArray const* const superPaths);

    typedef struct TestRequirementsBody {
        GWModel const*  model;
        PathArray       paths[1];
        SuperPathArray  superPaths[1];
    } TestRequirements;

    void construct_tr(TestRequirements* const tr, GWModel const* const gwm, int const cov_criterion);

    void dump_tr(TestRequirements const* const tr);

    void free_tr(TestRequirements* const tr);

    bool isValid_tr(TestRequirements const* const tr);
#endif
