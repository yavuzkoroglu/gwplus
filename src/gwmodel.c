#include "gwmodel.h"
#include "padkit/chunk.h"
#include "padkit/graphmatrix.h"
#include "padkit/jsonparser.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static GWModelArray* current_gwma   = NULL;
static GWModel* current_gwm         = NULL;
static size_t skip_level            = 0;
static uint32_t source_id           = 0xFFFFFFFF;
static uint32_t target_id           = 0xFFFFFFFF;

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
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_edge;
    jp->atObjectEnd = startReading_edges;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void checkStack_model(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

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
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_models;
    jp->atObjectEnd = emptyVoidEvent_jsonp;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void checkStack_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)

    if (skip_level != jp->stack_size) return;

    jp->atArrayEnd  = emptyVoidEvent_jsonp;
    jp->atNameStart = searchName_vertex;
    jp->atObjectEnd = startReading_vertices;
    jp->atValueEnd  = emptyVoidEvent_jsonp;
}
static void continueReading_model(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atNameStart     = searchName_model;
    jp->atObjectEnd     = startReading_models;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
}
static void readEdgeId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_edge_ids = current_gwm->chunks + GWM_CHUNK_EDGE_IDS;
    ChunkTable* const tbl_edges = current_gwm->tables + GWM_TBL_EDGES;
    uint32_t const e_id         = chunk_edge_ids->nStrings - 1;

    DEBUG_ERROR_IF(append_chunk(chunk_edge_ids, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_ids, string, len))

    DEBUG_ASSERT(insert_ctbl(tbl_edges, chunk_edge_ids, e_id, e_id, CTBL_BEHAVIOR_UNIQUE) == CTBL_INSERT_OK)
    NDEBUG_EXECUTE(insert_ctbl(tbl_edges, chunk_edge_ids, e_id, e_id, CTBL_BEHAVIOR_UNIQUE))

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeName(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_edge_names = current_gwm->chunks + GWM_CHUNK_EDGE_NAMES;

    DEBUG_ERROR_IF(append_chunk(chunk_edge_names, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_names, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeSourceId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;

    if (source_id != 0xFFFFFFFF) { TERMINATE_ERROR_MSG("Two source ids in one edge!"); }
    if (target_id != 0xFFFFFFFF) { TERMINATE_ERROR_MSG("Target id appeared before the source id in one edge!"); }

    ChunkTableEntry* tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry == NULL) { TERMINATE_ERROR_MSG("Vertex ID='%s' appeared in an edge before it is defined!", string); }

    source_id = tblEntry->value;

    jp->atString = emptyStringEvent_jsonp;
}
static void readEdgeTargetId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;

    if (source_id == 0xFFFFFFFF) { TERMINATE_ERROR_MSG("Target id appeared before the source id in one edge!"); }
    if (target_id != 0xFFFFFFFF) { TERMINATE_ERROR_MSG("Two target ids in one edge!"); }

    ChunkTableEntry* tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry == NULL) { TERMINATE_ERROR_MSG("Vertex ID='%s' appeared in an edge before it is defined!", string); }

    target_id = tblEntry->value;

    addTransition_gwm(current_gwm, source_id, target_id);

    source_id = 0xFFFFFFFF;
    target_id = 0xFFFFFFFF;

    jp->atString = emptyStringEvent_jsonp;
}
static void readModelInfo(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_info = current_gwm->chunks + GWM_CHUNK_INFO;

    DEBUG_ERROR_IF(add_chunk(chunk_info, string, len) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_info, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void readVertexId(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;

    ChunkTableEntry* tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry != NULL) { TERMINATE_ERROR_MSG("Duplicate Vertex IDs!"); }

    uint32_t v_id = current_gwm->size_vertices - 1;

    DEBUG_ERROR_IF(append_chunk(chunk_vertex_ids, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_ids, string, len))

    DEBUG_ASSERT(insert_ctbl(tbl_vertices, chunk_vertex_ids, v_id, v_id, CTBL_BEHAVIOR_UNIQUE) == CTBL_INSERT_OK)
    NDEBUG_EXECUTE(insert_ctbl(tbl_vertices, chunk_vertex_ids, v_id, v_id, CTBL_BEHAVIOR_UNIQUE))

    jp->atString = emptyStringEvent_jsonp;
}
static void readVertexName(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_names = current_gwm->chunks + GWM_CHUNK_VERTEX_NAMES;

    DEBUG_ERROR_IF(append_chunk(chunk_vertex_names, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_names, string, len))

    jp->atString = emptyStringEvent_jsonp;
}
static void searchName_edge(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString = searchString_edge;
}
static void searchName_model(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString = searchString_model;
}
static void searchName_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString = searchString_vertex;
}
static void searchName_models(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atString = searchString_models;
}
static void searchString_edge(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_MSG("%s('%s')", __func__, string)

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
    DEBUG_MSG("%s('%s')", __func__, string)

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
    DEBUG_MSG("%s('%s')", __func__, string)

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
    DEBUG_MSG("%s('%s')", __func__, string)

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
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_edge_ids     = current_gwm->chunks + GWM_CHUNK_EDGE_IDS;
    Chunk* const chunk_edge_names   = current_gwm->chunks + GWM_CHUNK_EDGE_NAMES;

    jp->atNameStart     = searchName_edge;
    jp->atObjectEnd     = startReading_edges;
    jp->atObjectStart   = emptyVoidEvent_jsonp;

    uint32_t e_id       = add_chunk(chunk_edge_ids, "", 0);
    uint32_t e_name_id  = add_chunk(chunk_edge_names, "", 0);
    DEBUG_ASSERT(e_id == e_name_id)
}
static void startReading_edges(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = continueReading_model;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_edge;
}
static void startReading_model(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    REALLOC_IF_NECESSARY(GWModel, current_gwma->array, size_t, current_gwma->cap, current_gwma->size, {REALLOC_ERROR;})

    constructEmpty_gwm((current_gwm = current_gwma->array + current_gwma->size++), GWM_RECOMMENDED_PARAMETERS);

    jp->atNameStart     = searchName_model;
    jp->atObjectEnd     = startReading_models;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
}
static void startReading_models(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = stopReading_gwma;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_model;
    current_gwm         = NULL;
}
static void startReading_vertex(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    jp->atNameStart     = searchName_vertex;
    jp->atObjectEnd     = startReading_vertices;
    jp->atObjectStart   = emptyVoidEvent_jsonp;

    addVertex_gwm(current_gwm, "", 0, "", 0);
}
static void startReading_vertices(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = continueReading_model;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = startReading_vertex;
}
static void stopReading_gwma(JSONParser* const jp) {
    DEBUG_MSG("%s", __func__)

    DEBUG_ASSERT(isValid_jsonp(jp))

    /* Identify t-type vertices in every model
     * A t-type vertex is a vertex with no outgoing edges */
    for (uint32_t model_id = 0; model_id < current_gwma->size; model_id++) {
        for (uint32_t vertex_id = 0; vertex_id < current_gwma->array[model_id].size_vertices; vertex_id++) {
            if (current_gwma->array[model_id].size_outEdges[vertex_id] == 0) {
                REALLOC_IF_NECESSARY(
                    uint32_t, current_gwma->array[model_id].t_ids,
                    uint32_t, current_gwma->array[model_id].cap_t, current_gwma->array[model_id].sz_t,
                    {REALLOC_ERROR;}
                )
                current_gwma->array[model_id].t_ids[current_gwma->array[model_id].sz_t++] = vertex_id;
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

void addTransition_gwm(GWModel* const gwm, uint32_t const source, uint32_t const sink) {
    DEBUG_ASSERT(isValid_gwm(gwm))
    DEBUG_ASSERT(source < gwm->size_vertices)
    DEBUG_ASSERT(sink < gwm->size_vertices)

    REALLOC_IF_NECESSARY(
        uint32_t, gwm->transitions[source],
        uint32_t, gwm->cap_outEdges[source], gwm->size_outEdges[source],
        {REALLOC_ERROR;}
    )

    /* Binary search, the array of sinks is sorted ;) */
    uint32_t l = 0;
    uint32_t r = gwm->size_outEdges[source];
    while (l < r) {
        uint32_t m = (r + l) >> 1;
        if (gwm->transitions[source][m] > sink) r = m; else l = m + 1;
    }

    /* Do nothing if the transition already exists */
    if (r > 0 && gwm->transitions[source][r - 1] == sink) return;

    /* We insert our transition such that the array of sinks remain sorted */
    memmove(
        gwm->transitions[source] + r,                               /* Transitions with higher sink */
        gwm->transitions[source] + r + 1,                           /* Shift one right */
        (size_t)(gwm->size_outEdges[source] - r) * sizeof(uint32_t) /* Length in bytes */
    );

    /* Finally, make the transition! */
    gwm->transitions[source][r] = sink;
    gwm->size_outEdges[source]++;
}

void addVertex_gwm(
    GWModel* const gwm,
    char const* const v_id, uint64_t const v_id_len,
    char const* const v_name, uint64_t const v_name_len
) {
    DEBUG_ASSERT(isValid_gwm(gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    Chunk* const chunk_vertex_names = current_gwm->chunks + GWM_CHUNK_VERTEX_NAMES;

    current_gwm->size_vertices++;

    if (current_gwm->size_vertices == current_gwm->cap_vertices) {
        uint32_t const new_cap_vertices = current_gwm->cap_vertices << 1;
        if (new_cap_vertices < current_gwm->cap_vertices) {REALLOC_ERROR;}

        uint32_t const guess_new_cap_outEdges = current_gwm->cap_outEdges[0];

        void* ptr = realloc(current_gwm->transitions, new_cap_vertices * sizeof(uint32_t*));
        DEBUG_ERROR_IF(ptr == NULL)

        ptr = realloc(current_gwm->size_outEdges, new_cap_vertices * sizeof(uint32_t));
        DEBUG_ERROR_IF(ptr == NULL)

        ptr = realloc(current_gwm->cap_outEdges, new_cap_vertices * sizeof(uint32_t));
        DEBUG_ERROR_IF(ptr == NULL)

        for (uint32_t i = current_gwm->cap_vertices; i < new_cap_vertices; i++) {
            ptr = malloc(guess_new_cap_outEdges * sizeof(uint32_t));
            DEBUG_ERROR_IF(ptr == NULL)
            current_gwm->transitions[i] = ptr;

            current_gwm->size_outEdges[i]   = 0;
            current_gwm->cap_outEdges[i]    = guess_new_cap_outEdges;
        }
    }

    add_chunk(chunk_vertex_ids, v_id, v_id_len);
    add_chunk(chunk_vertex_names, v_name, v_name_len);
}

void constructEmpty_gwm(GWModel* const gwm, uint32_t const initial_cap_vertices, uint32_t const initial_cap_edges, uint32_t initial_cap_t) {
    DEBUG_ERROR_IF(gwm == NULL)
    DEBUG_ERROR_IF(initial_cap_vertices == 0)
    DEBUG_ERROR_IF(initial_cap_vertices == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_edges == 0)
    DEBUG_ERROR_IF(initial_cap_edges == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_t == 0)
    DEBUG_ERROR_IF(initial_cap_t == 0xFFFFFFFF)

    uint32_t const initial_edge_cap_per_vertex = initial_cap_edges / initial_cap_vertices;
    DEBUG_ERROR_IF(initial_edge_cap_per_vertex == 0)

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        gwm->chunks + GWM_CHUNK_INFO,
        GWM_INITIAL_STR_LEN * GWM_CHUNK_INFO_MAX_STRINGS,
        GWM_CHUNK_INFO_MAX_STRINGS
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        gwm->chunks + GWM_CHUNK_VERTEX_IDS,
        GWM_INITIAL_STR_LEN * (uint64_t)initial_cap_vertices,
        initial_cap_vertices
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        gwm->chunks + GWM_CHUNK_VERTEX_NAMES,
        GWM_INITIAL_STR_LEN * (uint64_t)initial_cap_vertices,
        initial_cap_vertices
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        gwm->chunks + GWM_CHUNK_EDGE_IDS,
        GWM_INITIAL_STR_LEN * (uint64_t)initial_cap_vertices,
        initial_cap_vertices
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        gwm->chunks + GWM_CHUNK_EDGE_NAMES,
        GWM_INITIAL_STR_LEN * (uint64_t)initial_cap_vertices,
        initial_cap_vertices
    ))

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_ctbl(
        gwm->tables + GWM_TBL_VERTICES,
        initial_cap_vertices,
        CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_ctbl(
        gwm->tables + GWM_TBL_EDGES,
        initial_cap_edges,
        CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
    ))

    gwm->transitions = malloc((size_t)initial_cap_vertices * sizeof(uint32_t*));
    DEBUG_ERROR_IF(gwm->transitions == NULL)

    gwm->size_outEdges = malloc((size_t)initial_cap_vertices * sizeof(uint32_t));
    DEBUG_ERROR_IF(gwm->size_outEdges == NULL)

    gwm->cap_outEdges = malloc((size_t)initial_cap_vertices * sizeof(uint32_t));
    DEBUG_ERROR_IF(gwm->cap_outEdges == NULL)

    gwm->size_vertices  = 0;
    gwm->cap_vertices   = initial_cap_vertices;

    for (uint32_t i = 0; i < initial_cap_vertices; i++) {
        gwm->transitions[i] = malloc((size_t)initial_edge_cap_per_vertex * sizeof(uint32_t));
        DEBUG_ERROR_IF(gwm->transitions[i] == NULL)

        gwm->size_outEdges[i]   = 0;
        gwm->cap_outEdges[i]    = initial_edge_cap_per_vertex;
    }

    gwm->t_ids = malloc((size_t)initial_cap_t * sizeof(uint32_t));
    DEBUG_ERROR_IF(gwm->t_ids == NULL)

    gwm->sz_t   = 0;
    gwm->cap_t  = initial_cap_t;
}

void free_gwm(GWModel* const gwm) {
    DEBUG_ABORT_IF(!isValid_gwm(gwm))

    for (int i = 0; i <= GWM_CHUNK_LAST; i++) {
        DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(free_chunk(gwm->chunks + i))
    }

    for (int i = 0; i <= GWM_TBL_LAST; i++) {
        DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(free_ctbl(gwm->tables + i))
    }

    free(gwm->size_outEdges);
    free(gwm->cap_outEdges);
}

uint32_t get_s_id_gwm(GWModel const* const gwm) {
    DEBUG_ASSERT(isValid_gwm(gwm))

    Chunk const* const chunk_info           = gwm->chunks + GWM_CHUNK_INFO;
    Chunk const* const chunk_vertex_ids     = gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable const* const tbl_vertices    = gwm->tables + GWM_TBL_VERTICES;

    for (uint32_t i = 0; i < chunk_info->nStrings; i++) {
        char const* const str = get_chunk(chunk_info, i);
        DEBUG_ERROR_IF(str == NULL)

        if (!STR_EQ_CONST(str, "startElementId")) continue;

        if (++i >= chunk_info->nStrings) { TERMINATE_ERROR_MSG("Corrupt startElementId"); }
        char const* const s_id = get_chunk(chunk_info, i);
        DEBUG_ERROR_IF(s_id == NULL)
        uint64_t const s_id_len = strlen_chunk(chunk_info, i);

        ChunkTableEntry const* const tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, s_id, s_id_len);
        if (tblEntry == NULL) { TERMINATE_ERROR_MSG("startElementId '%s' is undefined!", s_id); }

        return tblEntry->value;
    }

    return 0xFFFFFFFF;
}

bool isValid_gwm(GWModel const* const gwm) {
    if (gwm == NULL) return 0;

    for (int i = 0; i <= GWM_CHUNK_LAST; i++) {
        if (!isValid_chunk(gwm->chunks + i)) return 0;
    }

    for (int i = 0; i <= GWM_TBL_LAST; i++) {
        if (!isValid_ctbl(gwm->tables + i)) return 0;
    }

    if (gwm->transitions == NULL)   return 0;
    if (gwm->size_outEdges == NULL) return 0;
    if (gwm->cap_outEdges == NULL)  return 0;

    if (gwm->cap_vertices == 0)                 return 0;
    if (gwm->cap_vertices == 0xFFFFFFFF)        return 0;
    if (gwm->size_vertices > gwm->cap_vertices) return 0;

    if (gwm->size_vertices != gwm->chunks[GWM_CHUNK_VERTEX_IDS].nStrings) return 0;

    return 1;
}

void constructFromJSON_gwma(GWModelArray* const gwma, size_t const initial_cap, FILE* const jsonFile) {
    DEBUG_MSG("%s", __func__)

    JSONParser jp[1];

    DEBUG_ERROR_IF(gwma == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFFFFFFFFFF)
    DEBUG_ERROR_IF(jsonFile == NULL)

    gwma->array = malloc(sizeof(GWModel) * (size_t)initial_cap);
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

    current_gwm     = NULL;
    current_gwma    = gwma;
    source_id       = 0xFFFFFFFF;
    target_id       = 0xFFFFFFFF;

    if (parseStream_jsonp(jp) != JSON_PARSER_OK) {
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!");
    }

    fclose(jsonFile);
}

void free_gwma(GWModelArray* const gwma) {
    DEBUG_ABORT_IF(!isValid_gwma(gwma))

    free(gwma->array);
}

bool isValid_gwma(GWModelArray const* const gwma) {
    return  gwma != NULL                    &&
            gwma->array != NULL             &&
            gwma->cap != 0                  &&
            gwma->cap != 0xFFFFFFFFFFFFFFFF &&
            gwma->size <= gwma->cap;
}
