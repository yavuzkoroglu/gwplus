/**
 * @file path.c
 * @brief Implements the functions defined in path.h
 * @author Yavuz Koroglu
 */
#include "padkit/reallocate.h"
#include "padkit/streq.h"
#include "path.h"

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

void dump_path(Path const* const path, Chunk const* const names) {
    DEBUG_ASSERT(isValid_path(path))
    DEBUG_ASSERT(isValid_chunk(names))

    printf("  [ ");
    uint32_t i = 0;
    while (i < path->len - 1) {
        uint32_t const v_id     = path->array[i];
        char const* const name  = get_chunk(names, v_id);
        DEBUG_ERROR_IF(name == NULL)

        printf("%s, ", name);
        i++;
    }
    if (path->len > 0) {
        uint32_t const v_id     = path->array[i];
        char const* const name  = get_chunk(names, v_id);
        DEBUG_ERROR_IF(name == NULL)

        printf("%s ", name);
    }
    puts("]");
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
            FLAG_PATH_AS_TYPE_C(path);
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

    FLAG_PATH_AS_DEALLOCATED(path);
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

    uint32_t overlap_start_pos  = head->len - 1;
    uint32_t overlap_len        = 1;
    size_t overlap_size_bytes   = sizeof(uint32_t);
    while (!mem_eq_n((char const*)(head->array + overlap_start_pos), (char const*)tail->array, overlap_size_bytes)) {
        overlap_start_pos--;
        overlap_len++;
        overlap_size_bytes += sizeof(uint32_t);
        if (overlap_start_pos == 0xFFFFFFFF)    return 0xFFFFFFFF;
        if (overlap_len > tail->len)            return 0xFFFFFFFF;
    }

    return overlap_start_pos;
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

void dump_patha(PathArray const* const pathArray, Chunk const* const names) {
    DEBUG_ASSERT(isValid_patha(pathArray))
    DEBUG_ASSERT(isValid_chunk(names))

    for (uint32_t i = 0; i < pathArray->size; i++) {
        Path const* const path = pathArray->array + i;
        printf("  p%u:", i);
        dump_path(path, names);
    }

    puts("");
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
}

bool isValid_patha(PathArray const* const pathArray) {
    return  pathArray != NULL                   &&
            pathArray->cap != 0                 &&
            pathArray->cap != 0xFFFFFFFF        &&
            pathArray->size <= pathArray->cap;
}
