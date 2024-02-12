/**
 * @file testrequirements.c
 * @brief Implements functions defined in testrequirements.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "coverage.h"
#include "globals.h"
#include "testrequirements.h"
#include "padkit/debug.h"
#include "padkit/reallocate.h"

typedef void(*Constructor_tr)(TestRequirements* const tr);

static void constructForNC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwma(tr->models))

    uint32_t const count_unique_vertices = countUniqueVertices_gwma(tr->models);

    if (count_unique_vertices == 0) {
        constructEmpty_patha(tr->paths, PATH_ARRAY_RECOMMENDED_INITIAL_CAP);
        tr->paths->size = 0;
        return;
    }

    constructEmpty_patha(tr->paths, count_unique_vertices);

    ConstVertexIterator itr[1];
    construct_cvitr(itr, tr->models);

    uint32_t v_id;
    while ((v_id = nextVertex_cvitr(itr)) != 0xFFFFFFFF) {
        uint32_t const e_id = firstEdgeTowards_gwma(itr->gwma, v_id);
        if (e_id == 0xFFFFFFFF) continue;

        Path* const path = tr->paths->array + tr->paths->size++;
        constructEmpty_path(path, 1, PATH_DEFAULT_FLAGS);

        DEBUG_ASSERT(extend_path(path, e_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, e_id, 1))
    }
}
static void constructForEC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwma(tr->models))

    uint32_t const count_unique_edges = countUniqueEdges_gwma(tr->models);

    if (count_unique_edges == 0) {
        constructEmpty_patha(tr->paths, PATH_ARRAY_RECOMMENDED_INITIAL_CAP);
        tr->paths->size = 0;
        return;
    }

    constructEmpty_patha(tr->paths, count_unique_edges);

    ConstEdgeIterator itr[1];
    construct_ceitr(itr, tr->models);

    uint32_t e_id;
    while ((e_id = nextEdge_ceitr(itr)) != 0xFFFFFFFF) {
        Path* const path = tr->paths->array + tr->paths->size++;
        constructEmpty_path(path, 1, PATH_DEFAULT_FLAGS);

        DEBUG_ASSERT(extend_path(path, e_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, e_id, 1))
    }
}
static void constructForEPC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwma(tr->models))

    uint32_t const count_unique_edges = countUniqueEdges_gwma(tr->models);

    if (count_unique_edges < 2) {
        constructEmpty_patha(tr->paths, PATH_ARRAY_RECOMMENDED_INITIAL_CAP);
        tr->paths->size = 0;
        return;
    }

    uint32_t const guess_count_edge_pairs = count_unique_edges * count_unique_edges;
    DEBUG_ASSERT(guess_count_edge_pairs > count_unique_edges)

    constructEmpty_patha(tr->paths, guess_count_edge_pairs);

    ConstEdgeIterator i[1];
    construct_ceitr(i, tr->models);

    uint32_t e1_id;
    while ((e1_id = nextEdge_ceitr(i)) != 0xFFFFFFFF) {
        GWEdge const* const e1 = tr->models->edges + e1_id;
        DEBUG_ASSERT(isValid_gwedge(e1))

        ConstTransitionIterator j[1];
        construct_ctitr(j, tr->models, e1->target);

        uint32_t e2_id;
        while ((e2_id = nextEdge_ctitr(j)) != 0xFFFFFFFF) {
            Path* const path = tr->paths->array + tr->paths->size++;
            constructEmpty_path(path, 2, PATH_DEFAULT_FLAGS);

            DEBUG_ASSERT(extend_path(path, e1_id, 1) == PATH_EXTEND_OK)
            NDEBUG_EXECUTE(extend_path(path, e1_id, 1))

            DEBUG_ASSERT(extend_path(path, e2_id, 1) == PATH_EXTEND_OK)
            NDEBUG_EXECUTE(extend_path(path, e2_id, 1))
        }
    }
}
static void constructForPPC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwma(tr->models))

    uint32_t const count_unique_edges = countUniqueEdges_gwma(tr->models);

    if (count_unique_edges == 0) {
        constructEmpty_patha(tr->paths, PATH_ARRAY_RECOMMENDED_INITIAL_CAP);
        tr->paths->size = 0;
        return;
    }

    uint32_t const paths_cap_guess = count_unique_edges * count_unique_edges;
    DEBUG_ASSERT(paths_cap_guess >= count_unique_edges)
    constructEmpty_patha(tr->paths, paths_cap_guess);

    DEBUG_ASSERT(isValid_patha(pathStack))
    DEBUG_ASSERT(pathStack->cap >= count_unique_edges)
    flush_patha(pathStack);

    ConstEdgeIterator edge_itr[1];
    construct_ceitr(edge_itr, tr->models);

    uint32_t e_id;
    while ((e_id = nextEdge_ceitr(edge_itr)) != 0xFFFFFFFF) {
        Path* const path = pathStack->array + pathStack->size++;
        constructEmpty_path(path, count_unique_edges, PATH_DEFAULT_FLAGS);

        DEBUG_ASSERT(extend_path(path, e_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, e_id, 1))
    }

    DEBUG_ASSERT(IS_PATH_ALLOCATED(path_at_hand))
    DEBUG_ASSERT(path_at_hand->cap >= count_unique_edges)
    while (pathStack->size > 0) {
        /* Pop a path from pathStack */
        clone_path(path_at_hand, pathStack->array + --pathStack->size);

        /* See if we can extend path_at_hand */
        size_t potential_extensions_count       = 0;
        uint32_t const last_e_id                = path_at_hand->array[path_at_hand->len - 1];
        if (!IS_PATH_PRIME(path_at_hand)) {
            DEBUG_ASSERT(last_e_id < tr->models->size_edges)
            GWEdge const* const last_edge       = tr->models->edges + last_e_id;
            DEBUG_ASSERT(isValid_gwedge(last_edge))

            uint32_t const last_v_id            = last_edge->target;
            DEBUG_ASSERT(last_v_id < tr->models->size_vertices)

            ConstTransitionIterator itr[1];
            construct_ctitr(itr, tr->models, last_v_id);

            uint32_t t_id;
            while ((t_id = nextEdge_ctitr(itr)) != 0xFFFFFFFF) {
                /* Push path_to_extend to pathStack */
                RECALLOC_IF_NECESSARY(
                    Path, pathStack->array,
                    uint32_t, pathStack->cap, pathStack->size,
                    RECALLOC_ERROR
                )
                Path* const path_to_extend = pathStack->array + pathStack->size++;
                clone_path(path_to_extend, path_at_hand);

                /* Attempt to extend path_to_extend with candidate_target */
                switch (extend_path(path_to_extend, t_id, 1)) {
                    case PATH_EXTEND_MAKES_IT_NON_SIMPLE:
                        /* Non-simple path, pop it from pathStack */
                        pathStack->size--;
                        break;
                    case PATH_EXTEND_OK:
                        potential_extensions_count++;
                }
            }
        }

        /* Check if path_at_hand is extendable */
        if (potential_extensions_count == 0) {
            if (!IS_PATH_PRIME(path_at_hand)) {
                for (
                    Path* path = tr->paths->array + tr->paths->size - 1;
                    path >= tr->paths->array;
                    path--
                ) {
                    if (!isValid_path(path) || IS_PATH_TYPE_C(path)) continue;

                    if (isSubPath_path(path_at_hand, path))
                        goto PATH_AT_HAND_IS_SUBSUMED__FORGET_IT;

                    if (isSubPath_path(path, path_at_hand))
                        invalidate_path(path);
                }
            }

            /* Add path_at_hand to an available tr->paths position */
            Path* path = tr->paths->array + tr->paths->size - 1;
            while (path >= tr->paths->array && isValid_path(path)) path--;
            if (path < tr->paths->array) {
                RECALLOC_IF_NECESSARY(
                    Path, tr->paths->array,
                    uint32_t, tr->paths->cap, tr->paths->size,
                    RECALLOC_ERROR
                )
                path = tr->paths->array + tr->paths->size++;
            }
            clone_path(path, path_at_hand);

            PATH_AT_HAND_IS_SUBSUMED__FORGET_IT:
            ;
        }
    }

    /* Flag all valid tr->paths as prime
     * while shifting over the invalidated ones */
    for (uint32_t i = tr->paths->size - 1; i != 0xFFFFFFFF; i--) {
        Path* const p_i = tr->paths->array + i;
        if (isValid_path(p_i)) {
            FLAG_PATH_AS_PRIME(p_i);
        } else {
            /* Remember p_i */
            Path tmp[1];
            memcpy(tmp, p_i, sizeof(Path));

            /* Decrement size */
            tr->paths->size--;

            /* Shift paths */
            size_t const size_in_bytes = (size_t)(tr->paths->size - i)  * sizeof(Path);
            memmove(p_i, p_i + 1, size_in_bytes);

            /* Flush and put p_i at the end */
            flush_path(tmp);
            memcpy(tr->paths->array + tr->paths->size, tmp, sizeof(Path));
        }
    }

    flush_patha(pathStack);
    flush_path(path_at_hand);
}

void construct_tr(TestRequirements* const tr, GWModelArray const* const models, int const cov_criterion) {
    static const Constructor_tr constructors[COV_LAST + 1] = {
        constructForNC_tr,
        constructForEC_tr,
        constructForEPC_tr,
        constructForPPC_tr
    };

    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwma(models))
    DEBUG_ASSERT(IS_VALID_COV(cov_criterion))

    tr->models          = models;
    tr->hyperPaths[0]   = NOT_A_HP_ARRAY;

    constructors[cov_criterion](tr);
}

void free_tr(TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_tr(tr))

    free_patha(tr->paths);
    /* if (isValid_hpa(tr->hyperPaths)) free_hpa(tr->hyperPaths); */

    *tr = NOT_TEST_REQUIREMENTS;
}

bool isValid_tr(TestRequirements const* const tr) {
    return tr != NULL && isValid_gwma(tr->models) && isValid_patha(tr->paths);
}
