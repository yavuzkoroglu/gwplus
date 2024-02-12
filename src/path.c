/**
 * @file path.c
 * @brief Implements the functions defined in path.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "padkit/reallocate.h"
#include "padkit/streq.h"
#include "path.h"

void clone_path(Path* const clone, Path const* const original) {
    DEBUG_ASSERT(isValid_path(original))
    DEBUG_ERROR_IF(clone == original)

    if (!IS_PATH_ALLOCATED(clone)) {
        constructEmpty_path(clone, original->cap, original->flags);
    } else if (clone->cap < original->len) {
        uint32_t new_cap = clone->cap;
        while (new_cap < original->len) {
            new_cap <<= 1;
            if (new_cap < clone->cap) REALLOC_ERROR
        }

        if (REALLOCATE(clone->array, clone->cap, new_cap, uint32_t) == NULL)
            REALLOC_ERROR

        if (REALLOCATE(clone->e_ids_sorted, clone->cap, new_cap, uint32_t) == NULL)
            REALLOC_ERROR

        clone->cap = new_cap;
    }

    size_t const size_in_bytes = (size_t)original->len * sizeof(uint32_t);
    memcpy(clone->array, original->array, size_in_bytes);
    memcpy(clone->e_ids_sorted, original->e_ids_sorted, size_in_bytes);

    clone->len      = original->len;
    clone->flags    = original->flags;
}

void concat_path(Path* const head, Path const* const tail) {
    DEBUG_ASSERT(isValid_path(head))
    DEBUG_ASSERT(isValid_path(tail))

    uint32_t const new_len = head->len + tail->len;
    DEBUG_ASSERT(new_len >= head->len)
    DEBUG_ASSERT(new_len >= tail->len)

    if (new_len == head->len) return;

    if (head->cap < new_len) {
        uint32_t new_cap = head->cap;
        while (new_cap < new_len) {
            new_cap <<= 1;
            if (new_cap < head->cap) REALLOC_ERROR
        }

        if (REALLOCATE(head->array, head->cap, new_cap, uint32_t) == NULL)
            REALLOC_ERROR

        if (REALLOCATE(head->e_ids_sorted, head->cap, new_cap, uint32_t) == NULL)
            REALLOC_ERROR

        head->cap = new_cap;
    }

    size_t const tail_size_in_bytes = (size_t)tail->len * sizeof(uint32_t);
    memcpy(head->array + head->len, tail->array, tail_size_in_bytes);
    head->len = new_len;
}

void constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags) {
    DEBUG_ERROR_IF(path == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    size_t const cap_in_bytes = sizeof(uint32_t) * (size_t)initial_cap;

    path->array = malloc(cap_in_bytes);
    DEBUG_ERROR_IF(path->array == NULL)

    path->e_ids_sorted = malloc(cap_in_bytes);
    DEBUG_ERROR_IF(path->e_ids_sorted == NULL)

    path->cap   = initial_cap;
    path->len   = 0;
    path->flags = flags;
}

bool contains_path(Path const* const path, uint32_t const e_id) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(e_id == 0xFFFFFFFF)

    uint32_t const position = search_path(path, e_id);

    return position != 0 && path->e_ids_sorted[position - 1] == e_id;
}

int extend_path(Path* const path, uint32_t const e_id, bool const respectFlags) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(e_id == 0xFFFFFFFF)

    if (path->len == 0) {
        FLAG_PATH_AS_SIMPLE(path);

        path->array[0]          = e_id;
        path->e_ids_sorted[0]   = e_id;
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
            REALLOC_ERROR

        if (REALLOCATE(path->e_ids_sorted, path->cap, new_cap, sizeof(uint32_t)) == NULL)
            REALLOC_ERROR

        path->cap = new_cap;
    }

    uint32_t const hypothetical_sorted_position = search_path(path, e_id);
    if (
        IS_PATH_SIMPLE(path)                                            &&
        hypothetical_sorted_position > 0                                &&
        path->e_ids_sorted[hypothetical_sorted_position - 1] == e_id
    ) {
        if (path->array[0] == e_id) {
            FLAG_PATH_AS_PRIME(path);
            FLAG_PATH_AS_TYPE_C(path);
        } else if (!respectFlags) {
            FLAG_PATH_AS_NOT_SIMPLE(path);
        } else {
            return PATH_EXTEND_MAKES_IT_NON_SIMPLE;
        }
    }

    uint32_t* const position    = path->e_ids_sorted + hypothetical_sorted_position;
    size_t const nElements      = path->len - hypothetical_sorted_position;
    memmove(position + 1, position, nElements * sizeof(uint32_t));
    *position = e_id;

    path->array[path->len++] = e_id;
    return PATH_EXTEND_OK;
}

void flush_path(Path* const path) {
    DEBUG_ERROR_IF(path == NULL)
    DEBUG_ASSERT(IS_PATH_ALLOCATED(path))

    path->len   = 0;
    path->flags = PATH_DEFAULT_FLAGS;
}

void free_path(Path* const path) {
    DEBUG_ASSERT(IS_PATH_ALLOCATED(path))

    free(path->array);
    free(path->e_ids_sorted);

    *path = NOT_A_PATH;
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

    size_t const sub_size_in_bytes  = (size_t)sub->len * sizeof(uint32_t);
    uint32_t* const super_end       = super->array + super->len - sub->len;

    for (uint32_t* ptr = super_end; ptr >= super->array; ptr--)
        if (mem_eq_n((char const*)ptr, (char const*)sub->array, sub_size_in_bytes))
            return 1;

    return 0;
}

bool isValid_path(Path const* const path) {
    return  path != NULL            &&
            path->cap != 0          &&
            path->cap != 0xFFFFFFFF &&
            path->len <= path->cap;
}

uint32_t overlap_path(Path const* const head, Path const* const tail) {
    DEBUG_ASSERT(isValid_path(head))
    DEBUG_ASSERT(isValid_path(tail))

    if (head->len == 0 || tail->len == 0) return 0xFFFFFFFF;

    uint32_t overlap_len        = (head->len < tail->len) ? head->len : tail->len;
    uint32_t overlap_start_pos  = head->len - overlap_len;
    size_t overlap_size_bytes   = (size_t)overlap_len * sizeof(uint32_t);

    while (!mem_eq_n(
        (char const*)(head->array + overlap_start_pos),
        (char const*)tail->array,
        overlap_size_bytes
    )) {
        overlap_len--;
        overlap_start_pos++;
        overlap_size_bytes -= sizeof(uint32_t);

        if (overlap_len == 0) return 0xFFFFFFFF;
    }

    return overlap_start_pos;
}

uint32_t search_path(Path const* const path, uint32_t const e_id) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ERROR_IF(e_id == 0xFFFFFFFF)

    /* Perform rightmost binary search amongst the sorted edge indices */
    uint32_t l = 0;
    uint32_t r = path->len;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (path->e_ids_sorted[m] > e_id) r = m; else l = m + 1;
    }

    return r;
}

void clone_patha(PathArray* const clone, PathArray const* const original) {
    DEBUG_ASSERT(isValid_patha(clone))
    DEBUG_ASSERT(isValid_patha(original))

    flush_patha(clone);
    for (uint32_t i = 0; i < original->size; i++) {
        RECALLOC_IF_NECESSARY(Path, clone->array, uint32_t, clone->cap, clone->size, REALLOC_ERROR)

        Path const* const original_p    = original->array + i;
        Path* const clone_p             = clone->array + clone->size++;

        clone_path(clone_p, original_p);
    }
}

void combineOverlaps_patha(PathArray* const pathArray) {
    DEBUG_ASSERT(isValid_patha(pathArray))

    if (pathArray->size <= 1) return;

    while (1) {
        uint32_t head_id        = 0xFFFFFFFF;
        uint32_t tail_id        = 0xFFFFFFFF;
        uint32_t overlap_len    = 0;
        uint32_t start_pos      = 0xFFFFFFFF;

        /* Find the largest overlap */
        for (uint32_t i = 0; i < pathArray->size - 1; i++) {
            Path const* const head = pathArray->array + i;
            DEBUG_ASSERT(isValid_path(head))

            for (uint32_t j = i + 1; j < pathArray->size; j++) {
                Path const* const tail = pathArray->array + j;
                DEBUG_ASSERT(isValid_path(tail))

                uint32_t const overlap_start_pos            = overlap_path(head, tail);
                uint32_t const reverse_overlap_start_pos    = overlap_path(tail, head);

                if (overlap_start_pos != 0xFFFFFFFF) {
                    uint32_t const candidate_len = head->len - overlap_start_pos;
                    if (reverse_overlap_start_pos != 0xFFFFFFFF) {
                        uint32_t const reverse_candidate_len = tail->len - reverse_overlap_start_pos;
                        if (candidate_len > reverse_candidate_len && candidate_len > overlap_len) {
                            head_id     = i;
                            tail_id     = j;
                            overlap_len = candidate_len;
                            start_pos   = overlap_start_pos;
                        } else if (reverse_candidate_len > candidate_len && reverse_candidate_len > overlap_len) {
                            head_id     = j;
                            tail_id     = i;
                            overlap_len = reverse_candidate_len;
                            start_pos   = reverse_overlap_start_pos;
                        }
                    } else if (candidate_len > overlap_len) {
                        head_id     = i;
                        tail_id     = j;
                        overlap_len = candidate_len;
                        start_pos   = overlap_start_pos;
                    }
                } else if (reverse_overlap_start_pos != 0xFFFFFFFF) {
                    uint32_t const reverse_candidate_len = tail->len - reverse_overlap_start_pos;
                    if (reverse_candidate_len > overlap_len) {
                        head_id     = j;
                        tail_id     = i;
                        overlap_len = reverse_candidate_len;
                        start_pos   = reverse_overlap_start_pos;
                    }
                }
            }
        }

        /* Terminate if no overlap */
        if (start_pos >= pathArray->size) return;

        DEBUG_ERROR_IF(head_id == 0xFFFFFFFF)
        Path* const head = pathArray->array + head_id;
        DEBUG_ASSERT(isValid_path(head))

        DEBUG_ERROR_IF(tail_id == 0xFFFFFFFF)
        Path* const tail = pathArray->array + tail_id;
        DEBUG_ASSERT(isValid_path(tail))

        /* Cut the head from overlap */
        head->len = start_pos;

        /* Concat the tail */
        concat_path(head, tail);

        /* Remember the tail */
        Path tmp[1];
        memcpy(tmp, tail, sizeof(Path));

        /* Decrement the path array size */
        pathArray->size--;

        /* Shift over the old tail */
        size_t const size_in_bytes = (size_t)(pathArray->size - tail_id) * sizeof(Path);
        memmove(tail, tail + 1, size_in_bytes);

        /* Flush and then put the tail at the end */
        flush_path(tmp);
        memcpy(pathArray->array + pathArray->size, tmp, sizeof(Path));
    }
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

void eliminateSubPaths_patha(PathArray* const pathArray) {
    DEBUG_ASSERT(isValid_patha(pathArray))

    if (pathArray->size <= 1) return;

    for (uint32_t i = 0; i < pathArray->size - 1; i++) {
        Path* const p_i = pathArray->array + i;
        DEBUG_ASSERT(isValid_path(p_i))

        for (uint32_t j = i + 1; j < pathArray->size; j++) {
            Path* const p_j = pathArray->array + j;
            DEBUG_ASSERT(isValid_path(p_j))

            if (isSubPath_path(p_i, p_j)) {
                /* Remember p_i */
                Path tmp[1];
                memcpy(tmp, p_i, sizeof(Path));

                /* Shift paths */
                pathArray->size--;
                size_t const size_in_bytes = (size_t)(pathArray->size - i) * sizeof(Path);
                memmove(p_i, p_i + 1, size_in_bytes);

                /* Flush and put p_i at the end */
                flush_path(tmp);
                memcpy(pathArray->array + pathArray->size, tmp, sizeof(Path));

                i--;
                break;
            } else if (isSubPath_path(p_j, p_i)) {
                /* Remember p_j */
                Path tmp[1];
                memcpy(tmp, p_j, sizeof(Path));

                /* Shift paths */
                pathArray->size--;
                size_t const size_in_bytes = (size_t)(pathArray->size - j) * sizeof(Path);
                memmove(p_j, p_j + 1, size_in_bytes);

                /* Flush and put p_j at the end */
                flush_path(tmp);
                memcpy(pathArray->array + pathArray->size, tmp, sizeof(Path));

                j--;
            }
        }
    }
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
    ) if (IS_PATH_ALLOCATED(path)) free_path(path);

    free(pathArray->array);

    *pathArray = NOT_A_PATH_ARRAY;
}

bool isValid_patha(PathArray const* const pathArray) {
    return  pathArray != NULL                   &&
            pathArray->cap != 0                 &&
            pathArray->cap != 0xFFFFFFFF        &&
            pathArray->size <= pathArray->cap;
}
