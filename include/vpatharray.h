/**
 * @file vpatharray.h
 * @brief Defines VPathArray.
 * @author Yavuz Koroglu
 */
#ifndef VPATHARRAY_H
    #define VPATHARRAY_H
    #include "vpath.h"

    /**
     * @struct VertexPathArray
     * @brief An array of VertexPath objects.
     *
     * @var VertexPathArray::cap
     *   The maximum number of VertexPath objects the VertexPathArray can hold.
     * @var VertexPathArray::size
     *   The total number of VertexPath objects residing in the VertexPathArray.
     * @var VertexPathArray::array
     *   A pointer to the first VertexPath in the VertexPathArray.
     */
    typedef struct VertexPathArrayBody {
        uint32_t    cap;
        uint32_t    size;
        VertexPath* array;
    } VertexPathArray;

    /**
     * @def NOT_A_VPATH_ARRAY
     *   A special VertexPathArray denoting a NOT-VertexPathArray. This VertexPathArray cannot pass the isValid_vpa() test.
     */
    #define NOT_A_VPATH_ARRAY ((VertexPathArray){ 0, 0, NULL })

    /**
     * @def VPATH_ARRAY_DEFAULT_INITIAL_CAP
     *   This default initial capacity should work in most situations.
     */
    #define VPATH_ARRAY_DEFAULT_INITIAL_CAP 256

    /**
     * @brief Constructs 1-paths from all the vertices of a SimpleGraph.
     * @param vpaths A pointer to the VertexPathArray.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void constructVerticesAsPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph);

    /**
     * @brief Constructs all paths of a SimpleGraph with path length k.
     * @param vpaths A pointer to the VertexPathArray.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void constructAllKPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph, uint32_t const k);

    /**
     * @brief Constructs a VertexPathArray containing all prime paths of a SimpleGraph.
     * @param primePaths A pointer to the VertexPathArray.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void constructAllPrimePaths_vpa(VertexPathArray* const primePaths, SimpleGraph const* const graph);

    /**
     * @brief Constructs all paths of a SimpleGraph up to path length k, inclusive.
     * @param vpaths A pointer to the VertexPathArray.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void constructAllUpToKPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph, uint32_t const k);

    /**
     * @brief Constructs an empty VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     * @param initial_cap The initial capacity of the VertexPathArray.
     */
    void constructEmpty_vpa(VertexPathArray* const vpaths, uint32_t const initial_cap);

    /**
     * @brief Dumps a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     * @param output A pointer to the output FILE.
     */
    void dump_vpa(VertexPathArray const* const vpaths, FILE* const output);

    /**
     * @brief Eliminates all sub paths in a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     */
    void eliminateSubPaths_vpa(VertexPathArray* const vpaths);

    /**
     * @brief Flushes a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     */
    void flush_vpa(VertexPathArray* const vpaths);

    /**
     * @brief Frees a VertexPathArray and its allocated VertexPath objects.
     * @param vpaths A pointer to the VertexPathArray.
     */
    void free_vpa(VertexPathArray* const vpaths);

    /**
     * @brief Increases the capacity of a VertexPathArray if necessary.
     * @param vpaths A pointer to the VertexPathArray.
     */
    void increaseCapIfNecessary_vpa(VertexPathArray* const vpaths);

    /**
     * @brief Checks if a VertexPathArray is valid.
     * @param vpaths A pointer to the VertexPathArray.
     */
    bool isValid_vpa(VertexPathArray const* const vpaths);

    /**
     * @brief Pops a VertexPath from a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     */
    VertexPath* pop_vpa(VertexPathArray* const vpaths);

    /**
     * @brief Pushes a clone of a VertexPath to a VertexPathArray under the same SimpleGraph.
     * @param vpaths A pointer to the VertexPathArray.
     * @param vpath A pointer to the VertexPath.
     */
    VertexPath* pushClone_vpa(VertexPathArray* const vpaths, VertexPath const* const vpath);

    /**
     * @brief Pushes an empty VertexPath to a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     * @param graph A pointer to the constant SimpleGraph.
     */
    VertexPath* pushEmpty_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph);

    /**
     * @brief Removes a VertexPath from a VertexPathArray.
     * @param vpaths A pointer to the VertexPathArray.
     * @param vpathId The VertexPath index to remove.
     */
    void removePath_vpa(VertexPathArray* const vpaths, uint32_t const vpathId);
#endif
