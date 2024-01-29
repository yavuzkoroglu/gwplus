/**
 * @file algortihm.c
 * @brief Implements the functions defined in algorithm.h
 * @author Yavuz Koroglu
 */
#include "algorithm.h"
#include "padkit/debug.h"
#include "padkit/reallocate.h"

static void generateShortestPath(
    Path* const shortestPath, GWModel const* const model,
    uint32_t const from, uint32_t const to
) {
    DEBUG_ERROR_IF(shortestPath == NULL)
    DEBUG_ASSERT(isValid_gwm(model))
    DEBUG_ASSERT(from < model->size_vertices)
    DEBUG_ASSERT(to < model->size_vertices)

    if (IS_PATH_ALLOCATED(shortestPath)) {
        flush_path(shortestPath);
    } else {
        constructEmpty_path(shortestPath, model->size_vertices, PATH_DEFAULT_FLAGS);
    }

    uint32_t const guess_initial_cap = model->size_vertices * model->size_vertices;
    DEBUG_ASSERT(guess_initial_cap >= model->size_vertices)

    PathArray pathStack[1];
    constructEmpty_patha(pathStack, guess_initial_cap);
    clone_path(pathStack->array, shortestPath);
    pathStack->size++;

    while (pathStack->size > 0) {
        /* Pop one Path from pathStack */
        clone_path(shortestPath, pathStack->array + --pathStack->size);
        uint32_t const last_v_id = shortestPath->len == 0 ? from : shortestPath->array[shortestPath->len - 1];

        for (
            uint32_t transition_id = model->size_outEdges[last_v_id] - 1;
            transition_id != 0xFFFFFFFF;
            transition_id--
        ) {
            uint32_t const next_v_id = model->transitions[last_v_id][transition_id];

            if (next_v_id == to)        { free_patha(pathStack); return; }
            if (next_v_id == GWM_ID_T)  { continue; }

            RECALLOC_IF_NECESSARY(
                Path, pathStack->array,
                uint32_t, pathStack->cap, pathStack->size,
                {RECALLOC_ERROR;}
            )
            Path* const path_at_hand = pathStack->array + pathStack->size++;
            clone_path(path_at_hand, shortestPath);

            switch (extend_path(path_at_hand, next_v_id, 1)) {
                case PATH_EXTEND_MAKES_IT_NON_SIMPLE:
                    pathStack->size--;
                    break;
                case PATH_EXTEND_OK:
                    pathStack->size -= IS_PATH_TYPE_C(path_at_hand);
            }
        }
    }

    free_patha(pathStack);
    invalidate_path(shortestPath);
}
void generate_naive(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ERROR_IF(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))

    constructEmpty_patha(testPaths, tr->paths->size);

    Path s_to_start[1]    = {NOT_A_PATH};
    Path terminal_to_t[1] = {NOT_A_PATH};
    for (uint32_t p_id = 0; p_id < tr->paths->size; p_id++) {
        Path* const path = tr->paths->array + p_id;
        DEBUG_ASSERT(isValid_path(path))

        uint32_t const start_id     = path->array[0];
        uint32_t const terminal_id  = path->array[path->len - 1];

        generateShortestPath(s_to_start, tr->model, GWM_ID_S, start_id);
        generateShortestPath(terminal_to_t, tr->model, terminal_id, GWM_ID_T);

        if (isValid_path(s_to_start) && isValid_path(terminal_to_t)) {
            RECALLOC_IF_NECESSARY(
                Path, testPaths->array,
                uint32_t, testPaths->cap, testPaths->size,
                {RECALLOC_ERROR;}
            )
            Path* const testPath = testPaths->array + testPaths->size++;
            clone_path(testPath, s_to_start);
            concat_path(testPath, path);
            concat_path(testPath, terminal_to_t);
        }
    }

    eliminateSubPaths_patha(testPaths);
    combineOverlaps_patha(testPaths);

    if (IS_PATH_ALLOCATED(s_to_start))
        free_path(s_to_start);

    if (IS_PATH_ALLOCATED(terminal_to_t))
        free_path(terminal_to_t);
}

void generate_random(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ERROR_IF(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}
void generate_approx(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ERROR_IF(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}
void generate_minflow(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ERROR_IF(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}

PathArray* generateTestsFrom(TestRequirements* const tr, int const algo_id) {
    static const Algorithm algorithms[ALGO_LAST + 1] = ALGORITHMS;

    DEBUG_ASSERT(isValid_tr(tr))
    DEBUG_ASSERT(IS_VALID_ALGO(algo_id))

    PathArray* testPaths = calloc(1, sizeof(PathArray));
    if (testPaths == NULL) {
        TERMINATE_ERROR_MSG("Could not allocate %zu bytes for PathArray* testPaths!!", sizeof(PathArray));
    }

    algorithms[algo_id](testPaths, tr);

    return testPaths;
}
