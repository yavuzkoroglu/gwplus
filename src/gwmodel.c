#include "gwmodel.h"
#include "padkit/chunk.h"
#include "padkit/debug.h"
#include "padkit/jsonparser.h"
#include "padkit/streq.h"

static GWModelArray* gwma = NULL;

static void atArrayEnd_models               (JSONParser const* const jp);
static void atArrayStart_edges              (JSONParser const* const jp);
static void atArrayStart_models             (JSONParser const* const jp);
static void atArrayStart_vertices           (JSONParser const* const jp);
static void atNameEnd_lookFor               (JSONParser const* const jp);
static void atNameStart_lookFor_models      (JSONParser const* const jp);
static void atNameStart_lookFor_properties  (JSONParser const* const jp);
static void atObjectEnd_model               (JSONParser const* const jp);
static void atObjectStart_model             (JSONParser const* const jp);
static void atString_lookFor_models         (JSONParser const* const jp, char const* const string, size_t const len);
static void atString_lookFor_properties     (JSONParser const* const jp, char const* const string, size_t const len);
static void atString_model_name             (JSONParser const* const jp, char const* const string, size_t const len);
static void atString_model_id               (JSONParser const* const jp, char const* const string, size_t const len);
static void atValueEnd_error                (JSONParser const* const jp);
static void json_parser_error               (void);

static void atArrayEnd_models(JSONParser const* const jp) {
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
static void atArrayStart_models(JSONParser const* const jp) {
    jp->atArrayEnd      = atArrayEnd_models;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atObjectStart   = atObjectStart_model;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
}
static void atNameEnd_lookFor(JSONParser const* const jp) {
    jp->atString = emptyStringEvent_jsonp;
}
static void atNameStart_lookFor_models(JSONParser const* const jp) {
    jp->atString = atString_lookFor_models;
}
static void atNameStart_lookFor_properties(JSONParser const* const jp) {
    jp->atString = atString_lookFor_properties;
}
static void atString_lookFor_models(JSONParser const* const jp, char const* const string, size_t const len) {
    if (STR_EQ_CONST(string, "models")) {
        jp->atArrayStart    = atArrayStart_models;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atValueEnd      = atValueEnd_error;
    }
}
static void atString_lookFor_properties(JSONParser const* const jp, char const* const string, size_t const len) {
    if (STR_EQ_CONST(string, "name")) {
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = atString_model_name;
        jp->atValueEnd      = atValueEnd_error;
    } else if (STR_EQ_CONST(string, "id")) {
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = atString_model_id;
        jp->atValueEnd      = atValueEnd_error;
    } else if (STR_EQ_CONST(string, "vertices")) {
        jp->atArrayStart    = atArrayStart_vertices;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atValueEnd      = atValueEnd_error;
    } else if (STR_EQ_CONST(string, "edges")) {
        jp->atArrayStart    = atArrayStart_edges;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atValueEnd      = atValueEnd_error;
    } else if (STR_EQ_CONST(string, "startElementId")) {
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atString        = atString_model_start_id;
        jp->atValueEnd      = atValueEnd_error;
    }
}
static void atString_model_name(JSONParser const* const jp, char const* const string, size_t const len) {
    DEBUG_ERROR_IF(add_chunk(jp->chunks + GWM_CHUNK_INFO, "name", 4) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(jp->chunks + GWM_CHUNK_INFO, "name", 4))

    DEBUG_ERROR_IF(add_chunk(jp->chunks + GWM_CHUNK_INFO, string, len) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(jp->chunks + GWM_CHUNK_INFO, string, len))

    jp->atNameEnd       = atNameEnd_lookFor;
    jp->atNameStart     = atNameStart_lookFor_properties;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
}
static void atString_model_id(JSONParser const* const jp, char const* const string, size_t const len);
static void atObjectEnd_model(JSONParser const* const jp) {
    jp->atArrayEnd      = atArrayEnd_models;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = atObjectStart_model;
}
static void atObjectStart_model(JSONParser const* const jp) {
    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atNameEnd       = atNameEnd_lookFor;
    jp->atNameStart     = atNameStart_lookFor_properties;
    jp->atObjectEnd     = atObjectEnd_model;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
}
static void atValueEnd_error(JSONParser const* const jp) {
    json_parser_error();
}
static void json_parser_error(void) {
    fputs("JSON_PARSER_ERROR!!", stderr);
    exit(EXIT_FAILURE);
}

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

    if (gwm->start_node_gwid >= gwm->idTable->nKeys) return 0;
    if (gwm->start_node_rnid >= gwm->chunks[GWM_CHUNK_GIDS].nStrings) return 0;

    return 1;
}

void constructFromJSON_gwma(GWModelArray* const gwModelArray, size_t const initial_cap, FILE* const jsonFile) {
    JSONParser jp[1];

    gwma = gwModelArray;
    DEBUG_ERROR_IF(gwma == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(jsonFile == NULL)

    gwma->array = malloc(sizeof(GWModel) * initial_cap);
    DEBUG_ERROR_IF(gwma->array == NULL);

    gwma->cap   = initial_cap;
    gwma->size  = 0;

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        construct_jsonp(
            jp, jsonFile,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            atNameEnd_lookFor,
            atNameStart_lookFor_models,
            emptyVoidEvent_jsonp,
            emptyNumberEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyStringEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp,
            emptyVoidEvent_jsonp
        )
    )
    jp->atNameEnd   = atNameEnd_lookFor;
    jp->atNameStart = atNameStart_lookFor_models;

    if (parseStream_jsonp(jp) != JSON_PARSER_OK)
        json_parser_error();

    DEBUG_ASSERT(fclose(jsonFile) == 0)
    NDEBUG_EXECUTE(fclose(jsonFile))
}
