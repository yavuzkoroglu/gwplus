#ifndef GWMODEL_H
    #define GWMODEL_H
    #include "padkit/chunk.h"
    #include "padkit/chunktable.h"
    #include "padkit/graphmatrix.h"

    #define GWM_CHUNK_INFO_MAX_STRINGS  6
    #define GWM_INITIAL_STR_LEN         64
    #define GWM_INITIAL_ELEMENT_COUNT   1024

    #define GWM_CHUNK_INFO  0
    #define GWM_CHUNK_IDS   1
    #define GWM_CHUNK_NAMES 2
    #define GWM_CHUNK_LAST  GWM_CHUNK_NAMES
    typedef struct GWModelBody {
        Chunk chunks[3];
        ChunkTable idTable[1];
        GraphMatrix edgeMtx[1];
        uint32_t start_vertex_cid;
        uint32_t nVertices;
    } GWModel;

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_gwm(GWModel* const gwm);

    void free_gwm(GWModel* const gwm);

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
