/**
 * @file coverage.h
 * @brief Defines coverage criterion macros.
 * @author Yavuz Koroglu
 */
#ifndef COVERAGE_H
    #define COVERAGE_H

    /**
     * @def COV_NC
     *   The coverage criterion index of Node Coverage.
     */
    #define COV_NC  0

    /**
     * @def COV_EC
     *   The coverage criterion index of Edge Coverage.
     */
    #define COV_EC  1

    /**
     * @def COV_EPC
     *   The coverage criterion index of Edge-Pair Coverage.
     */
    #define COV_EPC 2

    /**
     * @def COV_PPC
     *   The coverage criterion index of Prime Path Coverage.
     */
    #define COV_PPC 3

    /**
     * @def COV_LAST
     *   The coverage criterion index of last coverage criterion.
     */
    #define COV_LAST    COV_PPC

    /**
     * @def COV_NC_STR
     *   The coverage criterion string of Node Coverage.
     */
    #define COV_NC_STR  "node"

    /**
     * @def COV_EC_STR
     *   The coverage criterion string of Edge Coverage.
     */
    #define COV_EC_STR  "edge"

    /**
     * @def COV_EPC_STR
     *   The coverage criterion string of Edge-Pair Coverage.
     */
    #define COV_EPC_STR "edgepair"

    /**
     * @def COV_PPC_STR
     *   The coverage criterion string of Prime Path Coverage.
     */
    #define COV_PPC_STR "prime"

    /**
     * @def COV_NC_DESC
     *   Description for Node Coverage.
     */
    #define COV_NC_DESC     "Node Coverage"

    /**
     * @def COV_EC_DESC
     *   Description for Edge Coverage.
     */
    #define COV_EC_DESC     "Edge Coverage"

    /**
     * @def COV_EPC_DESC
     *   Description for Edge-Pair Coverage.
     */
    #define COV_EPC_DESC    "Edge-Pair Coverage"

    /**
     * @def COV_PPC_DESC
     *   Description for Prime Path Coverage.
     */
    #define COV_PPC_DESC    "Prime Path Coverage"

    /**
     * @def COV_STRINGS
     *   List of coverage criterion strings.
     */
    #define COV_STRINGS         { COV_NC_STR, COV_EC_STR, COV_EPC_STR, COV_PPC_STR }

    /**
     * @def COV_STRINGS
     *   List of coverage criterion descriptions.
     */
    #define COV_DESCRIPTIONS    { COV_NC_DESC, COV_EC_DESC, COV_EPC_DESC, COV_PPC_DESC }

    /**
     * @def IS_VALID_COV
     *   Checks if a coverage criterion index is valid.
     */
    #define IS_VALID_COV(cov_id) (COV_LAST >= cov_id && cov_id >= 0)
#endif
