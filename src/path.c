#include "padkit/reallocate.h"
#include "path.h"

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags) {
    #ifndef NDEBUG
        if (path == NULL)               return 0;
        if (initial_cap == 0)           return 0;
        if (initial_cap == 0xFFFFFFFF)  return 0;
    #endif

    size_t const cap_in_bytes = sizeof(uint32_t) * (size_t)initial_cap;

    path->array = malloc(cap_in_bytes);
    #ifndef NDEBUG
        if (path->array == NULL) return 0;
    #endif

    path->vertex_ids_sorted = malloc(cap_in_bytes);
    #ifndef NDEBUG
        if (path->vertex_ids_sorted == NULL) return 0;
    #endif

    path->cap   = initial_cap;
    path->len   = 0;
    path->flags = flags;

    #ifndef NDEBUG
        return 1;
    #endif
}

bool contains_path(Path const* const path, uint32_t const vertex_id) {
    return 0;
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_path(Path* const path) {
    #ifndef NDEBUG
        if (!isValid_path(path)) return 0;
    #endif
    path->len   = 0;
    path->flags = PATH_DEFAULT_FLAGS;
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_path(Path* const path) {
    #ifndef NDEBUG
        if (!isValid_path(path)) return 0;
    #endif
    free(path->array);
    free(path->vertex_ids_sorted);
    #ifndef NDEBUG
        return 1;
    #endif
}

int insert_path(Path* const path, uint32_t const vertex_id, bool const respectFlags) {
    #ifndef NDEBUG
        if (!isValid_path(path)) return PATH_INSERT_ERROR;
    #endif

    if (path->len == 0) {
        FLAG_PATH_AS_SIMPLE(path);

        path->array[0]              = vertex_id;
        path->vertex_ids_sorted[0]  = vertex_id;
        path->len = 1;
        return PATH_INSERT_OK;
    }

    if (IS_PATH_PRIME(path)) {
        if (!respectFlags) {
            FLAG_PATH_AS_NOT_SIMPLE(path);
        } else {
            return PATH_INSERT_MAKES_IT_NON_SIMPLE;
        }
    }

    if (path->cap <= path->len) {
        uint32_t new_cap = path->cap << 1;
        if (REALLOCATE(path->array, path->cap, new_cap, sizeof(uint32_t)) == NULL) return PATH_INSERT_ERROR;
        if (REALLOCATE(path->vertex_ids_sorted, path->cap, new_cap, sizeof(uint32_t)) == NULL) return PATH_INSERT_ERROR;
        path->cap = new_cap;
    }

    uint32_t const hypothetical_sorted_position = search_path(path, vertex_id);
    if (IS_PATH_SIMPLE(path) && hypothetical_sorted_position > 0 && path->vertex_ids_sorted[hypothetical_sorted_position - 1] == vertex_id) {
        if (path->array[0] == vertex_id) {
            FLAG_PATH_AS_PRIME(path);
        } else if (!respectFlags) {
            FLAG_PATH_AS_NOT_SIMPLE(path);
        } else {
            return PATH_INSERT_MAKES_IT_NON_SIMPLE;
        }
    }

    uint32_t* const position    = path->vertex_ids_sorted + hypothetical_sorted_position;
    size_t const nElements      = path->len - hypothetical_sorted_position;
    memmove(position + 1, position, nElements * sizeof(uint32_t));
    *position = vertex_id;

    path->array[path->len++] = vertex_id;
    return PATH_INSERT_OK;
}

bool isValid_path(Path const* const path) {
    return  path != NULL            &&
            path->cap != 0          &&
            path->cap != 0xFFFFFFFF &&
            path->len <= path->cap;
}

uint32_t search_path(Path const* const path, uint32_t const vertex_id) {
    #ifndef NDEBUG
        if (!isValid_path(path))        return 0xFFFFFFFF;
        if (vertex_id == 0xFFFFFFFF)    return 0xFFFFFFFF;
    #endif

    uint32_t l = 0;
    uint32_t r = path->len;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (path->vertex_ids_sorted[m] > vertex_id) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return r;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_patha(PathArray* const pathArray, uint32_t const initial_cap) {
    #ifndef NDEBUG
        if (pathArray == NULL)          return 0;
        if (initial_cap == 0)           return 0;
        if (initial_cap == 0xFFFFFFFF)  return 0;
    #endif

    size_t const cap_in_bytes = sizeof(Path) * (size_t)initial_cap;

    pathArray->array = malloc(cap_in_bytes);
    #ifndef NDEBUG
        if (pathArray->array == NULL) return 0;
    #endif

    pathArray->cap  = initial_cap;
    pathArray->size = 0;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_patha(PathArray* const pathArray) {
    #ifndef NDEBUG
        if (!isValid_patha(pathArray)) return 0;
    #endif
    pathArray->size = 0;
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_patha(PathArray* const pathArray) {
    #ifndef NDEBUG
        if (!isValid_patha(pathArray)) return 0;
    #endif
    free(pathArray->array);
    #ifndef NDEBUG
        return 1;
    #endif
}

bool isValid_patha(PathArray const* const pathArray) {
    return  pathArray != NULL                   &&
            pathArray->cap != 0                 &&
            pathArray->cao != 0xFFFFFFFF        &&
            pathArray->size <= pathArray->cap;
}

