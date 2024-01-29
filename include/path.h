/**
 * @file path.h
 * @brief Defines Path, PathArray and related functions.
 *
 * A Path is an array of vertex indices where a vertex index is a 32-bit
 * unsigned integer.
 *
 * A Path also includes a sorted array of its vertex indices, which enables
 * a binary search optimization when we ask if a path traverses a given
 * vertex or not.
 *
 * @author Yavuz Koroglu
 */
#ifndef PATH_H
    #define PATH_H
    #include "padkit/chunk.h"

    /**
     * @def PATH_RECOMMENDED_INITIAL_CAP
     *   This initial cap should work nicely in most situations.
     */
    #define PATH_RECOMMENDED_INITIAL_CAP        256

    /**
     * @def PATH_ARRAY_RECOMMENDED_INITIAL_CAP
     *   This initial cap should work nicely in most situations.
     */
    #define PATH_ARRAY_RECOMMENDED_INITIAL_CAP  256

    /**
     * @def FLAG_PATH_SIMPLE
     *   A simple path is a path that traverses its vertices once, except that the initial and
     *   the final vertices can be the same.
     */
    #define FLAG_PATH_SIMPLE    (uint64_t)(1 << 0)

    /**
     * @def FLAG_PATH_SIMPLE
     *   A prime path is a simple path that is not a sub path of any other simple path.
     */
    #define FLAG_PATH_PRIME     (uint64_t)(1 << 1)

    /**
     * @def FLAG_TYPE_S
     *   A type_s path is a path that traverses the initial vertex of a graph.
     */
    #define FLAG_PATH_TYPE_S    (uint64_t)(1 << 2)

    /**
     * @def FLAG_TYPE_T
     *   A type_t path is a path that traverses a terminal vertex in a graph where
     *   a terminal vertex is a vertex that has no outgoing edges.
     */
    #define FLAG_PATH_TYPE_T    (uint64_t)(1 << 3)

    /**
     * @def FLAG_PATH_TEST_PATH
     *   A test path is a path that starts from the initial vertex of a graph.
     */
    #define FLAG_PATH_TEST_PATH (uint64_t)(1 << 4)

    /**
     * @def FLAG_PATH_ALLOCATED
     *   This flag should become 1 as soon as its array and vertex_ids_sorted are allocated.
     */
    #define FLAG_PATH_ALLOCATED (uint64_t)(1 << 5)

    /**
     * @def FLAG_PATH_TYPE_C
     *   This flag should become 1 as soon as the first and the last vertices are the same.
     */
    #define FLAG_PATH_TYPE_C (uint64_t)(1 << 6)

    /**
     * @def FLAG_PATH_AS_NOT_SIMPLE
     *   Notice that a non-simple path can never be a prime path.
     */
    #define FLAG_PATH_AS_NOT_SIMPLE(path)   path->flags &= ~(FLAG_PATH_SIMPLE | FLAG_PATH_PRIME)

    /**
     * @def FLAG_PATH_AS_PRIME
     *   Notice that every prime path is also a simple path.
     */
    #define FLAG_PATH_AS_PRIME(path)        path->flags |= (FLAG_PATH_SIMPLE | FLAG_PATH_PRIME)

    /**
     * @def FLAG_PATH_AS_SIMPLE
     *   Flags the path as simple.
     */
    #define FLAG_PATH_AS_SIMPLE(path)       path->flags |= (FLAG_PATH_SIMPLE)

    /**
     * @def FLAG_PATH_AS_ALLOCATED
     *   Flags the path as allocated.
     */
    #define FLAG_PATH_AS_ALLOCATED(path)    path->flags |= (FLAG_PATH_ALLOCATED)

    /**
     * @def FLAG_PATH_AS_DEALLOCATED
     *   Flags the path as deallocated.
     */
    #define FLAG_PATH_AS_DEALLOCATED(path)  path->flags &= ~(FLAG_PATH_ALLOCATED)

    /**
     * @def FLAG_PATH_AS_TYPE_S
     *   Flags the path as it traverses the starting vertex.
     */
    #define FLAG_PATH_AS_TYPE_S(path)       path->flags |= (FLAG_PATH_TYPE_S)

    /**
     * @def FLAG_PATH_AS_TYPE_T
     *   Flags the path as it traverses the terminal vertex.
     */
    #define FLAG_PATH_AS_TYPE_T(path)       path->flags |= (FLAG_PATH_TYPE_T)

    /**
     * @def FLAG_PATH_AS_TYPE_C
     *   Flags the path as it becomes a cycle.
     */
    #define FLAG_PATH_AS_TYPE_C(path)       path->flags |= (FLAG_PATH_TYPE_C)

    /**
     * @def IS_PATH_SIMPLE
     *   This value is 1 if the path is flagged as simple.
     */
    #define IS_PATH_SIMPLE(path)    !!(path->flags & FLAG_PATH_SIMPLE)

    /**
     * @def IS_PATH_PRIME
     *   This value is 1 if the path is flagged as prime.
     */
    #define IS_PATH_PRIME(path)     !!(path->flags & FLAG_PATH_PRIME)

    /**
     * @def IS_PATH_ALLOCATED
     *   This value is 1 if the path is flagged as allocated.
     */
    #define IS_PATH_ALLOCATED(path) !!(path->flags & FLAG_PATH_ALLOCATED)

    /**
     * @def IS_PATH_TYPE_C
     *   This value is 1 if the path is flagged as type_c.
     */
    #define IS_PATH_TYPE_C(path)    !!(path->flags & FLAG_PATH_TYPE_C)

    /**
     * @def IS_PATH_TYPE_S
     *   This value is 1 if the path is flagged as type_s.
     */
    #define IS_PATH_TYPE_S(path)    !!(path->flags & FLAG_PATH_TYPE_S)

    /**
     * @def IS_PATH_TYPE_T
     *   This value is 1 if the path is flagged as type_t.
     */
    #define IS_PATH_TYPE_T(path)    !!(path->flags & FLAG_PATH_TYPE_T)

    /**
     * @def IS_PATH_TYPE_P
     *   This value is 1 if the path is flagged as type_p.
     */
    #define IS_PATH_TYPE_P(path)    !(IS_PATH_TYPE_S(path) || IS_PATH_TYPE_T(path))

    /**
     * @def PATH_DEFAULT_FLAGS
     *   These flags are the default flags for a new path.
     */
    #define PATH_DEFAULT_FLAGS  FLAG_PATH_ALLOCATED

    /**
     * @def PATH_RECOMMENDED_PARAMETERS
     *   These are the <default-parameters> for constructEmpty_path(path, <default-parameters>).
     */
    #define PATH_RECOMMENDED_PARAMETERS     PATH_DEFAULT_INITIAL_CAP, PATH_DEFAULT_FLAGS

    /**
     * @def NOT_A_PATH
     *   A special Path denoting a NOT-Path. This Path cannot pass the isValid_path() test.
     */
    #define NOT_A_PATH                      (Path){ 0, 0, NULL, NULL, 0 }

    /**
     * @struct Path
     * @brief An array of vertex indices.
     *
     * @var Path::cap
     *   The maximum number of vertices the Path can have.
     * @var Path::len
     *   The number of vertices the Path has.
     * @var Path::vertex_ids_sorted
     *   The sorted list of vertex indices, useful when asking if the Path traverses a vertex.
     * @var Path::array
     *   The array of vertex indices.
     * @var Path::flags
     *   Flag bits of the Path.
     */
    typedef struct PathBody {
        uint32_t cap;
        uint32_t len;
        uint32_t* vertex_ids_sorted;
        uint32_t* array;
        uint64_t flags;
    } Path;

    /**
     * @brief Clones a Path.
     *
     * Uses memcpy(), so clone and original should NOT overlap!
     *
     * @param clone The clone Path.
     * @param original The original Path.
     */
    void clone_path(Path* const clone, Path const* const original);

    /**
     * @brief Concatenates two Path objects.
     * @param head A pointer to the head Path.
     * @param tail A pointer to the tail Path.
     */
    void concat_path(Path* const head, Path const* const tail);

    /**
     * @brief Constructs an empty Path (with zero vertices).
     * @param path A pointer to the Path.
     * @param initial_cap The initial capacity of the Path.
     * @param flags The initial flags of the Path.
     */
    void constructEmpty_path(Path* const path, uint32_t const initial_cap, uint64_t const flags);

    /**
     * @brief Checks if a Path contains a vertex index.
     * @param path A pointer to the Path.
     * @param vertex_id The vertex index.
     */
    bool contains_path(Path const* const path, uint32_t const vertex_id);

    /**
     * @brief Dumps a Path to stdout.
     * @param path A pointer to the Path.
     * @param names A pointer to a Chunk holding vertex names.
     */
    void dump_path(Path const* const path, Chunk const* const names);

    /**
     * @brief Extends a Path by appending a vertex index.
     * @param path A pointer to the Path.
     * @param vertex_id The vertex index.
     * @param respectFlags Will prevent path extension if it makes the Path non-simple.
     */
    #define PATH_EXTEND_OK                  0
    #define PATH_EXTEND_MAKES_IT_NON_SIMPLE 1
    int extend_path(Path* const path, uint32_t const vertex_id, bool const respectFlags);

    /**
     * @brief Empties a Path.
     * @param path A pointer to the Path.
     */
    void flush_path(Path* const path);

    /**
     * @brief Frees a Path.
     * @param path A pointer to the Path.
     */
    void free_path(Path* const path);

    /**
     * @brief Invalidates a Path, so isValid_path() returns 0.
     * @param path A pointer to the Path.
     */
    void invalidate_path(Path* const path);

    /**
     * @brief Checks if a Path is valid.
     * @param path A pointer to the Path.
     */
    bool isValid_path(Path const* const path);

    /**
     * @brief Checks if a Path is a sub path of another path.
     * @param sub Candidate sub path.
     * @param super Candidate super path.
     */
    bool isSubPath_path(Path const* const sub, Path const* const super);

    /**
     * @brief Finds the overlap between two paths.
     * @param head The head Path.
     * @param tail The tail Path.
     */
    uint32_t overlap_path(Path const* const head, Path const* const tail);

    /**
     * @brief Finds the hypothetical position index of a vertex if it was added to a Path.
     * @param path A pointer to the Path.
     * @param vertex_id The vertex index.
     */
    uint32_t search_path(Path const* const path, uint32_t const vertex_id);

    /**
     * @struct PathArray
     * @brief An array of Path objects.
     * @see Path
     *
     * @var PathArray::cap
     *   The maximum number of paths the PathArray can have.
     * @var PathArray::size
     *   The number of paths the PathArray has.
     * @var PathArray::array
     *   A pointer to the first Path in the array.
     */
    typedef struct PathArrayBody {
        uint32_t cap;
        uint32_t size;
        Path* array;
    } PathArray;

    /**
     * @brief Combines overlapping paths to reduce the number of paths in a PathArray.
     * @param pathArray A pointer to the PathArray.
     */
    void combineOverlaps_patha(PathArray* const pathArray);

    /**
     * @brief Constructs an empty PathArray.
     * @param pathArray A pointer to the PathArray.
     * @param initial_cap The initial capacity of the PathArray.
     */
    void constructEmpty_patha(PathArray* const pathArray, uint32_t const initial_cap);

    /**
     * @brief Dumps a PathArray to stdout.
     * @param pathArray A pointer to the PathArray.
     * @param names A pointer to a Chunk holding vertex names.
     */
    void dump_patha(PathArray const* const pathArray, Chunk const* const names);

    /**
     * @brief Eliminates all sub paths in a PathArray.
     * @param pathArray A pointer to the PathArray.
     */
    void eliminateSubPaths_patha(PathArray* const pathArray);

    /**
     * @brief Empties a PathArray.
     * @param pathArray A pointer to the PathArray.
     */
    void flush_patha(PathArray* const pathArray);

    /**
     * @brief Frees a PathArray.
     * @param pathArray A pointer to the PathArray.
     */
    void free_patha(PathArray* const pathArray);

    /**
     * @brief Checks if a PathArray is valid.
     * @param pathArray A pointer to the PathArray.
     */
    bool isValid_patha(PathArray const* const pathArray);
#endif
