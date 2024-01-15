#include "gwmodel.h"
#include "padkit/chunk.h"
#include "padkit/graphmatrix.h"
#include "padkit/jsonparser.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static GWModelArray* gwma   = NULL;
static GWModel* current_gwm = NULL;
static uint32_t current_cid = 0xFFFFFFFF;
static uint32_t source_cid  = 0xFFFFFFFF;
static uint32_t target_cid  = 0xFFFFFFFF;
static size_t   skip_level  = 0;

static void stopReading_gwma(JSONParser* const jp);                                                 /* end */
static void searchName_models(JSONParser* const jp);                                                /* s00 */
static void searchString_models(JSONParser* const jp, char const* const string, size_t const len);  /* s01 */
static void startReading_models(JSONParser* const jp);                                              /* s02 */
static void continueReading_model(JSONParser* const jp);                                            /* s03 shared */
static void startReading_model(JSONParser* const jp);                                               /* s03 shared */
static void searchName_model(JSONParser* const jp);                                                 /* s04 */
static void searchString_model(JSONParser* const jp, char const* const string, size_t const len);   /* s05 */
static void readModelInfo(JSONParser* const jp, char const* const string, size_t const len);        /* s06 */
static void startReading_edges(JSONParser* const jp);                                               /* s07 */
static void startReading_vertices(JSONParser* const jp);                                            /* s08 */
static void startReading_vertex(JSONParser* const jp);                                              /* s09 */
static void startReading_edge(JSONParser* const jp);                                                /* s10 */
static void searchName_vertex(JSONParser* const jp);                                                /* s11 */
static void searchName_edge(JSONParser* const jp);                                                  /* s12 */
static void searchString_vertex(JSONParser* const jp, char const* const string, size_t const len);  /* s13 */
static void searchString_edge(JSONParser* const jp, char const* const string, size_t const len);    /* s14 */
static void readVertexId(JSONParser* const jp, char const* const string, size_t const len);         /* s15 */
static void readVertexName(JSONParser* const jp, char const* const string, size_t const len);       /* s16 */
static void readEdgeId(JSONParser* const jp, char const* const string, size_t const len);           /* s17 */
static void readEdgeName(JSONParser* const jp, char const* const string, size_t const len);         /* s18 */
static void readEdgeSourceId(JSONParser* const jp, char const* const string, size_t const len);     /* s19 */
static void readEdgeTargetId(JSONParser* const jp, char const* const string, size_t const len);     /* s20 */
static void checkStack_models(JSONParser* const jp);                                                /* s21 */
static void checkStack_model(JSONParser* const jp);                                                 /* s22 */
static void checkStack_vertex(JSONParser* const jp);                                                /* s23 */
static void checkStack_edge(JSONParser* const jp);                                                  /* s24 */

static void checkStack_edge(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_edge;
    jp->atObjectEnd = startReading_edges;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void checkStack_model(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    DEBUG_MSG("skip_level = %zu, jp->stack_size = %zu\n", skip_level, jp->stack_size)
    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_model;
    jp->atObjectEnd = startReading_models;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void checkStack_models(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_models;
    jp->atObjectEnd = emptyVoidEvent_jsonp;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void checkStack_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_vertex;
    jp->atObjectEnd = startReading_vertices;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void continueReading_model(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atNameStart     = searchName_model;
    jp->atObjectEnd     = startReading_models;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
}
static void readEdgeId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_IDS].nStrings - 1)

    DEBUG_ERROR_IF(append_chunk(current_gwm->chunks + GWM_CHUNK_IDS, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(current_gwm->chunks + GWM_CHUNK_IDS, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeName(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_NAMES].nStrings - 1)

    DEBUG_ERROR_IF(append_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeSourceId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_IDS].nStrings - 1)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_NAMES].nStrings - 1)

    ChunkTableEntry* tblEntry = get_ctbl(current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS, string, len);
    if (tblEntry == NULL) {
        readVertexId(jp, string, len);
        tblEntry = get_ctbl(current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS, string, len);
        DEBUG_ERROR_IF(tblEntry == NULL)
    }

    source_cid = tblEntry->value;
    uint32_t const max_cid = source_cid > target_cid ? source_cid : target_cid;
    if (max_cid < current_gwm->chunks[GWM_CHUNK_IDS].nStrings) {
        uint32_t gmtx_new_width = GWM_INITIAL_ELEMENT_COUNT;
        while (gmtx_new_width < max_cid) {
            gmtx_new_width <<= 1;
            DEBUG_ERROR_IF(gmtx_new_width == 0)
        }
        DEBUG_ASSERT_NDEBUG_EXECUTE(resizeIfNecessary_gmtx(current_gwm->edgeMtx, gmtx_new_width, gmtx_new_width))
        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(current_gwm->edgeMtx, source_cid, target_cid))

        source_cid = 0xFFFFFFFF;
        target_cid = 0xFFFFFFFF;
    }

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeTargetId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_IDS].nStrings - 1)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_NAMES].nStrings - 1)

    ChunkTableEntry* tblEntry = get_ctbl(current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS, string, len);
    if (tblEntry == NULL) {
        readVertexId(jp, string, len);
        tblEntry = get_ctbl(current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS, string, len);
        DEBUG_ERROR_IF(tblEntry == NULL)
    }

    target_cid = tblEntry->value;
    uint32_t const max_cid = source_cid > target_cid ? source_cid : target_cid;
    if (max_cid < current_gwm->chunks[GWM_CHUNK_IDS].nStrings) {
        uint32_t gmtx_new_width = GWM_INITIAL_ELEMENT_COUNT;
        while (gmtx_new_width < max_cid) {
            gmtx_new_width <<= 1;
            DEBUG_ERROR_IF(gmtx_new_width == 0)
        }
        DEBUG_ASSERT_NDEBUG_EXECUTE(resizeIfNecessary_gmtx(current_gwm->edgeMtx, gmtx_new_width, gmtx_new_width))
        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(current_gwm->edgeMtx, source_cid, target_cid))

        source_cid = 0xFFFFFFFF;
        target_cid = 0xFFFFFFFF;
    }

    jp->atString = emptyStringEvent_jsonp;
}
static void readModelInfo(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, string, len) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void readVertexId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_IDS].nStrings - 1)

    DEBUG_ERROR_IF(append_chunk(current_gwm->chunks + GWM_CHUNK_IDS, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(current_gwm->chunks + GWM_CHUNK_IDS, string, len))

    DEBUG_ASSERT(
        insert_ctbl(
            current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS,
            current_cid, current_cid, CTBL_BEHAVIOR_UNIQUE
        ) == CTBL_INSERT_OK
    )
    NDEBUG_EXECUTE(
        insert_ctbl(
            current_gwm->idTable, current_gwm->chunks + GWM_CHUNK_IDS,
            current_cid, current_cid, CTBL_BEHAVIOR_UNIQUE
        )
    )

    jp->atString = emptyStringEvent_jsonp;
}
static void readVertexName(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ERROR_IF(current_gwm == NULL)
    DEBUG_ERROR_IF(current_cid == 0xFFFFFFFF)
    DEBUG_ASSERT(current_cid == current_gwm->chunks[GWM_CHUNK_NAMES].nStrings - 1)

    DEBUG_ERROR_IF(append_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void searchName_edge(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString    = searchString_edge;
}
static void searchName_model(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString    = searchString_model;
}
static void searchName_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString = searchString_vertex;
}
static void searchName_models(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString     = searchString_models;
}
static void searchString_edge(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "id")) {
        jp->atString = readEdgeId;
    } else if (STR_EQ_CONST(string, "name")) {
        jp->atString = readEdgeName;
    } else if (STR_EQ_CONST(string, "sourceVertexId")) {
        jp->atString = readEdgeSourceId;
    } else if (STR_EQ_CONST(string, "targetVertexId")) {
        jp->atString = readEdgeTargetId;
    } else {
        skip_level      = jp->stack_size;
        jp->atArrayEnd  = checkStack_edge;
        jp->atObjectEnd = checkStack_edge;
        jp->atString    = emptyStringEvent_jsonp;
        jp->atValueEnd  = checkStack_edge;
    }
}
static void searchString_model(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "id")) {
        DEBUG_ERROR_IF(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "id", 2) == 0xFFFFFFFF)
        NDEBUG_EXECUTE(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "id", 2))

        jp->atString = readModelInfo;
    } else if (STR_EQ_CONST(string, "name")) {
        DEBUG_ERROR_IF(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "name", 4) == 0xFFFFFFFF)
        NDEBUG_EXECUTE(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "name", 4))

        jp->atString = readModelInfo;
    } else if (STR_EQ_CONST(string, "startElementId")) {
        DEBUG_ERROR_IF(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "startElementId", 14) == 0xFFFFFFFF)
        NDEBUG_EXECUTE(add_chunk(current_gwm->chunks + GWM_CHUNK_INFO, "startElementId", 14))

        jp->atString = readModelInfo;
    } else if (STR_EQ_CONST(string, "edges")) {
        jp->atArrayStart    = startReading_edges;
        jp->atString        = emptyStringEvent_jsonp;
    } else if (STR_EQ_CONST(string, "vertices")) {
        jp->atArrayStart    = startReading_vertices;
        jp->atString        = emptyStringEvent_jsonp;
    } else {
        skip_level      = jp->stack_size;
        jp->atArrayEnd  = checkStack_model;
        jp->atObjectEnd = checkStack_model;
        jp->atString    = emptyStringEvent_jsonp;
        jp->atValueEnd  = checkStack_model;
    }
}
static void searchString_vertex(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "id")) {
        jp->atString = readVertexId;
    } else if (STR_EQ_CONST(string, "name")) {
        jp->atString = readVertexName;
    } else {
        skip_level      = jp->stack_size;
        jp->atArrayEnd  = checkStack_vertex;
        jp->atObjectEnd = checkStack_vertex;
        jp->atString    = emptyStringEvent_jsonp;
        jp->atValueEnd  = checkStack_vertex;
    }
}
static void searchString_models(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')\n", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    jp->atNameStart = emptyVoidEvent_jsonp;
    jp->atString    = emptyStringEvent_jsonp;
    if (STR_EQ_CONST(string, "models")) {
        jp->atArrayStart = startReading_models;
    } else {
        skip_level      = jp->stack_size;
        jp->atArrayEnd  = checkStack_models;
        jp->atObjectEnd = checkStack_models;
        jp->atValueEnd  = checkStack_models;
    }
}
static void startReading_edge(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ERROR_IF(current_gwm == NULL)

    jp->atNameStart     = searchName_edge;
    jp->atObjectEnd     = startReading_edges;
    jp->atObjectStart   = emptyVoidEvent_jsonp;

    current_cid         = add_chunk(current_gwm->chunks + GWM_CHUNK_IDS, "", 0);
    uint32_t name_id    = add_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, "", 0);
    DEBUG_ASSERT(current_cid == name_id)
}
static void startReading_edges(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = continueReading_model;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_edge;
}
static void startReading_model(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    REALLOC_IF_NECESSARY(GWModel, gwma->array, size_t, gwma->cap, gwma->size, {REALLOC_ERROR;})

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_gwm((current_gwm = gwma->array + gwma->size++)))

    jp->atNameStart     = searchName_model;
    jp->atObjectEnd     = startReading_models;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
}
static void startReading_models(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = stopReading_gwma;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_model;
    current_gwm         = NULL;
}
static void startReading_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ERROR_IF(current_gwm == NULL)

    jp->atNameStart     = searchName_vertex;
    jp->atObjectEnd     = startReading_vertices;
    jp->atObjectStart   = emptyVoidEvent_jsonp;

    current_gwm->nVertices++;
    current_cid         = add_chunk(current_gwm->chunks + GWM_CHUNK_IDS, "", 0);
    uint32_t name_id    = add_chunk(current_gwm->chunks + GWM_CHUNK_NAMES, "", 0);
    DEBUG_ASSERT(current_cid == name_id)
}
static void startReading_vertices(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = continueReading_model;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_vertex;
}
static void stopReading_gwma(JSONParser* const jp) {
    DEBUG_MSG("%s\n", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    for (GWModel* gwm = gwma->array + gwma->size - 1; gwm >= gwma->array; gwm--) {
        DEBUG_ERROR_IF(gwm == NULL)

        for (uint32_t chunk_id = 0; chunk_id < gwm->chunks[GWM_CHUNK_INFO].nStrings; chunk_id++) {
            char const* const str = get_chunk(gwm->chunks + GWM_CHUNK_INFO, chunk_id);
            DEBUG_ERROR_IF(str == NULL)

            if (STR_EQ_CONST(str, "startElementId")) {
                char const* const id_str = get_chunk(gwm->chunks + GWM_CHUNK_INFO, chunk_id + 1);
                DEBUG_ERROR_IF(id_str == NULL)

                uint64_t const id_str_len = strlen_chunk(gwm->chunks + GWM_CHUNK_INFO, chunk_id + 1);
                ChunkTableEntry* tblEntry = get_ctbl(gwm->idTable, gwm->chunks + GWM_CHUNK_IDS, id_str, id_str_len);
                if (tblEntry == NULL) {
                    fprintf(stderr, "Invalid Start Vertex => %s\n", id_str);
                    exit(EXIT_FAILURE);
                }
                gwm->start_vertex_cid = tblEntry->value;
            }
        }
    }

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

#ifndef NDEBUG
    bool constructEmpty_gwm(GWModel* const gwm) {
        if (gwm == NULL) return NULL;

        if (
            !constructEmpty_chunk(
                gwm->chunks + GWM_CHUNK_INFO,
                GWM_INITIAL_STR_LEN * GWM_CHUNK_INFO_MAX_STRINGS,
                GWM_CHUNK_INFO_MAX_STRINGS
            )
        ) return 0;

        if (
            !constructEmpty_chunk(
                gwm->chunks + GWM_CHUNK_IDS,
                GWM_INITIAL_STR_LEN * GWM_INITIAL_ELEMENT_COUNT,
                GWM_INITIAL_ELEMENT_COUNT
            )
        ) return 0;

        if (
            !constructEmpty_chunk(
                gwm->chunks + GWM_CHUNK_NAMES,
                GWM_INITIAL_STR_LEN * GWM_INITIAL_ELEMENT_COUNT,
                GWM_INITIAL_ELEMENT_COUNT
            )
        ) return 0;

        if (!constructEmpty_ctbl(gwm->idTable, GWM_INITIAL_ELEMENT_COUNT, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT))
            return 0;

        if (!construct_gmtx(gwm->edgeMtx, GWM_INITIAL_ELEMENT_COUNT, GWM_INITIAL_ELEMENT_COUNT))
            return 0;

        gwm->start_vertex_cid   = 0xFFFFFFFF;
        gwm->nVertices          = 0;
        return 1;
    }
#else
    void constructEmpty_gwm(GWModel* const gwm) {
        constructEmpty_chunk(
            gwm->chunks + GWM_CHUNK_INFO,
            GWM_INITIAL_STR_LEN * GWM_CHUNK_INFO_MAX_STRINGS,
            GWM_CHUNK_INFO_MAX_STRINGS
        );

        constructEmpty_chunk(
            gwm->chunks + GWM_CHUNK_IDS,
            GWM_INITIAL_STR_LEN * GWM_INITIAL_ELEMENT_COUNT,
            GWM_INITIAL_ELEMENT_COUNT
        );

        constructEmpty_chunk(
            gwm->chunks + GWM_CHUNK_NAMES,
            GWM_INITIAL_STR_LEN * GWM_INITIAL_ELEMENT_COUNT,
            GWM_INITIAL_ELEMENT_COUNT
        );

        constructEmpty_ctbl(gwm->idTable, GWM_INITIAL_ELEMENT_COUNT, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT);

        constructEmpty_gmtx(gwm->edgeMtx, GWM_INITIAL_ELEMENT_COUNT, GWM_INITIAL_ELEMENT_COUNT);

        gwm->start_vertex_cid   = 0xFFFFFFFF;
        gwm->nVertices          = 0;
    }
#endif

void free_gwm(GWModel* const gwm) {
    DEBUG_ABORT_IF(!isValid_gwm(gwm))

    for (int i = 0; i <= GWM_CHUNK_LAST; i++) {
        DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(free_chunk(gwm->chunks + i))
    }

    DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(free_ctbl(gwm->idTable))
    DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(free_gmtx(gwm->edgeMtx))
}

bool isValid_gwm(GWModel const* const gwm) {
    if (gwm == NULL) return 0;

    for (int i = 0; i <= GWM_CHUNK_LAST; i++) {
        if (!isValid_chunk(gwm->chunks + i)) return 0;
    }

    if (!isValid_ctbl(gwm->idTable)) return 0;
    if (!isValid_gmtx(gwm->edgeMtx)) return 0;

    if (gwm->start_vertex_cid >= gwm->idTable->nKeys) return 0;
    if (gwm->nVertices >= gwm->chunks[GWM_CHUNK_IDS].nStrings) return 0;

    return 1;
}

void constructFromJSON_gwma(GWModelArray* const gwModelArray, size_t const initial_cap, FILE* const jsonFile) {
    DEBUG_MSG("%s\n", __func__)

    JSONParser jp[1];

    gwma = gwModelArray;
    DEBUG_ERROR_IF(gwma == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(jsonFile == NULL)

    gwma->array = malloc(sizeof(GWModel) * initial_cap);
    DEBUG_ERROR_IF(gwma->array == NULL)

    gwma->cap   = initial_cap;
    gwma->size  = 0;

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        construct_jsonp(
            jp, jsonFile,
            emptyVoidEvent_jsonp,   /* atArrayEnd */
            emptyVoidEvent_jsonp,   /* atArrayStart */
            emptyVoidEvent_jsonp,   /* atFalse */
            emptyVoidEvent_jsonp,   /* atNameEnd */
            searchName_models,      /* atNameStart */
            emptyVoidEvent_jsonp,   /* atNull */
            emptyNumberEvent_jsonp, /* atNumber */
            emptyVoidEvent_jsonp,   /* atObjectEnd */
            emptyVoidEvent_jsonp,   /* atObjectStart */
            emptyVoidEvent_jsonp,   /* atRootEnd */
            emptyVoidEvent_jsonp,   /* atRootStart */
            emptyStringEvent_jsonp, /* atString */
            emptyVoidEvent_jsonp,   /* atTrue */
            emptyVoidEvent_jsonp,   /* atValueEnd */
            emptyVoidEvent_jsonp    /* atValueStart */
        )
    )

    current_gwm = NULL;
    current_cid = 0xFFFFFFFF;
    source_cid  = 0xFFFFFFFF;
    target_cid  = 0xFFFFFFFF;

    if (parseStream_jsonp(jp) != JSON_PARSER_OK) {
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!");
    }

    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))
}
