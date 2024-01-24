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
    #define FLAG_PATH_ALLOCATED (1 << 5)

    #define FLAG_PATH_AS_NOT_SIMPLE(path)   path->flags &= !(FLAG_PATH_SIMPLE | FLAG_PATH_PRIME)
    #define FLAG_PATH_AS_PRIME(path)        path->flags |= (FLAG_PATH_SIMPLE | FLAG_PATH_PRIME)
    #define FLAG_PATH_AS_SIMPLE(path)       path->flags |= (FLAG_PATH_SIMPLE)
    #define FLAG_PATH_AS_ALLOCATED(path)    path->flags |= (FLAG_PATH_ALLOCATED)

    #define IS_PATH_SIMPLE(path)    (path->flags & FLAG_PATH_SIMPLE)
    #define IS_PATH_PRIME(path)     ((path->flags & FLAG_PATH_PRIME) && IS_PATH_SIMPLE(path))
    #define IS_PATH_ALLOCATED(path) (path->flags & FLAG_PATH_ALLOCATED)

    #define PATH_DEFAULT_FLAGS  FLAG_PATH_ALLOCATED

    #define PATH_RECOMMENDED_PARAMETERS     PATH_DEFAULT_INITIAL_CAP, PATH_DEFAULT_FLAGS

    typedef struct PathBody {
        uint32_t cap;
        uint32_t len;
        uint32_t* vertex_ids_sorted;
        uint32_t* array;
        uint64_t flags;
    } Path;

    void clone_path(Path* const clone, Path const* const original);

    void constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags);

    bool contains_path(Path const* const path, uint32_t const vertex_id);

    #define PATH_EXTEND_OK                  0
    #define PATH_EXTEND_MAKES_IT_NON_SIMPLE 1
    int extend_path(Path* const path, uint32_t const vertex_id, bool const respectFlags);

    void flush_path(Path* const path);

    void free_path(Path* const path);

    void invalidate_path(Path* const path);

    bool isValid_path(Path const* const path);

    bool isSubPath_path(Path const* const sub, Path const* const super);

    uint32_t search_path(Path const* const path, uint32_t const vertex_id);

    typedef struct PathArrayBody {
        uint32_t cap;
        uint32_t size;
        Path* array;
    } PathArray;

    void constructEmpty_patha(PathArray* const pathArray, uint32_t const initial_cap);

    void flush_patha(PathArray* const pathArray);

    void free_patha(PathArray* const pathArray);

    bool isValid_patha(PathArray const* const pathArray);

    void primePathsFromGWModel_patha(PathArray* const pathArray, GWModel const* const gwm);
#endif
