/**
 * @file algortihm.c
 * @brief Implements the functions defined in algorithm.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "algorithm.h"
#include "globals.h"
#include "padkit/debug.h"
#include "padkit/reallocate.h"

static void generateShortestPath(
    Path* const shortestPath, GWModelArray const* const models,
    uint32_t const from, uint32_t const to
) {
    DEBUG_ERROR_IF(shortestPath == NULL)
    DEBUG_ASSERT(isValid_gwma(models))
    DEBUG_ASSERT(from < models->size_vertices)
    DEBUG_ASSERT(to < models->size_vertices)

    uint32_t const count_unique_edges = countUniqueEdges_gwma(models);

    PathArray* stack_A = pathStack;
    DEBUG_ASSERT(isValid_patha(stack_A))
    flush_patha(stack_A);

    PathArray* stack_B = pathStack + 1;
    DEBUG_ASSERT(isValid_patha(stack_B))
    flush_patha(stack_B);

    if (IS_PATH_ALLOCATED(shortestPath)) {
        flush_path(shortestPath);
    } else {
        constructEmpty_path(shortestPath, count_unique_edges, PATH_DEFAULT_FLAGS);
    }

    if (areEqual_gwvertex(models->vertices + from, models->vertices + to))
        return;

    ConstTransitionIterator itr[1];
    construct_ctitr(itr, models, from);
    for (uint32_t e_id; (e_id = nextEdge_ctitr(itr)) != 0xFFFFFFFF;) {
        DEBUG_ASSERT(e_id < models->size_edges)
        GWEdge const* const edge = models->edges + e_id;
        DEBUG_ASSERT(isValid_gwedge(edge))

        Path* const path = stack_A->array + stack_A->size++;
        clone_path(path, shortestPath);

        DEBUG_ASSERT(extend_path(path, e_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, e_id, 1))

        if (areEqual_gwvertex(models->vertices + edge->target, models->vertices + to)) {
            clone_path(shortestPath, path);
            return;
        }
    }

    while (stack_A->size > 0) {
        /* Swap stacks */
        if (stack_A > stack_B) {
            stack_A--;
            stack_B++;
        } else {
            stack_A++;
            stack_B--;
        }

        while (stack_B->size > 0) {
            /* Pop a path from the current stack */
            Path* const path = stack_B->array + --stack_B->size;
            DEBUG_ASSERT(isValid_path(path))
            DEBUG_ASSERT(path->len > 0)

            uint32_t const last_e_id = path->array[path->len - 1];
            DEBUG_ASSERT(last_e_id < models->size_edges)

            GWEdge const* const last_edge = models->edges + last_e_id;
            DEBUG_ASSERT(isValid_gwedge(last_edge))

            uint32_t const last_v_id = last_edge->target;
            DEBUG_ASSERT(last_v_id < models->size_vertices)

            construct_ctitr(itr, models, last_v_id);
            for (uint32_t e_id; (e_id = nextEdge_ctitr(itr)) != 0xFFFFFFFF;) {
                DEBUG_ASSERT(e_id < models->size_edges)
                GWEdge const* const edge = models->edges + e_id;
                DEBUG_ASSERT(isValid_gwedge(edge))

                /* Push a path to the other stack */
                Path* const path_to_extend = stack_A->array + stack_A->size++;
                clone_path(path_to_extend, path);

                /* Attempt to extend the new path */
                switch (extend_path(path_to_extend, e_id, 1)) {
                    case PATH_EXTEND_MAKES_IT_NON_SIMPLE:
                        stack_A->size--;
                        break;
                    case PATH_EXTEND_OK:
                        if (areEqual_gwvertex(models->vertices + edge->target, models->vertices + to)) {
                            clone_path(shortestPath, path_to_extend);
                            return;
                        }
                }
            }
        }
    }

    invalidate_path(shortestPath);
}
void generate_naive(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))

    DEBUG_ERROR_IF(path_at_hand == NULL)

    Path* const prefixPath = path_at_hand + 1;
    DEBUG_ERROR_IF(prefixPath == NULL)

    clone_patha(testPaths, tr->paths);

    uint32_t old_sz = testPaths->size;
    combineOverlaps_patha(testPaths);
    eliminateSubPaths_patha(testPaths);
    while (old_sz != testPaths->size) {
        old_sz = testPaths->size;
        combineOverlaps_patha(testPaths);
        eliminateSubPaths_patha(testPaths);
    }

    while (1) {
        uint32_t prefix_id  = 0xFFFFFFFF;
        uint32_t suffix_id  = 0xFFFFFFFF;
        uint32_t len        = 0xFFFFFFFF;

        for (uint32_t i = 0; i < testPaths->size - 1; i++) {
            Path* const p_i = testPaths->array + i;
            DEBUG_ASSERT(isValid_path(p_i))
            DEBUG_ASSERT(p_i->len > 0)

            uint32_t const e_i = p_i->array[p_i->len - 1];
            DEBUG_ASSERT(e_i < tr->models->size_edges)

            GWEdge const* const edge_i = tr->models->edges + e_i;
            DEBUG_ASSERT(isValid_gwedge(edge_i))

            uint32_t const v_i = edge_i->target;
            DEBUG_ASSERT(v_i < tr->models->size_vertices)

            for (uint32_t j = i + 1; j < testPaths->size; j++) {
                Path* const p_j = testPaths->array + j;
                DEBUG_ASSERT(isValid_path(p_j))
                DEBUG_ASSERT(p_j->len > 0)

                uint32_t const e_j = p_j->array[0];
                DEBUG_ASSERT(e_j < tr->models->size_edges)

                GWEdge const* const edge_j = tr->models->edges + e_j;
                DEBUG_ASSERT(isValid_gwedge(edge_j))

                uint32_t const v_j = edge_j->source;
                DEBUG_ASSERT(v_j < tr->models->size_vertices)

                generateShortestPath(path_at_hand, tr->models, v_i, v_j);
                if (isValid_path(path_at_hand) && path_at_hand->len < len) {
                    prefix_id   = i;
                    suffix_id   = j;
                    len         = path_at_hand->len;
                }

                generateShortestPath(path_at_hand, tr->models, v_j, v_i);
                if (isValid_path(path_at_hand) && path_at_hand->len < len) {
                    prefix_id   = j;
                    suffix_id   = i;
                    len         = path_at_hand->len;
                }
            }
        }

        if (len == 0xFFFFFFFF) break;

        Path* const prefix = testPaths->array + prefix_id;
        Path* const suffix = testPaths->array + suffix_id;

        clone_path(prefixPath, prefix);
        prefixPath->len--;
        concat_path(prefixPath, path_at_hand);
        concat_path(prefixPath, suffix);

        /* Remember suffix */
        Path tmp[1];
        memcpy(tmp, suffix, sizeof(Path));

        /* Decrement testPaths->size */
        testPaths->size--;

        /* Shift paths */
        size_t size_in_bytes = (size_t)(testPaths->size - suffix_id) * sizeof(Path);
        memmove(suffix, suffix + 1, size_in_bytes);

        /* Flush and put suffix at the end */
        flush_path(tmp);
        memcpy(testPaths->array + testPaths->size, tmp, sizeof(Path));
    }

    for (
        Path* path = testPaths->array + testPaths->size - 1;
        path >= testPaths->array;
        path--
    ) {
        DEBUG_ASSERT(isValid_path(path))
        DEBUG_ASSERT(path->len > 0)

        uint32_t const first_e_id = path->array[0];
        DEBUG_ASSERT(first_e_id < tr->models->size_edges)

        GWEdge const* const first_edge = tr->models->edges + first_e_id;
        DEBUG_ASSERT(isValid_gwedge(first_edge))

        uint32_t const first_v_id = first_edge->source;
        DEBUG_ASSERT(first_v_id < tr->models->size_vertices)

        if (first_v_id == tr->models->s_id) continue;
        generateShortestPath(prefixPath, tr->models, tr->models->s_id, first_v_id);
        DEBUG_ASSERT(isValid_path(prefixPath))
        concat_path(prefixPath, path);
        clone_path(path, prefixPath);
    }
}

void generate_random(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}
void generate_approx(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}
void generate_minflow(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}
void generate_cpostman(PathArray* const testPaths, TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
}

void generateTests(PathArray* const testPaths, TestRequirements* const tr, int const algo_id) {
    DEBUG_ASSERT(isValid_patha(testPaths))
    DEBUG_ASSERT(isValid_tr(tr))
    DEBUG_ASSERT(IS_VALID_ALGO(algo_id))

    Algorithm const algorithms[ALGO_LAST + 1] = ALGORITHMS;

    algorithms[algo_id](testPaths, tr);
}
