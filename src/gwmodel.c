/**
 * @file gwmodel.c
 * @brief Implements the functions defined in gwmodel.h
 * @author Yavuz Koroglu
 */
#include "gwmodel.h"
#include "padkit/chunk.h"
#include "padkit/graphmatrix.h"
#include "padkit/jsonparser.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static GWModelArray* current_gwma   = NULL;
static GWModel* current_gwm         = NULL;
static size_t skip_level            = 0;

/* See include/gwmodel.(dot|pdf) */
static void s00(JSONParser* const jp);
static void s01(JSONParser* const jp);
static void s02(JSONParser* const jp);
static void s03(JSONParser* const jp);
static void s04(JSONParser* const jp);
static void s05(JSONParser* const jp, char const* const string, size_t const len);
static void s06(JSONParser* const jp);
static void s07(JSONParser* const jp);
static void s08(JSONParser* const jp);
static void s09(JSONParser* const jp);
static void s10(JSONParser* const jp);
static void s11(JSONParser* const jp);
static void s12(JSONParser* const jp, char const* const string, size_t const len);
static void s13(JSONParser* const jp, char const* const string, size_t const len);
static void s14(JSONParser* const jp);
static void s15(JSONParser* const jp);
static void s16(JSONParser* const jp);
static void s17(JSONParser* const jp, char const* const string, size_t const len);
static void s18(JSONParser* const jp, char const* const string, size_t const len);
static void s19(JSONParser* const jp, char const* const string, size_t const len);
static void s20(JSONParser* const jp);
static void s21(JSONParser* const jp);
static void s22(JSONParser* const jp);
static void s23(JSONParser* const jp);
static void s24(JSONParser* const jp);
static void s25(JSONParser* const jp, char const* const string, size_t const len);
static void s26(JSONParser* const jp);
static void s27(JSONParser* const jp);
static void s28(JSONParser* const jp);
static void s29(JSONParser* const jp);
static void s30(JSONParser* const jp);
static void s31(JSONParser* const jp);
static void s32(JSONParser* const jp, char const* const string, size_t const len);
static void s33(JSONParser* const jp, char const* const string, size_t const len);
static void s34(JSONParser* const jp);
static void s35(JSONParser* const jp);
static void s36(JSONParser* const jp);
static void s37(JSONParser* const jp, char const* const string, size_t const len);
static void s38(JSONParser* const jp, char const* const string, size_t const len);
static void s39(JSONParser* const jp, char const* const string, size_t const len);
static void s40(JSONParser* const jp, char const* const string, size_t const len);
static void s41(JSONParser* const jp, char const* const string, size_t const len);
static void s42(JSONParser* const jp);
static void s43(JSONParser* const jp);
static void s44(JSONParser* const jp);
static void s45(JSONParser* const jp);
static void s46(JSONParser* const jp);
static void s47(JSONParser* const jp);
static void s48(JSONParser* const jp);
static void s49(JSONParser* const jp);
static void s50(JSONParser* const jp);
static void s51(JSONParser* const jp);
static void s52(JSONParser* const jp);
static void s53(JSONParser* const jp);

static void s00(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s01;
    jp->atRootEnd       = s02;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;

    current_gwm         = NULL;
    skip_level          = 0;
}

static void s01(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s03;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s04;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s02(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

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

    current_gwm         = NULL;
    skip_level          = 0;
}

static void s03(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s05;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s04(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = s02;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s05(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "models")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = s06;
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
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s07;
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
}

static void s06(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = s01;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s08;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s07(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = s09;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s09;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = s01;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s08(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

    /* Start a new model */
    REALLOC_IF_NECESSARY(
        GWModel, current_gwma->array,
        size_t, current_gwma->cap, current_gwma->size,
        {REALLOC_ERROR;}
    )
    constructEmpty_gwm(
        (current_gwm = current_gwma->array + current_gwma->size++),
        GWM_RECOMMENDED_PARAMETERS
    );

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s10;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s06;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s09(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s11;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s11;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s10(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s12;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s11(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s03;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s04;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s12(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_info = current_gwm->chunks + GWM_CHUNK_INFO;

    if (STR_EQ_CONST(string, "id") || STR_EQ_CONST(string, "name")) {
        /* This is new info */
        DEBUG_ERROR_IF(add_chunk(chunk_info, string, len) == 0xFFFFFFFF)
        NDEBUG_EXECUTE(add_chunk(chunk_info, string, len))

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
        jp->atString        = s13;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "vertices")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = s14;
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
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s42;
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
}

static void s13(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_info = current_gwm->chunks + GWM_CHUNK_INFO;

    /* Add the info value */
    DEBUG_ERROR_IF(add_chunk(chunk_info, string, len) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_info, string, len))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s10;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s06;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s14(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = s52;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s15;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s15(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwm(current_gwm))

    addVertex_gwm(current_gwm);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s16;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s14;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s16(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s17;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s17(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    if (STR_EQ_CONST(string, "id")) {
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
        jp->atString        = s18;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "name")) {
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
        jp->atString        = s19;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s43;
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
}

static void s18(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;
    uint32_t const v_id             = current_gwm->size_vertices - 1;

    DEBUG_ERROR_IF(append_chunk(chunk_vertex_ids, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_ids, string, len))

    DEBUG_ASSERT(
        insert_ctbl(
            tbl_vertices, chunk_vertex_ids, v_id, v_id, CTBL_BEHAVIOR_UNIQUE
        ) == CTBL_INSERT_OK
    )
    NDEBUG_EXECUTE(insert_ctbl(tbl_vertices, chunk_vertex_ids, v_id, v_id, CTBL_BEHAVIOR_UNIQUE))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s16;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s14;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s19(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_names = current_gwm->chunks + GWM_CHUNK_VERTEX_NAMES;

    DEBUG_ERROR_IF(append_chunk(chunk_vertex_names, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_names, string, len))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s16;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s14;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s20(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s21;
    jp->atRootEnd       = s22;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;

    current_gwm         = NULL;
    skip_level          = 0;
}

static void s21(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s23;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s24;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s22(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

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

    current_gwm         = NULL;
    skip_level          = 0;
}

static void s23(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s25;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s24(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = s22;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s25(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "models")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = s26;
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
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s27;
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
}

static void s26(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = s21;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s28;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s27(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = s29;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s29;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = s21;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s28(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(current_gwma))

    current_gwm
        = (current_gwm == NULL) ? current_gwma->array : current_gwm + 1;

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s30;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s26;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s29(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s31;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s31;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s30(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s32;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s31(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s23;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s24;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s32(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_info = current_gwm->chunks + GWM_CHUNK_INFO;

    if (STR_EQ_CONST(string, "startElementId")) {
        /* This is new info */
        DEBUG_ERROR_IF(add_chunk(chunk_info, string, len) == 0xFFFFFFFF)
        NDEBUG_EXECUTE(add_chunk(chunk_info, string, len))

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
        jp->atString        = s33;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "edges")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = s34;
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
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s48;
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
}

static void s33(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_info         = current_gwm->chunks + GWM_CHUNK_INFO;
    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;

    /* Add the info value */
    DEBUG_ERROR_IF(add_chunk(chunk_info, string, len) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_info, string, len))

    ChunkTableEntry const* const tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry == NULL) { TERMINATE_ERROR_MSG("Cannot recognize startElementId '%s'", string); }

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s30;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s26;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s34(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = s53;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = emptyVoidEvent_jsonp;
    jp->atObjectStart   = s35;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s35(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwm(current_gwm))

    addEdge_gwm(current_gwm);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s36;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s34;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s36(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

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
    jp->atString        = s37;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s37(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    if (STR_EQ_CONST(string, "id")) {
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
        jp->atString        = s38;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "name")) {
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
        jp->atString        = s39;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "sourceVertexId")) {
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
        jp->atString        = s40;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "targetVertexId")) {
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
        jp->atString        = s41;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = s49;
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
}

static void s38(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_edge_ids = current_gwm->chunks + GWM_CHUNK_EDGE_IDS;

    DEBUG_ERROR_IF(append_chunk(chunk_edge_ids, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_ids, string, len))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s36;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s34;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s39(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_edge_names = current_gwm->chunks + GWM_CHUNK_EDGE_NAMES;

    DEBUG_ERROR_IF(append_chunk(chunk_edge_names, string, len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_names, string, len))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s36;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s34;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s40(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;
    GWEdge* const edge              = current_gwm->edges + current_gwm->size_edges - 1;

    /* The edge cannot be valid, it must be missing a sourceVertexId */
    DEBUG_ERROR_IF(isValid_gwedge(edge))

    ChunkTableEntry const* const tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry == NULL) {TERMINATE_ERROR_MSG("Cannot recognize vertex id '%s'", string);}

    edge->source = tblEntry->value;

    if (isValid_gwedge(edge))
        addTransition_gwm(current_gwm, edge->source, edge->target);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s36;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s34;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s41(JSONParser* const jp, char const* const string, size_t const len) {
    /* DEBUG_MSG("%s('%s')", __func__, string) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwm(current_gwm))

    Chunk* const chunk_vertex_ids   = current_gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    ChunkTable* const tbl_vertices  = current_gwm->tables + GWM_TBL_VERTICES;
    GWEdge* const edge              = current_gwm->edges + current_gwm->size_edges - 1;

    /* The edge cannot be valid, it must be missing a targetVertexId */
    DEBUG_ERROR_IF(isValid_gwedge(edge))

    ChunkTableEntry const* const tblEntry = get_ctbl(tbl_vertices, chunk_vertex_ids, string, len);
    if (tblEntry == NULL) {TERMINATE_ERROR_MSG("Cannot recognize vertex id 'string'");}

    edge->target = tblEntry->value;

    if (isValid_gwedge(edge))
        addTransition_gwm(current_gwm, edge->source, edge->target);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s36;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s34;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s42(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = s44;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s10;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s06;
    jp->atObjectStart   = s44;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s43(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = s45;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s16;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s04;
    jp->atObjectStart   = s45;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s44(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s46;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s46;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s45(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s47;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s47;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s46(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s10;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s06;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s47(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s16;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s14;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s48(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s50;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s50;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s49(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    skip_level = jp->stack_size;

    jp->atArrayEnd      = s51;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = emptyVoidEvent_jsonp;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s51;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s50(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s30;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s26;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s51(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(skip_level == 0)
    DEBUG_ERROR_IF(skip_level > jp->stack_size)

    if (skip_level == jp->stack_size) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = s36;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = s34;
        jp->atObjectStart   = emptyVoidEvent_jsonp;
        jp->atRootEnd       = emptyVoidEvent_jsonp;
        jp->atRootStart     = emptyVoidEvent_jsonp;
        jp->atString        = emptyStringEvent_jsonp;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    }
}

static void s52(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s10;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s06;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s53(JSONParser* const jp) {
    /* DEBUG_MSG("%s", __func) */

    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s30;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s26;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

bool isValid_gwedge(GWEdge const* const edge) {
    return  edge != NULL                &&
            edge->source != 0xFFFFFFFF  &&
            edge->target != 0xFFFFFFFF;
}

void addEdge_gwm(GWModel* const gwm) {
    DEBUG_ASSERT(isValid_gwm(gwm))

    Chunk* const chunk_edge_ids = gwm->chunks + GWM_CHUNK_EDGE_IDS;
    Chunk* const chunk_edge_names = gwm->chunks + GWM_CHUNK_EDGE_NAMES;

    DEBUG_ERROR_IF(add_chunk(chunk_edge_ids, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_edge_ids, "", 0))

    DEBUG_ERROR_IF(add_chunk(chunk_edge_names, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_edge_names, "", 0))

    REALLOC_IF_NECESSARY(GWEdge, gwm->edges, uint32_t, gwm->cap_edges, gwm->size_edges, {REALLOC_ERROR;})
    gwm->edges[gwm->size_edges++] = NOT_A_GWEDGE;
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
    uint32_t* const position = gwm->transitions[source] + r;
    size_t const length_in_bytes = (size_t)(gwm->size_outEdges[source] - r) * sizeof(uint32_t);
    memmove(position + 1, position, length_in_bytes);
    *position = sink;

    /* Increment the number of out edges */
    gwm->size_outEdges[source]++;
}

void addVertex_gwm(GWModel* const gwm) {
    DEBUG_ASSERT(isValid_gwm(gwm))

    Chunk* const chunk_vertex_ids   = gwm->chunks + GWM_CHUNK_VERTEX_IDS;
    Chunk* const chunk_vertex_names = gwm->chunks + GWM_CHUNK_VERTEX_NAMES;

    if (gwm->size_vertices == gwm->cap_vertices) {
        uint32_t const new_cap_vertices = gwm->cap_vertices << 1;
        if (new_cap_vertices < gwm->cap_vertices) {REALLOC_ERROR;}

        uint32_t const guess_new_cap_outEdges = gwm->cap_outEdges[0];

        if (REALLOCATE(gwm->transitions, gwm->cap_vertices, new_cap_vertices, uint32_t*) == NULL)
            {REALLOC_ERROR;}

        if (REALLOCATE(gwm->size_outEdges, gwm->cap_vertices, new_cap_vertices, uint32_t) == NULL)
            {REALLOC_ERROR;}

        if (REALLOCATE(gwm->cap_outEdges, gwm->cap_vertices, new_cap_vertices, uint32_t) == NULL)
            {REALLOC_ERROR;}

        for (uint32_t i = gwm->cap_vertices; i < new_cap_vertices; i++) {
            gwm->transitions[i] = malloc(guess_new_cap_outEdges * sizeof(uint32_t));
            DEBUG_ERROR_IF(gwm->transitions[i] == NULL)

            gwm->size_outEdges[i]   = 0;
            gwm->cap_outEdges[i]    = guess_new_cap_outEdges;
        }

        gwm->cap_vertices = new_cap_vertices;
    }

    DEBUG_ERROR_IF(add_chunk(chunk_vertex_ids, "", 0) == 0xFFFFFFFF)
    DEBUG_ERROR_IF(add_chunk(chunk_vertex_names, "", 0) == 0xFFFFFFFF)
    gwm->size_vertices++;
}

void constructEmpty_gwm(
    GWModel* const gwm,
    uint32_t const initial_cap_vertices,
    uint32_t const initial_cap_edges,
    uint32_t const initial_cap_t
) {
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

    gwm->edges = malloc((size_t)initial_cap_edges * sizeof(GWEdge));
    DEBUG_ERROR_IF(gwm->edges == NULL)

    gwm->size_edges = 0;
    gwm->cap_edges  = initial_cap_edges;

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
    free(gwm->edges);
    free(gwm->t_ids);
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
    JSONParser jp[1];

    DEBUG_ERROR_IF(gwma == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFFFFFFFFFF)
    DEBUG_ERROR_IF(jsonFile == NULL)

    long const json_start_pos = ftell(jsonFile);
    DEBUG_ASSERT(json_start_pos >= 0L)

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
            emptyVoidEvent_jsonp,   /* atNameStart */
            emptyVoidEvent_jsonp,   /* atNull */
            emptyNumberEvent_jsonp, /* atNumber */
            emptyVoidEvent_jsonp,   /* atObjectEnd */
            emptyVoidEvent_jsonp,   /* atObjectStart */
            emptyVoidEvent_jsonp,   /* atRootEnd */
            s00,                    /* atRootStart */
            emptyStringEvent_jsonp, /* atString */
            emptyVoidEvent_jsonp,   /* atTrue */
            emptyVoidEvent_jsonp,   /* atValueEnd */
            emptyVoidEvent_jsonp    /* atValueStart */
        )
    )

    current_gwma = gwma;

    if (parseStream_jsonp(jp) != JSON_PARSER_OK) {
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!");
    }

    DEBUG_ERROR_IF(fseek(jsonFile, json_start_pos, SEEK_SET) != 0)
    NDEBUG_EXECUTE(fseek(jsonFile, json_start_pos, SEEK_SET))

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
    jp->atRootStart     = s20;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;

    if (parseStream_jsonp(jp) != JSON_PARSER_OK) {
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!");
    }
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
