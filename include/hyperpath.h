/**
 * @file hyperpath.h
 * @brief Defines Connection, ConnectionArray, HyperPath, HyperPathArray, and related functions.
 * @author Yavuz Koroglu
 */
#ifndef HYPERPATH_H
    #define HYPERPATH_H
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

    #define NOT_A_CON_ARRAY  ((ConnectionArray){ 0, 0, NULL })

    typedef struct ConnectionArrayBody {
        uint32_t    size;
        uint32_t    cap;
        Connection* array;
    } ConnectionArray;

    void constructEmpty_cona(ConnectionArray* const connections, uint32_t const initial_cap);

    void free_cona(ConnectionArray* const connections);

    bool isValid_cona(ConnectionArray const* const connections);

    #define NOT_A_HYPER_PATH ((HyperPath){ {NOT_A_PATH}, {NOT_A_CON_ARRAY} })

    typedef struct HyperPathBody {
        Path            pathOfPaths[1];
        ConnectionArray connections[1];
    } HyperPath;

    void free_hp(HyperPath* const hyperPath);

    bool isValid_hp(HyperPath const* const hyperPath);

    #define HP_ARRAY_RECOMMENDED_INITIAL_CAP 64

    #define NOT_A_HP_ARRAY  ((HyperPathArray){ 0, 0, NULL })

    typedef struct HyperPathArrayBody {
        uint32_t    size;
        uint32_t    cap;
        HyperPath*  array;
    } HyperPathArray;

    void constructEmpty_hpa(HyperPathArray* const hyperPaths, uint32_t const initial_cap);

    void free_hpa(HyperPathArray* const hyperPaths);

    bool isValid_hpa(HyperPathArray const* const hyperPaths);
#endif
