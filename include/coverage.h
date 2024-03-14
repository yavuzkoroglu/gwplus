/**
 * @file coverage.h
 * @brief Defines supported coverage criteria.
 * @author Anonymized for ICSE2025
 */
#ifndef COVERAGE_H
    #define COVERAGE_H
    #include <stdbool.h>

    typedef int coverage_t;

    #define CUSTOM_COVERAGE -4
    #define PRIME3_COVERAGE -3
    #define PRIME2_COVERAGE -2
    #define PRIME1_COVERAGE -1
    #define VERTEX_COVERAGE 0
    #define EDGE_COVERAGE   1
    #define EPAIR_COVERAGE  2

    #define IS_VALID_COVERAGE(cov) (cov >= CUSTOM_COVERAGE)
#endif
