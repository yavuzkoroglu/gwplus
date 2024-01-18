#ifndef GWMODEL_H
    #define GWMODEL_H
    #include "padkit/chunk.h"
    #include "padkit/chunktable.h"

    #define GWM_CHUNK_INFO_MAX_STRINGS  6
    #define GWM_INITIAL_STR_LEN         64

    #define GWM_RECOMMENDED_INITIAL_VERTEX_CAP  256
    #define GWM_RECOMMENDED_INITIAL_EDGE_CAP    8192
    #define GWM_RECOMMENDED_INITIAL_T_CAP       32

    #define GWM_RECOMMENDED_PARAMETERS      \
        GWM_RECOMMENDED_INITIAL_VERTEX_CAP, \
        GWM_RECOMMENDED_INITIAL_EDGE_CAP,   \
        GWM_RECOMMENDED_INITIAL_T_CAP

    #define GWM_CHUNK_INFO          0
    #define GWM_CHUNK_VERTEX_IDS    1
    #define GWM_CHUNK_VERTEX_NAMES  2
    #define GWM_CHUNK_EDGE_IDS      3
    #define GWM_CHUNK_EDGE_NAMES    4
    #define GWM_CHUNK_LAST          GWM_CHUNK_EDGE_NAMES
    #define GWM_TBL_VERTICES        0
    #define GWM_TBL_EDGES           1
    #define GWM_TBL_LAST            GWM_TBL_EDGES
    typedef struct GWModelBody {
        Chunk chunks[GWM_CHUNK_LAST + 1];
        ChunkTable tables[GWM_TBL_LAST + 1];
        uint32_t** transitions;
        uint32_t* size_outEdges;
        uint32_t* cap_outEdges;
        uint32_t size_vertices;
        uint32_t cap_vertices;
        uint32_t* t_ids;
        uint32_t sz_t;
        uint32_t cap_t;
    } GWModel;

    void addTransition_gwm(GWModel* const gwm, uint32_t const source, uint32_t const sink);

    void addVertex_gwm(
        GWModel* const gwm,
        char const* const v_id, uint64_t const v_id_len,
        char const* const v_name, uint64_t const v_name_len
    );

    void constructEmpty_gwm(
        GWModel* const gwm,
        uint32_t const initial_cap_vertices,
        uint32_t const initial_cap_edges,
        uint32_t const initial_cap_t
    );

    void free_gwm(GWModel* const gwm);

    uint32_t get_s_id_gwm(GWModel const* const gwm);

    bool isValid_gwm(GWModel const* const gwm);

    typedef struct GWModelArrayBody {
        size_t cap;
        size_t size;
        GWModel* array;
    } GWModelArray;

    void constructFromJSON_gwma(GWModelArray* const gwma, size_t const initial_cap, FILE* const jsonFile);

    void free_gwma(GWModelArray* const gwma);

    bool isValid_gwma(GWModelArray const* const gwma);
#endif
