/**
 * @file coverage.h
 * @brief Defines coverage criterion macros.
 * @author Yavuz Koroglu
 */
#ifndef COVERAGE_H
    #define COVERAGE_H

    #define COV_NC          0
    #define COV_EC          1
    #define COV_EPC         2
    #define COV_PPC         3
    #define COV_LAST        COV_PPC

    #define COV_NC_STR      "node"
    #define COV_EC_STR      "edge"
    #define COV_EPC_STR     "edgepair"
    #define COV_PPC_STR     "prime"

    #define COV_NC_DESC     "Node Coverage"
    #define COV_EC_DESC     "Edge Coverage"
    #define COV_EPC_DESC    "Edge-Pair Coverage"
    #define COV_PPC_DESC    "Prime Path Coverage"

    #define COV_STRINGS \
        { COV_NC_STR, COV_EC_STR, COV_EPC_STR, COV_PPC_STR }

    #define COV_DESCRIPTIONS \
        { COV_NC_DESC, COV_EC_DESC, COV_EPC_DESC, COV_PPC_DESC }

    #define IS_VALID_COV(cov_id) (COV_LAST >= cov_id && cov_id >= 0)
#endif
