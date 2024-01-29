/**
 * @file superpath.c
 * @brief Implements functions defined in superpath.h
 * @author Yavuz Koroglu
 */
#include "coverage.h"
#include "padkit/debug.h"
#include "padkit/reallocate.h"
#include "superpath.h"

typedef void(*Constructor_tr)(TestRequirements* const tr);

static void constructForNC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwm(tr->model))
    DEBUG_ASSERT(tr->model->size_vertices > 2)

    uint32_t const guess_path_count = tr->model->size_vertices - 2;
    constructEmpty_patha(tr->paths, guess_path_count);

    tr->paths->size = guess_path_count;
    uint32_t v_id = 2;
    uint32_t p_id = 0;
    while (p_id < tr->paths->size) {
        Path* const path = tr->paths->array + p_id;
        constructEmpty_path(path, 1, PATH_DEFAULT_FLAGS);
        DEBUG_ASSERT(extend_path(path, v_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, v_id, 1))
        v_id++;
        p_id++;
    }
}
static void constructForEC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwm(tr->model))
    DEBUG_ASSERT(tr->model->size_vertices > 2)

    uint32_t const c1               = tr->model->size_outEdges[GWM_ID_S];
    uint32_t const c2               = tr->model->size_vertices - 2;
    uint32_t const guess_path_count = tr->model->size_edges - c1 - c2;
    constructEmpty_patha(tr->paths, guess_path_count);

    tr->paths->size = guess_path_count;
    uint32_t p_id = 0;
    for (uint32_t source_id = 2; source_id < tr->model->size_vertices; source_id++) {
        for (uint32_t transition_id = 1; transition_id < tr->model->size_outEdges[source_id]; transition_id++) {
            uint32_t const sink_id = tr->model->transitions[source_id][transition_id];

            DEBUG_ASSERT(p_id < guess_path_count)
            Path* const path = tr->paths->array + p_id++;

            constructEmpty_path(path, 2, PATH_DEFAULT_FLAGS);
            DEBUG_ASSERT(extend_path(path, source_id, 1) == PATH_EXTEND_OK)
            NDEBUG_EXECUTE(extend_path(path, source_id, 1))

            DEBUG_ASSERT(extend_path(path, sink_id, 1) == PATH_EXTEND_OK)
            NDEBUG_EXECUTE(extend_path(path, sink_id, 1))
        }
    }
}
static void constructForEPC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwm(tr->model))
    DEBUG_ASSERT(tr->model->size_vertices > 2)

    uint32_t const c1               = tr->model->size_outEdges[GWM_ID_S];
    uint32_t const c2               = tr->model->size_vertices - 2;
    uint32_t const guess_edge_count = tr->model->size_edges - c1 - c2;
    uint32_t const guess_path_count = guess_edge_count * guess_edge_count;
    DEBUG_ASSERT(guess_path_count >= guess_edge_count)
    constructEmpty_patha(tr->paths, guess_path_count);

    uint32_t p_id = 0;
    for (uint32_t v0_id = 2; v0_id < tr->model->size_vertices; v0_id++) {
        for (uint32_t t_v0v1_id = 1; t_v0v1_id < tr->model->size_outEdges[v0_id]; t_v0v1_id++) {
            uint32_t const v1_id = tr->model->transitions[v0_id][t_v0v1_id];
            for (uint32_t t_v1v2_id = 1; t_v1v2_id < tr->model->size_outEdges[v1_id]; t_v1v2_id++) {
                uint32_t const v2_id = tr->model->transitions[v1_id][t_v1v2_id];
                if (v0_id == v1_id && v1_id == v2_id) continue;

                DEBUG_ASSERT(p_id < guess_path_count)
                Path* const path = tr->paths->array + p_id++;

                if (IS_PATH_ALLOCATED(path)) {
                    DEBUG_ASSERT(path->cap == 3)
                    flush_path(path);
                } else {
                    constructEmpty_path(path, 3, PATH_DEFAULT_FLAGS);
                }

                DEBUG_ASSERT(extend_path(path, v0_id, 0) == PATH_EXTEND_OK)
                NDEBUG_EXECUTE(extend_path(path, v0_id, 0))

                DEBUG_ASSERT(extend_path(path, v1_id, 0) == PATH_EXTEND_OK)
                NDEBUG_EXECUTE(extend_path(path, v1_id, 0))

                extend_path(path, v2_id, 0);
            }
        }
    }

    tr->paths->size = p_id;
}
static void constructForPPC_tr(TestRequirements* const tr) {
    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwm(tr->model))
    DEBUG_ASSERT(tr->model->size_vertices > 2)

    uint32_t const paths_cap_guess = tr->model->size_vertices * tr->model->size_vertices;
    DEBUG_ERROR_IF(paths_cap_guess < tr->model->size_vertices)
    constructEmpty_patha(tr->paths, paths_cap_guess);

    PathArray pathStack[1];
    constructEmpty_patha(pathStack, paths_cap_guess);

    Path path_at_hand[1];
    constructEmpty_path(path_at_hand, tr->model->size_vertices, PATH_DEFAULT_FLAGS);

    pathStack->size = tr->model->size_vertices - 2;
    for (uint32_t v_id = 2; v_id < tr->model->size_vertices; v_id++) {
        Path* const path = pathStack->array + pathStack->size - v_id + 1;

        constructEmpty_path(path, tr->model->size_vertices, PATH_DEFAULT_FLAGS);

        DEBUG_ASSERT(extend_path(path, v_id, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, v_id, 1))
    }

    while (pathStack->size > 0) {
        /* Pop a path from pathStack */
        clone_path(path_at_hand, pathStack->array + --pathStack->size);

        /* See if we can extend path_at_hand */
        uint32_t const last_v_id        = path_at_hand->array[path_at_hand->len - 1];
        uint32_t const* const targets   = tr->model->transitions[last_v_id];
        uint32_t const size_outEdges    = tr->model->size_outEdges[last_v_id];

        size_t potential_extensions_count = 0;
        if (!IS_PATH_PRIME(path_at_hand)) {
            for (uint32_t i = size_outEdges - 1; i > 0; i--) {
                uint32_t const candidate_target = targets[i];

                /* Push path_to_extend to pathStack */
                RECALLOC_IF_NECESSARY(
                    Path, pathStack->array,
                    uint32_t, pathStack->cap, pathStack->size,
                    {RECALLOC_ERROR;}
                )
                Path* const path_to_extend = pathStack->array + pathStack->size++;
                clone_path(path_to_extend, path_at_hand);

                /* Attempt to extend path_to_extend with candidate_target */
                switch (extend_path(path_to_extend, candidate_target, 1)) {
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
                    {RECALLOC_ERROR;}
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
    for (
        Path* p_i = tr->paths->array + tr->paths->size - 1;
        p_i >= tr->paths->array;
        p_i--
    ) {
        if (isValid_path(p_i)) {
            FLAG_PATH_AS_PRIME(p_i);
        } else {
            for (
                Path* p_j = p_i;
                p_j < tr->paths->array + tr->paths->size - 1;
                p_j++
            ) clone_path(p_j, p_j + 1);
        }
    }

    /* Recalculate tr->paths->size */
    for (uint32_t i = 0; i < tr->paths->size; i++) {
        if (isValid_path(tr->paths->array + i)) continue;

        tr->paths->size = i;
        break;
    }

    free_patha(pathStack);
    free_path(path_at_hand);
}

void construct_tr(TestRequirements* const tr, GWModel const* const gwm, int const cov_criterion) {
    static const Constructor_tr constructors[COV_LAST + 1] = {
        constructForNC_tr,
        constructForEC_tr,
        constructForEPC_tr,
        constructForPPC_tr
    };

    DEBUG_ERROR_IF(tr == NULL)
    DEBUG_ASSERT(isValid_gwm(gwm))
    DEBUG_ASSERT(IS_VALID_COV(cov_criterion))

    tr->model = gwm;
    tr->superPaths[0] = NOT_A_SP_ARRAY;

    if (tr->model->size_vertices <= 2) {
        constructEmpty_patha(tr->paths, PATH_ARRAY_RECOMMENDED_INITIAL_CAP);
        return;
    }

    constructors[cov_criterion](tr);
}

void dump_tr(TestRequirements const* const tr) {
    DEBUG_ASSERT(isValid_tr(tr))

    char const* const model_id      = getModelId_gwm(tr->model);
    char const* const model_name    = getModelName_gwm(tr->model);
    Chunk const* const vertex_names = tr->model->chunks + GWM_CHUNK_VERTEX_NAMES;

    printf(
        "\n"
        "         MODEL_ID = %s\n"
        "       MODEL_NAME = %s\n"
        "TEST_REQUIREMENTS = \n",
        model_id, model_name
    );

    dump_patha(tr->paths, vertex_names);
}

void free_tr(TestRequirements* const tr) {
    DEBUG_ASSERT(isValid_tr(tr))

    free_patha(tr->paths);
    /* if (isValid_spa(tr->superPaths)) free_spa(tr->superPaths); */
}

bool isValid_tr(TestRequirements const* const tr) {
    return tr != NULL && isValid_gwm(tr->model) && isValid_patha(tr->paths);
}
