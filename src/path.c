#include "padkit/reallocate.h"
#include "padkit/streq.h"
#include "path.h"

/*
static void dump_path(Path const* const path) {
    if (isValid_path(path)) {
        fprintf(stderr, "  [");
        for (uint32_t i = 0; i < path->len - 1; i++) {
            fprintf(stderr, "%u, ", path->array[i]);
        }
        if (path->len > 0) fprintf(stderr, "%u", path->array[path->len - 1]);
        fputs("]\n", stderr);
    } else {
        fputs("  INVALID_PATH\n", stderr);
    }
}

static void dump_patha(PathArray const* const paths) {
    DEBUG_ASSERT(isValid_patha(paths))

    for (Path* path = paths->array + paths->size - 1; path >= paths->array; path--)
        dump_path(path);
}
*/

void clone_path(Path* const clone, Path const* const original) {
    DEBUG_ASSERT(isValid_path(original))
    DEBUG_ERROR_IF(clone == original)

    if (!IS_PATH_ALLOCATED(clone)) {
        constructEmpty_path(clone, original->cap, original->flags);
    } else if (clone->cap < original->len) {
        uint32_t new_cap = clone->cap << 1;
        while (new_cap < original->len) {
            new_cap <<= 1;
            if (new_cap < clone->cap) {REALLOC_ERROR;}
        }

        if (REALLOCATE(clone->array, clone->cap, new_cap, uint32_t) == NULL)
            {REALLOC_ERROR;}

        if (REALLOCATE(clone->vertex_ids_sorted, clone->cap, new_cap, uint32_t) == NULL)
            {REALLOC_ERROR;}

        clone->cap = new_cap;
    }

    size_t const size_in_bytes = (size_t)original->len * sizeof(uint32_t);
    memcpy(clone->array, original->array, size_in_bytes);
    memcpy(clone->vertex_ids_sorted, original->vertex_ids_sorted, size_in_bytes);

    clone->len      = original->len;
    clone->flags    = original->flags;
}

void constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags) {
    DEBUG_ERROR_IF(path == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    size_t const cap_in_bytes = sizeof(uint32_t) * (size_t)initial_cap;

    path->array = malloc(cap_in_bytes);
    DEBUG_ERROR_IF(path->array == NULL)

    path->vertex_ids_sorted = malloc(cap_in_bytes);
    DEBUG_ERROR_IF(path->vertex_ids_sorted == NULL)

    path->cap   = initial_cap;
    path->len   = 0;
    path->flags = flags;
}

bool contains_path(Path const* const path, uint32_t const vertex_id) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(vertex_id == 0xFFFFFFFF)

    uint32_t const position = search_path(path, vertex_id);

    return position != 0 && path->vertex_ids_sorted[position - 1] == vertex_id;
}

int extend_path(Path* const path, uint32_t const vertex_id, bool const respectFlags) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(vertex_id == 0xFFFFFFFF)

    if (path->len == 0) {
        FLAG_PATH_AS_SIMPLE(path);

        path->array[0]              = vertex_id;
        path->vertex_ids_sorted[0]  = vertex_id;
        path->len = 1;
        return PATH_EXTEND_OK;
    }

    if (IS_PATH_PRIME(path)) {
        if (!respectFlags) {
            FLAG_PATH_AS_NOT_SIMPLE(path);
        } else {
            return PATH_EXTEND_MAKES_IT_NON_SIMPLE;
        }
    }

    if (path->cap <= path->len) {
        uint32_t new_cap = path->cap << 1;

        if (REALLOCATE(path->array, path->cap, new_cap, sizeof(uint32_t)) == NULL)
            {REALLOC_ERROR;}

        if (REALLOCATE(path->vertex_ids_sorted, path->cap, new_cap, sizeof(uint32_t)) == NULL)
            {REALLOC_ERROR;}

        path->cap = new_cap;
    }

    uint32_t const hypothetical_sorted_position = search_path(path, vertex_id);
    if (
        IS_PATH_SIMPLE(path)                                                    &&
        hypothetical_sorted_position > 0                                        &&
        path->vertex_ids_sorted[hypothetical_sorted_position - 1] == vertex_id
    ) {
        if (path->array[0] == vertex_id) {
            FLAG_PATH_AS_PRIME(path);
        } else if (!respectFlags) {
            FLAG_PATH_AS_NOT_SIMPLE(path);
        } else {
            return PATH_EXTEND_MAKES_IT_NON_SIMPLE;
        }
    }

    uint32_t* const position    = path->vertex_ids_sorted + hypothetical_sorted_position;
    size_t const nElements      = path->len - hypothetical_sorted_position;
    memmove(position + 1, position, nElements * sizeof(uint32_t));
    *position = vertex_id;

    path->array[path->len++] = vertex_id;
    return PATH_EXTEND_OK;
}

void flush_path(Path* const path) {
    DEBUG_ASSERT(isValid_path(path))

    path->len   = 0;
    path->flags = PATH_DEFAULT_FLAGS;
}

void free_path(Path* const path) {
    DEBUG_ASSERT(isValid_path(path))

    free(path->array);
    free(path->vertex_ids_sorted);
}

void invalidate_path(Path* const path) {
    DEBUG_ASSERT(isValid_path(path))

    path->len   = 0xFFFFFFFF;
    path->flags = PATH_DEFAULT_FLAGS;
}

bool isSubPath_path(Path const* const sub, Path const* const super) {
    DEBUG_ASSERT(isValid_path(sub))
    DEBUG_ASSERT(isValid_path(super))

    if (sub->len > super->len) return 0;

    size_t const sub_size_in_bytes = (size_t)sub->len * sizeof(uint32_t);
    for (
        uint32_t* ptr = super->array + super->len - sub->len;
        ptr >= super->array;
        ptr--
    ) if (mem_eq_n((char const*)ptr, (char const*)sub->array, sub_size_in_bytes)) return 1;

    return 0;
}

bool isValid_path(Path const* const path) {
    return  path != NULL            &&
            path->cap != 0          &&
            path->cap != 0xFFFFFFFF &&
            path->len <= path->cap;
}

uint32_t search_path(Path const* const path, uint32_t const vertex_id) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(vertex_id == 0xFFFFFFFF)

    /* Perform rightmost binary search amongst the sorted vertex indices */
    uint32_t l = 0;
    uint32_t r = path->len;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (path->vertex_ids_sorted[m] > vertex_id) r = m; else l = m + 1;
    }

    return r;
}

void constructEmpty_patha(PathArray* const pathArray, uint32_t const initial_cap) {
    DEBUG_ERROR_IF(pathArray == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    pathArray->array = calloc(initial_cap, sizeof(Path));
    DEBUG_ERROR_IF(pathArray->array == NULL)

    pathArray->cap  = initial_cap;
    pathArray->size = 0;
}

void flush_patha(PathArray* const pathArray) {
    DEBUG_ASSERT(isValid_patha(pathArray))

    pathArray->size = 0;
}

void free_patha(PathArray* const pathArray) {
    DEBUG_ASSERT(isValid_patha(pathArray))

    for (
        Path* path = pathArray->array + pathArray->cap - 1;
        path >= pathArray->array;
        path--
    ) if (isValid_path(path)) free_path(path);

    free(pathArray->array);
}

bool isValid_patha(PathArray const* const pathArray) {
    return  pathArray != NULL                   &&
            pathArray->cap != 0                 &&
            pathArray->cap != 0xFFFFFFFF        &&
            pathArray->size <= pathArray->cap;
}

void primePathsFromGWModel_patha(PathArray* const primePaths, GWModel const* const gwm) {
    DEBUG_ERROR_IF(primePaths == NULL)
    DEBUG_ASSERT(isValid_gwm(gwm))

    if (gwm->size_vertices == 0) {
        constructEmpty_patha(primePaths, GWM_RECOMMENDED_INITIAL_VERTEX_CAP);
        return;
    }

    uint32_t const guess_initial_cap = gwm->size_vertices * gwm->size_vertices;
    DEBUG_ERROR_IF(guess_initial_cap < gwm->size_vertices)
    constructEmpty_patha(primePaths, guess_initial_cap);

    PathArray pathStack[1];
    constructEmpty_patha(pathStack, guess_initial_cap);

    Path path_at_hand[1];
    constructEmpty_path(path_at_hand, gwm->size_vertices, PATH_DEFAULT_FLAGS);

    pathStack->size = gwm->size_vertices;
    for (uint32_t i = 0; i < pathStack->size; i++) {
        Path* const path = pathStack->array + pathStack->size - i - 1;

        constructEmpty_path(path, gwm->size_vertices, PATH_DEFAULT_FLAGS);

        DEBUG_ASSERT(extend_path(path, i, 1) == PATH_EXTEND_OK)
        NDEBUG_EXECUTE(extend_path(path, i, 1))
    }

    while (pathStack->size > 0) {
        /* Pop a path from pathStack */
        clone_path(path_at_hand, pathStack->array + --pathStack->size);

        /* See if we can extend path_at_hand */
        uint32_t const last_vertex_id   = path_at_hand->array[path_at_hand->len - 1];
        uint32_t const* const targets   = gwm->transitions[last_vertex_id];
        uint32_t const size_outEdges    = gwm->size_outEdges[last_vertex_id];

        size_t potential_extensions_count = 0;
        if (!IS_PATH_PRIME(path_at_hand)) {
            for (uint32_t i = size_outEdges - 1; i != 0xFFFFFFFF; i--) {
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
                    Path* path = primePaths->array + primePaths->size - 1;
                    path >= primePaths->array;
                    path--
                ) {
                    if (!isValid_path(path) || IS_PATH_PRIME(path)) continue;

                    if (isSubPath_path(path_at_hand, path))
                        goto PATH_AT_HAND_IS_SUBSUMED__FORGET_IT;

                    if (isSubPath_path(path, path_at_hand))
                        invalidate_path(path);
                }
            }

            /* Add path_at_hand to an available primePaths position */
            Path* path = primePaths->array + primePaths->size - 1;
            while (path >= primePaths->array && isValid_path(path)) path--;
            if (path < primePaths->array) {
                RECALLOC_IF_NECESSARY(
                    Path, primePaths->array,
                    uint32_t, primePaths->cap, primePaths->size,
                    {RECALLOC_ERROR;}
                )
                path = primePaths->array + primePaths->size++;
            }
            clone_path(path, path_at_hand);

            PATH_AT_HAND_IS_SUBSUMED__FORGET_IT:
            ;
        }
    }

    /* Flag all valid primePaths as prime
     * while shifting over the invalidated ones */
    for (
        Path* p_i = primePaths->array + primePaths->size - 1;
        p_i >= primePaths->array;
        p_i--
    ) {
        if (isValid_path(p_i)) {
            FLAG_PATH_AS_PRIME(p_i);
        } else {
            for (
                Path* p_j = p_i;
                p_j < primePaths->array + primePaths->size - 1;
                p_j++
            ) clone_path(p_j, p_j + 1);
        }
    }

    /* Recalculate primePaths->size */
    for (uint32_t i = 0; i < primePaths->size; i++) {
        if (isValid_path(primePaths->array + i)) continue;

        primePaths->size = i;
        break;
    }

    free_patha(pathStack);
    free_path(path_at_hand);
}
