#ifndef PATH_H
    #define PATH_H
    #include "gwmodel.h"

    #define PATH_DEFAULT_INITIAL_CAP        256
    #define PATH_ARRAY_DEFAULT_INITIAL_CAP  256

    #define FLAG_PATH_SIMPLE    (1 << 0)
    #define FLAG_PATH_PRIME     (1 << 1)
    #define FLAG_PATH_TYPE_S    (1 << 2)
    #define FLAG_PATH_TYPE_T    (1 << 3)
    #define FLAG_PATH_TEST_PATH (1 << 4)

    #define FLAG_PATH_AS_NOT_SIMPLE(path)   path->flags &= !(FLAG_PATH_SIMPLE | FLAG_PATH_PRIME)
    #define FLAG_PATH_AS_PRIME(path)        path->flags |= FLAG_PATH_SIMPLE & FLAG_PATH_PRIME

    #define IS_PATH_SIMPLE(path) (path->flags & FLAG_PATH_SIMPLE)
    #define IS_PATH_PRIME(path)  (path->flags & FLAG_PATH_PRIME) && IS_PATH_SIMPLE(path)

    #define PATH_DEFAULT_FLAGS  0

    typedef struct PathBody {
        uint32_t cap;
        uint32_t len;
        uint32_t* vertex_ids_sorted;
        uint32_t* array;
        uint64_t flags;
    } Path;

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags);

    bool contains_path(Path const* const path, uint32_t const vertex_id);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_path(Path* const path);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_path(Path* const path);

    #ifndef NDEBUG
        #define PATH_INSERT_ERROR           -1
    #endif
    #define PATH_INSERT_OK                  0
    #define PATH_INSERT_MAKES_IT_NON_SIMPLE 1
    int insert_path(Path* const path, uint32_t const vertex_id, bool const respectFlags);

    bool isValid_path(Path const* const path);

    uint32_t search_path(Path const* const path, uint32_t const vertex_id);

    typedef struct PathArrayBody {
        uint32_t cap;
        uint32_t size;
        Path* array;
    } PathArray;

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_patha(PathArray* const pathArray, uint32_t const initial_cap);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_patha(PathArray* const pathArray);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_patha(PathArray* const pathArray);

    bool isValid_patha(PathArray const* const pathArray);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    simplePathsFromGWModel_patha(PathArray* const pathArray, GWModel const* const gwm);
#endif