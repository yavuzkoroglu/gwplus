/**
 * @file gwmodel.c
 * @brief Implements the functions defined in gwmodel.h
 * @author Yavuz Koroglu
 */
#include <math.h>
#include "gwmodel.h"
#include "padkit/chunk.h"
#include "padkit/graphmatrix.h"
#include "padkit/jsonparser.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static GWModelArray* models = NULL;
static GWModel* model       = NULL;
static size_t skip_level    = 0;

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
static void s54(JSONParser* const jp, char const* const string, size_t const len);
static void s55(JSONParser* const jp);
static void s56(JSONParser* const jp);
static void s57(JSONParser* const jp, char const* const string, size_t const len);
static void s58(JSONParser* const jp);
static void s59(JSONParser* const jp, double const number);
static void s60(JSONParser* const jp, double const number);
static void s61(JSONParser* const jp, char const* const string, size_t const len);

static void s00(JSONParser* const jp) {
    DEBUG_ASSERT(isValid_jsonp(jp))

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

    skip_level          = 0;
}

static void s01(JSONParser* const jp) {
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
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;

    skip_level          = 0;
}

static void s03(JSONParser* const jp) {
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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(models))

    addModel_gwma(models);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

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
        jp->atString        = s13;
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
        jp->atString        = s61;
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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setModelIdStr_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(models))

    addVertex_gwma(models);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

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
    } else if (STR_EQ_CONST(string, "sharedState")) {
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
        jp->atString        = s54;
        jp->atTrue          = emptyVoidEvent_jsonp;
        jp->atValueEnd      = emptyVoidEvent_jsonp;
        jp->atValueStart    = emptyVoidEvent_jsonp;
    } else if (STR_EQ_CONST(string, "properties")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = emptyNumberEvent_jsonp;
        jp->atObjectEnd     = emptyVoidEvent_jsonp;
        jp->atObjectStart   = s55;
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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setVertexIdStr_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setVertexName_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(models))

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

    model               = models->models - 1;
    skip_level          = 0;
}

static void s21(JSONParser* const jp) {
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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ASSERT(isValid_gwma(models))

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

    model               = NULL;
    models              = NULL;
    skip_level          = 0;
}

static void s23(JSONParser* const jp) {
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
    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ASSERT(isValid_gwma(models))
    DEBUG_ASSERT(models->size_models > 0)

    model++;
    DEBUG_ASSERT(isValid_gwm(model))

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "startElementId")) {
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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setStartingVertex_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))

    DEBUG_ASSERT(isValid_gwma(models))
    DEBUG_ASSERT(isValid_gwm(model))

    addEdge_gwma(models, model);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setEdgeIdStr_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setEdgeName_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setEdgeSource_gwma(models, string, len);

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
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setEdgeTarget_gwma(models, string, len);

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

static void s54(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    shareVertex_gwma(models, string, len);

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

static void s55(JSONParser* const jp) {
    DEBUG_ASSERT(isValid_jsonp(jp))

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s56;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s58;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s56(JSONParser* const jp) {
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
    jp->atString        = s57;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s57(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    if (STR_EQ_CONST(string, "x")) {
        jp->atArrayEnd      = emptyVoidEvent_jsonp;
        jp->atArrayStart    = emptyVoidEvent_jsonp;
        jp->atFalse         = emptyVoidEvent_jsonp;
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = s59;
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
        jp->atNameEnd       = emptyVoidEvent_jsonp;
        jp->atNameStart     = emptyVoidEvent_jsonp;
        jp->atNull          = emptyVoidEvent_jsonp;
        jp->atNumber        = s60;
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

static void s58(JSONParser* const jp) {
    DEBUG_ASSERT(isValid_jsonp(jp))

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

static void s59(JSONParser* const jp, double const number) {
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(isnan(number))
    DEBUG_ASSERT(isfinite(number))

    DEBUG_ASSERT(isValid_gwma(models))

    setVertexX_gwma(models, number);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s56;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s58;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s60(JSONParser* const jp, double const number) {
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(isnan(number))
    DEBUG_ASSERT(isfinite(number))

    DEBUG_ASSERT(isValid_gwma(models))

    setVertexY_gwma(models, number);

    jp->atArrayEnd      = emptyVoidEvent_jsonp;
    jp->atArrayStart    = emptyVoidEvent_jsonp;
    jp->atFalse         = emptyVoidEvent_jsonp;
    jp->atNameEnd       = emptyVoidEvent_jsonp;
    jp->atNameStart     = s56;
    jp->atNull          = emptyVoidEvent_jsonp;
    jp->atNumber        = emptyNumberEvent_jsonp;
    jp->atObjectEnd     = s58;
    jp->atObjectStart   = emptyVoidEvent_jsonp;
    jp->atRootEnd       = emptyVoidEvent_jsonp;
    jp->atRootStart     = emptyVoidEvent_jsonp;
    jp->atString        = emptyStringEvent_jsonp;
    jp->atTrue          = emptyVoidEvent_jsonp;
    jp->atValueEnd      = emptyVoidEvent_jsonp;
    jp->atValueStart    = emptyVoidEvent_jsonp;
}

static void s61(JSONParser* const jp, char const* const string, size_t const len) {
    DEBUG_ASSERT(isValid_jsonp(jp))
    DEBUG_ERROR_IF(string == NULL)

    DEBUG_ASSERT(isValid_gwma(models))

    setModelName_gwma(models, string, len);

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

bool areEqual_gwvertex(GWVertex const* const v1, GWVertex const* const v2) {
    DEBUG_ASSERT(isValid_gwvertex(v1))
    DEBUG_ASSERT(isValid_gwvertex(v2))

    return v1->original_v_id == v2->original_v_id;
}

void construct_gwvertex(GWVertex* const vertex, uint32_t const original_v_id, uint32_t const initial_cap_edges) {
    DEBUG_ERROR_IF(vertex == NULL)
    DEBUG_ERROR_IF(original_v_id == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_edges == 0)
    DEBUG_ERROR_IF(initial_cap_edges == 0xFFFFFFFF)

    vertex->original_v_id   = original_v_id;
    vertex->shared_id       = GWVERTEX_NOT_SHARED;
    vertex->x               = GWVERTEX_DEFAULT_X;
    vertex->y               = GWVERTEX_DEFAULT_Y;
    vertex->size_edges      = 0;
    vertex->cap_edges       = initial_cap_edges;
    vertex->edges           = malloc((size_t)initial_cap_edges * sizeof(uint32_t));
    DEBUG_ERROR_IF(vertex->edges == NULL)
}

void free_gwvertex(GWVertex* const vertex) {
    DEBUG_ABORT_UNLESS(isValid_gwvertex(vertex))

    free(vertex->edges);
    *vertex = NOT_A_GWVERTEX;
}

bool isValid_gwvertex(GWVertex const* const vertex) {
    return  vertex != NULL                          &&
            vertex->original_v_id != 0xFFFFFFFF     &&
            !isnan(vertex->x)                       &&
            isfinite(vertex->x)                     &&
            !isnan(vertex->y)                       &&
            isfinite(vertex->y)                     &&
            vertex->size_edges <= vertex->cap_edges &&
            vertex->cap_edges != 0                  &&
            vertex->cap_edges != 0xFFFFFFFF         &&
            vertex->edges != NULL;
}

void addVertex_gwshared(GWShared* const shared_vertex, uint32_t const v_id) {
    DEBUG_ASSERT(isValid_gwshared(shared_vertex))

    REALLOC_IF_NECESSARY(
        uint32_t, shared_vertex->vertices,
        uint32_t, shared_vertex->cap_vertices, shared_vertex->size_vertices,
        REALLOC_ERROR
    )

    /* Binary search, shared_vertex->local_vertices is sorted ;) */
    uint32_t l = 0;
    uint32_t r = shared_vertex->size_vertices;
    while (l < r) {
        uint32_t m = (r + l) >> 1;
        if (shared_vertex->vertices[m] > v_id) r = m; else l = m + 1;
    }

    /* Do not allow multiple entries for the same GWVertex */
    if (r > 0 && shared_vertex->vertices[r - 1] == v_id) return;

    /* We insert the new vertex index such that shared_vertex->local_vertices remain sorted */
    uint32_t* const position = shared_vertex->vertices + r;
    size_t const length_in_bytes = (size_t)(shared_vertex->size_vertices - r) * sizeof(uint32_t);
    memmove(position + 1, position, length_in_bytes);
    *position = v_id;

    /* Increment the number of vertices */
    shared_vertex->size_vertices++;
}

void constructEmpty_gwshared(GWShared* const shared_vertex, uint32_t const initial_cap) {
    DEBUG_ERROR_IF(shared_vertex == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    shared_vertex->vertices = malloc((size_t)initial_cap * sizeof(uint32_t));
    DEBUG_ERROR_IF(shared_vertex->vertices == NULL)

    shared_vertex->size_vertices    = 0;
    shared_vertex->cap_vertices     = initial_cap;
}

void free_gwshared(GWShared* const shared_vertex) {
    DEBUG_ABORT_UNLESS(isValid_gwshared(shared_vertex))

    free(shared_vertex->vertices);
    *shared_vertex = NOT_A_GWSHARED;
}

bool isValid_gwshared(GWShared const* const shared_vertex) {
    return  shared_vertex != NULL                                       &&
            shared_vertex->size_vertices <= shared_vertex->cap_vertices &&
            shared_vertex->cap_vertices != 0                            &&
            shared_vertex->cap_vertices != 0xFFFFFFFF                   &&
            shared_vertex->vertices != NULL;
}

bool isValid_gwedge(GWEdge const* const edge) {
    return  edge != NULL                &&
            edge->source != 0xFFFFFFFF  &&
            edge->target != 0xFFFFFFFF;
}

bool isValid_gwm(GWModel const* const gwm) {
    return  gwm != NULL                         &&
            gwm->first_v_id != 0xFFFFFFFF       &&
            gwm->first_e_id != 0xFFFFFFFF       &&
            gwm->size_vertices != 0xFFFFFFFF    &&
            gwm->size_edges != 0xFFFFFFFF;
}

void addEdge_gwma(GWModelArray* const gwma, GWModel* const gwm) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ASSERT(isValid_gwm(gwm))

    Chunk* const chunk_edge_ids     = gwma->chunks + GWMA_CHUNK_EDGE_IDS;
    Chunk* const chunk_edge_names   = gwma->chunks + GWMA_CHUNK_EDGE_NAMES;

    DEBUG_ERROR_IF(add_chunk(chunk_edge_ids, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_edge_ids, "", 0))

    DEBUG_ERROR_IF(add_chunk(chunk_edge_names, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_edge_names, "", 0))

    if (gwm->size_edges == 0) gwm->first_e_id = gwma->size_edges;

    REALLOC_IF_NECESSARY(GWEdge, gwma->edges, uint32_t, gwma->cap_edges, gwma->size_edges, REALLOC_ERROR)
    gwma->edges[gwma->size_edges++] = NOT_A_GWEDGE;

    gwm->size_edges++;
}

void addModel_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))

    Chunk* const chunk_model_ids    = gwma->chunks + GWMA_CHUNK_MODEL_IDS;
    Chunk* const chunk_model_names  = gwma->chunks + GWMA_CHUNK_MODEL_NAMES;

    DEBUG_ERROR_IF(add_chunk(chunk_model_ids, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_model_ids, "", 0))

    DEBUG_ERROR_IF(add_chunk(chunk_model_names, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_model_names, "", 0))

    REALLOC_IF_NECESSARY(GWModel, gwma->models, uint32_t, gwma->cap_models, gwma->size_models, REALLOC_ERROR)
    gwma->models[gwma->size_models++] = (GWModel){ gwma->size_vertices, gwma->size_edges, 0, 0 };
}

void addTransition_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))

    uint32_t const e_id = gwma->size_edges - 1;
    DEBUG_ERROR_IF(e_id == 0xFFFFFFFF)

    GWEdge const* const edge = gwma->edges + e_id;
    DEBUG_ASSERT(isValid_gwedge(edge))
    DEBUG_ASSERT(edge->source < gwma->size_vertices)
    DEBUG_ASSERT(edge->target < gwma->size_vertices)

    GWVertex* const from = gwma->vertices + edge->source;

    REALLOC_IF_NECESSARY(
        uint32_t, from->edges,
        uint32_t, from->cap_edges, from->size_edges,
        REALLOC_ERROR
    )

    /* Binary search, the array of edges is sorted ;) */
    uint32_t l = 0;
    uint32_t r = from->size_edges;
    while (l < r) {
        uint32_t m = (r + l) >> 1;
        if (from->edges[m] > e_id) r = m; else l = m + 1;
    }

    /* Do nothing if the transition already exists */
    if (r > 0 && from->edges[r - 1] == edge->target) return;

    /* We insert our transition such that the array of sinks remain sorted */
    uint32_t* const position = from->edges + r;
    size_t const length_in_bytes = (size_t)(from->size_edges - r) * sizeof(uint32_t);
    memmove(position + 1, position, length_in_bytes);
    *position = e_id;

    /* Increment the number of outgoing edges */
    from->size_edges++;
}

void addVertex_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))

    Chunk* const chunk_vertex_ids   = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;
    Chunk* const chunk_vertex_names = gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;

    DEBUG_ERROR_IF(add_chunk(chunk_vertex_ids, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_vertex_ids, "", 0))

    DEBUG_ERROR_IF(add_chunk(chunk_vertex_names, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk_vertex_names, "", 0))

    REALLOC_IF_NECESSARY(GWModel, gwma->vertices, uint32_t, gwma->cap_vertices, gwma->size_vertices, REALLOC_ERROR)
    construct_gwvertex(gwma->vertices + gwma->size_vertices, gwma->size_vertices, gwma->guess_edge_count_per_vertex);
    gwma->size_vertices++;

    GWModel* const lastModel = lastModel_gwma(gwma);
    DEBUG_ASSERT(isValid_gwm(lastModel))

    lastModel->size_vertices++;
}

void constructEmpty_gwma(
    GWModelArray* const gwma,
    uint32_t const initial_cap_edges, uint32_t const initial_cap_models,
    uint32_t const initial_cap_shared_vertices, uint32_t const initial_cap_vertices,
    size_t const guess_id_str_len, size_t const guess_name_len
) {
    DEBUG_ERROR_IF(gwma == NULL)
    DEBUG_ERROR_IF(initial_cap_edges == 0)
    DEBUG_ERROR_IF(initial_cap_models == 0)
    DEBUG_ERROR_IF(initial_cap_shared_vertices == 0)
    DEBUG_ERROR_IF(initial_cap_vertices == 0)
    DEBUG_ERROR_IF(initial_cap_edges == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_models == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_shared_vertices == 0xFFFFFFFF)
    DEBUG_ERROR_IF(initial_cap_vertices == 0xFFFFFFFF)

    Chunk* const chunk_model_ids            = gwma->chunks + GWMA_CHUNK_MODEL_IDS;
    Chunk* const chunk_model_names          = gwma->chunks + GWMA_CHUNK_MODEL_NAMES;
    Chunk* const chunk_vertex_ids           = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;
    Chunk* const chunk_vertex_names         = gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;
    Chunk* const chunk_edge_ids             = gwma->chunks + GWMA_CHUNK_EDGE_IDS;
    Chunk* const chunk_edge_names           = gwma->chunks + GWMA_CHUNK_EDGE_NAMES;
    Chunk* const chunk_shared_states        = gwma->chunks + GWMA_CHUNK_SHARED_STATES;
    ChunkTable* const ctbl_vertex_ids       = gwma->tables + GWMA_TBL_VERTEX_IDS;
    ChunkTable* const ctbl_shared_states    = gwma->tables + GWMA_TBL_SHARED_STATES;

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_model_ids, (size_t)initial_cap_models * guess_id_str_len, initial_cap_models
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_model_names, (size_t)initial_cap_models * guess_name_len, initial_cap_models
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_vertex_ids, (size_t)initial_cap_vertices * guess_id_str_len, initial_cap_vertices
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_vertex_names, (size_t)initial_cap_vertices * guess_name_len, initial_cap_vertices
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_edge_ids, (size_t)initial_cap_edges * guess_id_str_len, initial_cap_edges
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_edge_names, (size_t)initial_cap_edges * guess_name_len, initial_cap_edges
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(
        chunk_shared_states, (size_t)initial_cap_shared_vertices * guess_name_len, initial_cap_shared_vertices
    ))

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_ctbl(
        ctbl_vertex_ids, initial_cap_vertices, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
    ))
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_ctbl(
        ctbl_shared_states, initial_cap_shared_vertices, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
    ))

    gwma->s_id = GWVERTEX_NOT_SHARED;
    gwma->guess_edge_count_per_vertex   = initial_cap_edges / initial_cap_vertices + 1;
    gwma->guess_vertex_count_per_shared = initial_cap_vertices / initial_cap_shared_vertices + 1;

    gwma->size_edges            = 0;
    gwma->size_models           = 0;
    gwma->size_shared_vertices  = 0;
    gwma->size_vertices         = 0;

    gwma->cap_edges             = initial_cap_edges;
    gwma->cap_models            = initial_cap_models;
    gwma->cap_shared_vertices   = initial_cap_shared_vertices;
    gwma->cap_vertices          = initial_cap_vertices;

    gwma->edges = malloc((size_t)initial_cap_edges * sizeof(GWEdge));
    DEBUG_ERROR_IF(gwma->edges == NULL)

    gwma->models = malloc((size_t)initial_cap_models * sizeof(GWModel));
    DEBUG_ERROR_IF(gwma->models == NULL)

    gwma->shared_vertices = malloc((size_t)initial_cap_shared_vertices * sizeof(GWShared));
    DEBUG_ERROR_IF(gwma->shared_vertices == NULL)

    gwma->vertices = malloc((size_t)initial_cap_vertices * sizeof(GWVertex));
    DEBUG_ERROR_IF(gwma->vertices == NULL)
}

uint32_t countUniqueEdges_gwma(GWModelArray const* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    return gwma->size_edges;
}

uint32_t countUniqueVertices_gwma(GWModelArray const* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))

    ConstVertexIterator itr[1];
    construct_cvitr(itr, gwma);

    uint32_t next_v_id;
    uint32_t vertex_count = 0;
    while ((next_v_id = nextVertex_cvitr(itr)) != 0xFFFFFFFF)
        vertex_count++;

    return vertex_count;
}

void fillUsingJSON_gwma(GWModelArray* const gwma, FILE* const jsonFile) {
    JSONParser jp[1];

    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(jsonFile == NULL)

    /* Record the starting position in jsonFile */
    long const json_start_pos = ftell(jsonFile);
    DEBUG_ASSERT(json_start_pos >= 0L)

    /* Prepare to parse vertices */
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

    /* Set the static models variable to gwma */
    models = gwma;

    /* Parse vertices */
    if (parseStream_jsonp(jp) != JSON_PARSER_OK)
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!")

    /* Go back to the recorded starting position in jsonFile */
    DEBUG_ERROR_IF(fseek(jsonFile, json_start_pos, SEEK_SET) != 0)
    NDEBUG_EXECUTE(fseek(jsonFile, json_start_pos, SEEK_SET))

    /* Prepare to parse edges */
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

    /* Parse edges */
    if (parseStream_jsonp(jp) != JSON_PARSER_OK)
        TERMINATE_ERROR_MSG("JSON_PARSER_ERROR!!")

    /* Free the JSONParser */
    free_jsonp(jp);
}

uint32_t findVertexId_gwma(GWModelArray const* const gwma, char const* const v_id_str, size_t const v_id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(v_id_str == NULL)

    Chunk const* const chunk_vertex_ids     = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;
    ChunkTable const* const ctbl_vertex_ids = gwma->tables + GWMA_TBL_VERTEX_IDS;

    ChunkTableEntry const* const entry = get_ctbl(ctbl_vertex_ids, chunk_vertex_ids, v_id_str, v_id_str_len);
    return entry == NULL ? 0xFFFFFFFF : entry->value;
}

uint32_t firstEdgeTowards_gwma(GWModelArray const* const gwma, uint32_t const v_id) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ASSERT(v_id < gwma->size_vertices)

    GWVertex const* vertex = gwma->vertices + v_id;
    DEBUG_ASSERT(isValid_gwvertex(vertex))

    if (IS_GWVERTEX_SHARED(vertex)) {
        DEBUG_ASSERT(vertex->shared_id < gwma->size_shared_vertices)
        GWShared const* shared = gwma->shared_vertices + vertex->shared_id;
        DEBUG_ASSERT(isValid_gwshared(shared))

        for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
            GWEdge const* edge = gwma->edges + e_id;
            for (uint32_t shared_v_id = 0; shared_v_id < shared->size_vertices; shared_v_id++) {
                if (edge->target == shared->vertices[shared_v_id]) return e_id;
            }
        }
    } else {
        for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
            GWEdge const* edge = gwma->edges + e_id;
            if (edge->target == v_id) return e_id;
        }
    }
    return 0xFFFFFFFF;
}

void free_gwma(GWModelArray* const gwma) {
    DEBUG_ABORT_IF(!isValid_gwma(gwma))

    for (
        GWVertex* vertex = gwma->vertices + gwma->size_vertices - 1;
        vertex >= gwma->vertices;
        vertex--
    ) free_gwvertex(vertex);

    for (
        GWShared* shared_vertex = gwma->shared_vertices + gwma->size_shared_vertices - 1;
        shared_vertex >= gwma->shared_vertices;
        shared_vertex--
    ) free_gwshared(shared_vertex);

    free(gwma->vertices);
    free(gwma->shared_vertices);
    free(gwma->models);
    free(gwma->edges);

    for (Chunk* chunk = gwma->chunks + GWMA_CHUNK_LAST; chunk >= gwma->chunks; chunk--)
        free_chunk(chunk);

    for (ChunkTable* ctbl = gwma->tables + GWMA_TBL_LAST; ctbl >= gwma->tables; ctbl--)
        free_ctbl(ctbl);

    *gwma = NOT_A_GWMODEL_ARRAY;
}

bool isValid_gwma(GWModelArray const* const gwma) {
    if (gwma == NULL) return 0;

    for (Chunk const* chunk = gwma->chunks + GWMA_CHUNK_LAST; chunk >= gwma->chunks; chunk--)
        if (!isValid_chunk(chunk)) return 0;

    for (ChunkTable const* ctbl = gwma->tables + GWMA_TBL_LAST; ctbl >= gwma->tables; ctbl--)
        if (!isValid_ctbl(ctbl)) return 0;

    if (gwma->guess_edge_count_per_vertex == 0)                 return 0;
    if (gwma->guess_vertex_count_per_shared == 0)               return 0;

    if (gwma->size_edges > gwma->cap_edges)                     return 0;
    if (gwma->size_models > gwma->cap_models)                   return 0;
    if (gwma->size_shared_vertices > gwma->cap_shared_vertices) return 0;
    if (gwma->size_vertices > gwma->cap_vertices)               return 0;

    if (gwma->cap_edges == 0)                                   return 0;
    if (gwma->cap_models == 0)                                  return 0;
    if (gwma->cap_shared_vertices == 0)                         return 0;
    if (gwma->cap_vertices == 0)                                return 0;

    if (gwma->cap_edges == 0xFFFFFFFF)                          return 0;
    if (gwma->cap_models == 0xFFFFFFFF)                         return 0;
    if (gwma->cap_shared_vertices == 0xFFFFFFFF)                return 0;
    if (gwma->cap_vertices == 0xFFFFFFFF)                       return 0;

    if (gwma->edges == NULL)                                    return 0;
    if (gwma->models == NULL)                                   return 0;
    if (gwma->shared_vertices == NULL)                          return 0;
    if (gwma->vertices == NULL)                                 return 0;

    return 1;
}

GWEdge* lastEdge_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    return gwma->size_edges == 0 ? NULL : gwma->edges + gwma->size_edges - 1;
}

GWModel* lastModel_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    return gwma->size_models == 0 ? NULL : gwma->models + gwma->size_models - 1;
}

GWVertex* lastVertex_gwma(GWModelArray* const gwma) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    return gwma->size_vertices == 0 ? NULL : gwma->vertices + gwma->size_vertices - 1;
}

void setEdgeIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(id_str == NULL)

    Chunk* const chunk_edge_ids = gwma->chunks + GWMA_CHUNK_EDGE_IDS;
    DEBUG_ERROR_IF(append_chunk(chunk_edge_ids, id_str, id_str_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_ids, id_str, id_str_len))
}

void setEdgeName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(name == NULL)

    Chunk* const chunk_edge_names = gwma->chunks + GWMA_CHUNK_EDGE_NAMES;
    DEBUG_ERROR_IF(append_chunk(chunk_edge_names, name, name_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_edge_names, name, name_len))
}

void setEdgeSource_gwma(GWModelArray* const gwma, char const* const v_id_str, size_t const v_id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(v_id_str == NULL)

    GWEdge* const edge = lastEdge_gwma(gwma);
    DEBUG_ASSERT(edge->source = 0xFFFFFFFF)

    edge->source = findVertexId_gwma(gwma, v_id_str, v_id_str_len);
    DEBUG_ASSERT(edge->source < gwma->size_vertices)

    if (isValid_gwedge(edge)) addTransition_gwma(gwma);
}

void setEdgeTarget_gwma(GWModelArray* const gwma, char const* const v_id_str, size_t const v_id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(v_id_str == NULL)

    GWEdge* const edge = lastEdge_gwma(gwma);
    DEBUG_ASSERT(edge->target = 0xFFFFFFFF)

    edge->target = findVertexId_gwma(gwma, v_id_str, v_id_str_len);
    DEBUG_ASSERT(edge->target < gwma->size_vertices)

    if (isValid_gwedge(edge)) addTransition_gwma(gwma);
}

void setModelIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(id_str == NULL)

    Chunk* const chunk_model_ids = gwma->chunks + GWMA_CHUNK_MODEL_IDS;
    DEBUG_ERROR_IF(append_chunk(chunk_model_ids, id_str, id_str_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_model_ids, id_str, id_str_len))
}

void setModelName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(name == NULL)

    Chunk* const chunk_model_names = gwma->chunks + GWMA_CHUNK_MODEL_NAMES;
    DEBUG_ERROR_IF(append_chunk(chunk_model_names, name, name_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_model_names, name, name_len))
}

void setStartingVertex_gwma(GWModelArray* const gwma, char const* const s_id_str, size_t const s_id_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(s_id_str == NULL)

    Chunk* const chunk_vertex_ids = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;

    for (gwma->s_id = gwma->size_vertices - 1; gwma->s_id != 0xFFFFFFFF; gwma->s_id--) {
        char const* const v_id_str = get_chunk(chunk_vertex_ids, gwma->s_id);
        DEBUG_ERROR_IF(v_id_str == NULL)
        if (str_eq_n(v_id_str, s_id_str, s_id_len)) return;
    }
}

void setVertexIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(id_str == NULL)

    Chunk* const chunk_vertex_ids = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;
    DEBUG_ERROR_IF(append_chunk(chunk_vertex_ids, id_str, id_str_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_ids, id_str, id_str_len))

    ChunkTable* const ctbl_vertex_ids = gwma->tables + GWMA_TBL_VERTEX_IDS;
    DEBUG_ASSERT(
        insert_ctbl(
            ctbl_vertex_ids, chunk_vertex_ids,
            gwma->size_vertices - 1, gwma->size_vertices - 1,
            CTBL_BEHAVIOR_UNIQUE
        ) == CTBL_INSERT_OK
    )
    NDEBUG_EXECUTE(insert_ctbl(
        ctbl_vertex_ids, chunk_vertex_ids,
        gwma->size_vertices - 1, gwma->size_vertices - 1,
        CTBL_BEHAVIOR_UNIQUE
    ))
}

void setVertexName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(name == NULL)

    Chunk* const chunk_vertex_names = gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;
    DEBUG_ERROR_IF(append_chunk(chunk_vertex_names, name, name_len) == NULL)
    NDEBUG_EXECUTE(append_chunk(chunk_vertex_names, name, name_len))
}

void setVertexX_gwma(GWModelArray* const gwma, double const x) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(isnan(x))
    DEBUG_ASSERT(isfinite(x))

    GWVertex* const vertex = lastVertex_gwma(gwma);
    DEBUG_ASSERT(isValid_gwvertex(vertex))

    vertex->x = x;
}

void setVertexY_gwma(GWModelArray* const gwma, double const y) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(isnan(y))
    DEBUG_ASSERT(isfinite(y))

    GWVertex* const vertex = lastVertex_gwma(gwma);
    DEBUG_ASSERT(isValid_gwvertex(vertex))

    vertex->y = y;
}

void shareVertex_gwma(GWModelArray* const gwma, char const* const shared_name, size_t const shared_name_len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(shared_name == NULL)

    uint32_t const v_id = gwma->size_vertices - 1;
    DEBUG_ERROR_IF(v_id == 0xFFFFFFFF)

    GWVertex* const vertex = gwma->vertices + v_id;
    DEBUG_ASSERT(isValid_gwvertex(vertex))
    DEBUG_ERROR_IF(IS_GWVERTEX_SHARED(vertex))

    Chunk* const chunk_shared_states        = gwma->chunks + GWMA_CHUNK_SHARED_STATES;
    ChunkTable* const ctbl_shared_states    = gwma->tables + GWMA_TBL_SHARED_STATES;
    ChunkTableEntry const* const entry      = get_ctbl(
        ctbl_shared_states, chunk_shared_states,
        shared_name, shared_name_len
    );
    if (entry == NULL) {
        /* Add a new shared vertex */
        REALLOC_IF_NECESSARY(
            GWShared, gwma->shared_vertices,
            uint32_t, gwma->cap_shared_vertices, gwma->size_shared_vertices,
            REALLOC_ERROR
        )

        GWShared* const shared_vertex = gwma->shared_vertices + gwma->size_shared_vertices++;
        constructEmpty_gwshared(shared_vertex, gwma->guess_vertex_count_per_shared);
        addVertex_gwshared(shared_vertex, v_id);

        vertex->shared_id = add_chunk(chunk_shared_states, shared_name, shared_name_len);
        DEBUG_ASSERT(vertex->shared_id < gwma->size_shared_vertices)

        DEBUG_ASSERT(
            insert_ctbl(
                ctbl_shared_states, chunk_shared_states,
                vertex->shared_id, vertex->shared_id,
                CTBL_BEHAVIOR_UNIQUE
            ) == CTBL_INSERT_OK
        )
        NDEBUG_EXECUTE(insert_ctbl(
            ctbl_shared_states, chunk_shared_states,
            vertex->shared_id, vertex->shared_id,
            CTBL_BEHAVIOR_UNIQUE
        ))
    } else {
        /* Connect to the existing shared vertex */
        vertex->shared_id = entry->value;
        DEBUG_ASSERT(vertex->shared_id < gwma->size_shared_vertices)

        GWShared* const shared_vertex = gwma->shared_vertices + vertex->shared_id;
        DEBUG_ASSERT(isValid_gwshared(shared_vertex))

        addVertex_gwshared(shared_vertex, v_id);
        vertex->original_v_id = shared_vertex->vertices[0];
    }
}

void writeJSON_gwma(GWModelArray const* const gwma, FILE* const jsonFile, uint32_t const* const ePath, uint32_t len) {
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ERROR_IF(jsonFile == NULL)
    DEBUG_ERROR_IF(ePath == NULL)
    DEBUG_ERROR_IF(len == 0xFFFFFFFF)

    Chunk const* const chunk_model_ids      = gwma->chunks + GWMA_CHUNK_MODEL_IDS;
    Chunk const* const chunk_model_names    = gwma->chunks + GWMA_CHUNK_MODEL_NAMES;
    Chunk const* const chunk_vertex_ids     = gwma->chunks + GWMA_CHUNK_VERTEX_IDS;
    Chunk const* const chunk_vertex_names   = gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;
    Chunk const* const chunk_edge_ids       = gwma->chunks + GWMA_CHUNK_EDGE_IDS;
    Chunk const* const chunk_edge_names     = gwma->chunks + GWMA_CHUNK_EDGE_NAMES;
    Chunk const* const chunk_shared_states  = gwma->chunks + GWMA_CHUNK_SHARED_STATES;

    fputs("{\"models\":[", jsonFile);
    for (uint32_t model_id = 0; model_id < gwma->size_models; model_id++) {
        GWModel const* const gwm = gwma->models + model_id;
        DEBUG_ASSERT(isValid_gwm(gwm))

        char const* const model_name = get_chunk(chunk_model_names, model_id);
        DEBUG_ERROR_IF(model_name == NULL)

        char const* const model_id_str = get_chunk(chunk_model_ids, model_id);
        DEBUG_ERROR_IF(model_id_str == NULL)

        fprintf(
            jsonFile,
            "{"
            "\"name\":\"%s\","
            "\"id\":\"%s\","
            "\"generator\":\"predefined_path(predefined_path)\","
            "\"actions\":[],"
            "\"vertices\":[",
            model_name,
            model_id_str
        );

        for (uint32_t v_id = gwm->first_v_id; v_id < gwm->first_v_id + gwm->size_vertices; v_id++) {
            GWVertex const* const vertex = gwma->vertices + v_id;
            DEBUG_ASSERT(isValid_gwvertex(vertex))

            char const* const v_id_str = get_chunk(chunk_vertex_ids, v_id);
            DEBUG_ERROR_IF(v_id_str == NULL)

            char const* const v_name = get_chunk(chunk_vertex_names, v_id);
            DEBUG_ERROR_IF(v_name == NULL)

            if (IS_GWVERTEX_SHARED(vertex)) {
                char const* const shared_vertex_name = get_chunk(chunk_shared_states, vertex->shared_id);
                DEBUG_ERROR_IF(shared_vertex_name == NULL)

                fprintf(
                    jsonFile,
                    "{"
                    "\"id\":\"%s\","
                    "\"name\":\"%s\","
                    "\"sharedState\":\"%s\","
                    "\"actions\":[],"
                    "\"requirements\":[],"
                    "\"properties\":{\"x\":%lf,\"y\":%lf}"
                    "}",
                    v_id_str,
                    v_name,
                    shared_vertex_name,
                    vertex->x,
                    vertex->y
                );
            } else {
                fprintf(
                    jsonFile,
                    "{"
                    "\"id\":\"%s\","
                    "\"name\":\"%s\","
                    "\"actions\":[],"
                    "\"requirements\":[],"
                    "\"properties\":{\"x\":%lf,\"y\":%lf}"
                    "}",
                    v_id_str,
                    v_name,
                    vertex->x,
                    vertex->y
                );
            }

            if (v_id < gwm->first_v_id + gwm->size_vertices - 1) fputs(",", jsonFile);
        }

        fputs("],\"edges\":[", jsonFile);

        for (uint32_t e_id = gwm->first_e_id; e_id < gwm->first_e_id + gwm->size_edges; e_id++) {
            GWEdge const* const edge = gwma->edges + e_id;
            DEBUG_ASSERT(isValid_gwedge(edge))

            char const* const edge_id_str = get_chunk(chunk_edge_ids, e_id);
            DEBUG_ERROR_IF(edge_id_str == NULL)

            char const* const edge_name = get_chunk(chunk_edge_names, e_id);
            DEBUG_ERROR_IF(edge_name == NULL)

            char const* const source_id_str = get_chunk(chunk_vertex_ids, edge->source);
            DEBUG_ERROR_IF(source_id_str == NULL)

            char const* const target_id_str = get_chunk(chunk_vertex_ids, edge->target);
            DEBUG_ERROR_IF(target_id_str == NULL)

            fprintf(
                jsonFile,
                "{"
                "\"id\":\"%s\","
                "\"name\":\"%s\","
                "\"actions\":[],"
                "\"requirements\":[],"
                "\"properties\":[],"
                "\"sourceVertexId\":\"%s\","
                "\"targetVertexId\":\"%s\""
                "}",
                edge_id_str,
                edge_name,
                source_id_str,
                target_id_str
            );

            if (e_id < gwm->first_e_id + gwm->size_edges - 1) fputs(",", jsonFile);
        }

        fputs("]", jsonFile);

        if (model_id == gwma->size_models - 1) {
            char const* const s_id_str = get_chunk(chunk_vertex_ids, gwma->s_id);
            DEBUG_ERROR_IF(s_id_str == NULL)

            fprintf(jsonFile, ",\"startElementId\":\"%s\",\"predefinedPathEdgeIds\":[", s_id_str);

            for (uint32_t i = 0; i < len; i++) {
                uint32_t const e_id = ePath[i];
                DEBUG_ASSERT(e_id < gwma->size_edges)

                char const* const e_id_str = get_chunk(chunk_edge_ids, e_id);
                DEBUG_ERROR_IF(e_id_str == NULL)

                if (i > 0) fputs(",", jsonFile);
                fprintf(jsonFile, "\"%s\"", e_id_str);
            }

            fputs("]", jsonFile);
        }

        fputs("}", jsonFile);
        if (model_id < gwma->size_models - 1) fputs(",", jsonFile);
    }
    fputs("]}", jsonFile);
}

void construct_cvitr(ConstVertexIterator* const itr, GWModelArray const* const gwma) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_gwma(gwma))

    itr->gwma           = gwma;
    itr->nextVertexId   = gwma->size_vertices - 1;
    itr->state          = CVITR_STATE_NON_SHARED;
}

bool isValid_cvitr(ConstVertexIterator const* const itr) {
    return itr != NULL && isValid_gwma(itr->gwma) && itr->state <= CVITR_STATE_LAST;
}

uint32_t nextVertex_cvitr(ConstVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_cvitr(itr))

    switch (itr->state) {
        case CVITR_STATE_NON_SHARED:
            if (itr->nextVertexId < itr->gwma->size_vertices) {
                for (
                    GWVertex const* vertex = itr->gwma->vertices + itr->nextVertexId;
                    itr->nextVertexId != 0xFFFFFFFF;
                    vertex = itr->gwma->vertices + --itr->nextVertexId
                ) {
                    DEBUG_ASSERT(isValid_gwvertex(vertex))
                    if (!IS_GWVERTEX_SHARED(vertex) && itr->nextVertexId != itr->gwma->s_id)
                        return itr->nextVertexId--;
                }
            }
            itr->nextVertexId   = itr->gwma->size_shared_vertices - 1;
            itr->state          = CVITR_STATE_SHARED;
        case CVITR_STATE_SHARED:
            if (itr->nextVertexId < itr->gwma->size_shared_vertices) {
                GWShared const* const shared_vertex = itr->gwma->shared_vertices + itr->nextVertexId--;
                DEBUG_ASSERT(isValid_gwshared(shared_vertex))
                DEBUG_ASSERT(shared_vertex->size_vertices > 0)

                return shared_vertex->vertices[0];
            }
            itr->nextVertexId   = itr->gwma->s_id;
            itr->state          = CVITR_STATE_STARTING;
        case CVITR_STATE_STARTING:
            itr->nextVertexId   = 0xFFFFFFFF;
            itr->state          = CVITR_STATE_FINISHED;
            return itr->gwma->s_id;
        case CVITR_STATE_FINISHED:
        default:
            return 0xFFFFFFFF;
    }
}

void construct_ceitr(ConstEdgeIterator* const itr, GWModelArray const* const gwma) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_gwma(gwma))

    itr->gwma       = gwma;
    itr->nextEdgeId = gwma->size_edges - 1;
}

bool isValid_ceitr(ConstEdgeIterator const* const itr) {
    return itr != NULL && isValid_gwma(itr->gwma);
}

uint32_t nextEdge_ceitr(ConstEdgeIterator* const itr) {
    DEBUG_ASSERT(isValid_ceitr(itr))

    if (itr->nextEdgeId == 0xFFFFFFFF)
        return 0xFFFFFFFF;
    else
        return itr->nextEdgeId--;
}

void construct_ctitr(ConstTransitionIterator* const itr, GWModelArray const* const gwma, uint32_t const v_id) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ASSERT(v_id < gwma->size_vertices)

    itr->gwma   = gwma;
    itr->vertex = gwma->vertices + v_id;
    DEBUG_ASSERT(isValid_gwvertex(itr->vertex))

    if (IS_GWVERTEX_SHARED(itr->vertex)) {
        GWShared const* const shared_vertex = gwma->shared_vertices + itr->vertex->shared_id;
        DEBUG_ASSERT(isValid_gwshared(shared_vertex))

        itr->nextSource = shared_vertex->size_vertices - 1;
        DEBUG_ASSERT(itr->nextSource != 0xFFFFFFFF)

        uint32_t const first_v_id = shared_vertex->vertices[itr->nextSource--];
        DEBUG_ASSERT(first_v_id < gwma->size_vertices)

        itr->vertex = gwma->vertices + first_v_id;
        DEBUG_ASSERT(isValid_gwvertex(itr->vertex))
    } else {
        itr->nextSource = 0xFFFFFFFF;
    }

    itr->nextEdgeId = itr->vertex->size_edges - 1;
}

bool isValid_ctitr(ConstTransitionIterator const* const itr) {
    return  itr != NULL                     &&
            isValid_gwma(itr->gwma)         &&
            isValid_gwvertex(itr->vertex);
}

uint32_t nextEdge_ctitr(ConstTransitionIterator* const itr) {
    DEBUG_ASSERT(isValid_ctitr(itr))

    if (itr->nextEdgeId == 0xFFFFFFFF) {
        if (itr->nextSource == 0xFFFFFFFF) return 0xFFFFFFFF;
        DEBUG_ASSERT(IS_GWVERTEX_SHARED(itr->vertex))

        GWShared const* const shared_vertex = itr->gwma->shared_vertices + itr->vertex->shared_id;
        DEBUG_ASSERT(isValid_gwshared(shared_vertex))

        uint32_t const v_id = shared_vertex->vertices[itr->nextSource--];
        DEBUG_ASSERT(v_id < itr->gwma->size_vertices)

        itr->vertex = itr->gwma->vertices + v_id;
        DEBUG_ASSERT(isValid_gwvertex(itr->vertex))

        itr->nextEdgeId = itr->vertex->size_edges - 1;
        return nextEdge_ctitr(itr);
    } else {
        return itr->vertex->edges[itr->nextEdgeId--];
    }
}
