/**
 * @file algorithm.h
 * @brief Defines test path generation algorithms.
 * @author Yavuz Koroglu
 */
#ifndef ALGORITHM_H
    #define ALGORITHM_H
    #include "testrequirements.h"

    /**
     * @def ALGO_NAIVE
     *   Algorithm index of the naive algorithm.
     */
    #define ALGO_NAIVE          0

    /**
     * @def ALGO_RANDOM
     *   Algorithm index of the random algorithm.
     */
    #define ALGO_RANDOM         1

    /**
     * @def ALGO_APPROX
     *   Algorithm index of the approx algorithm.
     */
    #define ALGO_APPROX         2

    /**
     * @def ALGO_MINFLOW
     *   Algorithm index of the minflow algorithm.
     */
    #define ALGO_MINFLOW        3

    /**
     * @def ALGO_CPOSTMAN
     *   Algorithm index of the cpostman algorithm.
     */
    #define ALGO_CPOSTMAN       4

    /**
     * @def ALGO_LAST
     *   Algorithm index of the last algorithm.
     */
    #define ALGO_LAST           ALGO_CPOSTMAN

    /**
     * @def ALGO_NAIVE_STR
     *   Algorithm string of the naive algorithm.
     */
    #define ALGO_NAIVE_STR      "naive"

    /**
     * @def ALGO_RANDOM_STR
     *   Algorithm string of the random algorithm.
     */
    #define ALGO_RANDOM_STR     "random"

    /**
     * @def ALGO_APPROX_STR
     *   Algorithm string of the approx algorithm.
     */
    #define ALGO_APPROX_STR     "approx"

    /**
     * @def ALGO_MINFLOW_STR
     *   Algorithm string of the minflow algorithm.
     */
    #define ALGO_MINFLOW_STR    "minflow"

    /**
     * @def ALGO_CPOSTMAN_STR
     *   Algorithm string of the cpostman algorithm.
     */
    #define ALGO_CPOSTMAN_STR    "cpostman"

    /**
     * @def ALGO_NAIVE_DESC
     *   Descritpion of the naive algorithm.
     */
    #define ALGO_NAIVE_DESC     "Creates one test path for every test requirement using a shortest path algorithm"

    /**
     * @def ALGO_RANDOM_DESC
     *   Description of the random algorithm.
     */
    #define ALGO_RANDOM_DESC    "Random walks until all tests requirements are met"

    /**
     * @def ALGO_APPROX_DESC
     *   Description of the approx algorithm.
     */
    #define ALGO_APPROX_DESC    "Uses a transform graph of test requirements and a path elimination algorithm"

    /**
     * @def ALGO_MINFLOW_DESC
     *   Description of the minflow algorithm.
     */
    #define ALGO_MINFLOW_DESC   "Uses an acyclic transform graph of test requirements and a minimum flow algorithm"

    /**
     * @def ALGO_CPOSTMAN_DESC
     *   Description of the minflow algorithm.
     */
    #define ALGO_CPOSTMAN_DESC   "Uses the chinese postman algorithm"

    /**
     * @def ALGO_STRINGS
     *   List of algorithm strings.
     */
    #define ALGO_STRINGS        { ALGO_NAIVE_STR, ALGO_RANDOM_STR, ALGO_APPROX_STR, ALGO_MINFLOW_STR, ALGO_CPOSTMAN_STR }

    /**
     * @def ALGO_DESCRIPTIONS
     *   List of algorithm descriptions.
     */
    #define ALGO_DESCRIPTIONS   { ALGO_NAIVE_DESC, ALGO_RANDOM_DESC, ALGO_APPROX_DESC, ALGO_MINFLOW_DESC, ALGO_CPOSTMAN_DESC }

    typedef void(*Algorithm)(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @brief Generates test paths from test requirements using naive algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     */
    void generate_naive(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @brief Generates test paths from test requirements using random algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     */
    void generate_random(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @brief Generates test paths from test requirements using approx algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     */
    void generate_approx(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @brief Generates test paths from test requirements using minflow algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     */
    void generate_minflow(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @brief Generates test paths from test requirements using cpostman algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     */
    void generate_cpostman(PathArray* const testPaths, TestRequirements* const tr);

    /**
     * @def ALGORITHMS
     *   List of all test path generation algorithms.
     */
    #define ALGORITHMS { generate_naive, generate_random, generate_approx, generate_minflow, generate_cpostman }

    /**
     * @brief Generates test paths from test requirements using a specified algorithm.
     * @param testPaths A pointer to the test paths.
     * @param tr A pointer to the test requirements.
     * @param algo_id The algorithm index.
     */
    void generateTests(PathArray* const testPaths, TestRequirements* const tr, int const algo_id);

    /**
     * @def IS_VALID_ALGO
     *   Checks if an algorithm index is valid.
     */
    #define IS_VALID_ALGO(algo_id) (ALGO_LAST >= algo_id && algo_id >= 0)
#endif
