/**
 * @file vpath.h
 * @brief Defines a TGI-compatible vertex path.
 * @see tgi.h
 * @author Yavuz Koroglu
 */
#ifndef VPATH_H
    #define VPATH_H
    #include "tgi.h"

    /**
     * @struct VertexPath
     * @brief A VertexPath is an array of vertices, where every two consecutive vertices are neighbors in a TestableGraph.
     *
     * @var VertexPath::graph
     *   A pointer to the constant TestableGraph.
     * @var VertexPath::isAllocated
     *   A VertexPath is allocated if and only if it uses some heap memory.
     * @var VertexPath::isSimple
     *   A VertexPath is simple if and only if none of its strict sub paths are cycles.
     * @var VertexPath::isCycle
     *   A VertexPath is a cycle if and only if its first and last vertices are the same.
     * @var VertexPath::isPrime
     *   A VertexPath is prime if and only if it is simple and not a strict sub path of any other simple path.
     * @var VertexPath::_moreFlags
     *   We have space for more flags, if needed.
     * @var VertexPath::len
     *   The total number of vertices in the VertexPath.
     * @var VertexPath::cap
     *   The maximum number of vertices the VertexPath can hold.
     * @var VertexPath::sorted
     *   The array of vertex indices, sorted by their index values.
     * @var VertexPath::array
     *   The path as an array of vertex indices.
     */
    typedef struct VertexPathBody {
        TestableGraph const*    graph;
        uint64_t                isAllocated :1;
        uint64_t                isSimple    :1;
        uint64_t                isCycle     :1;
        uint64_t                isPrime     :1;
        uint64_t                _moreFlags  :60;
        uint32_t                len;
        uint32_t                cap;
        uint32_t*               sorted;
        uint32_t*               array;
    } VertexPath;

    /**
     * @def NOT_A_VPATH
     *   A special VertexPath denoting a NOT-VertexPath. This VertexPath cannot pass the isValid_vpath test.
     */
    #define NOT_A_VPATH ((VertexPath){ NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL })

    /**
     * @brief Clones a VertexPath.
     * @param clone A pointer to the clone VertexPath.
     * @param original A pointer to the original VertexPath.
     */
    void clone_vpath(VertexPath* const clone, VertexPath const* const original);

    /**
     * @brief Computes the shortest path between two vertices. If these vertices are the same, the shortest path is empty.
     * @param shortestPath A pointer to the shortestPath.
     * @param graph A pointer to the TestableGraph.
     * @param from The vertex index of the source vertex.
     * @param to The vertex index of the target vertex.
     */
    bool computeShortest_vpath(VertexPath* const shortestPath, TestableGraph const* const graph, uint32_t const from, uint32_t const to);

    /**
     * @brief Concatenates two paths. The first vertex of the tail must be a neighbor of the last vertex of the head.
     * @param head The first VertexPath.
     * @param tail The second VertexPath.
     */
    void concat_vpath(VertexPath* const head, VertexPath const* const tail);

    /**
     * @brief Constructs an empty VertexPath under a TestableGraph.
     * @param vpath A pointer to the VertexPath.
     * @param graph A pointer to the TestableGraph.
     */
    void constructEmpty_vpath(VertexPath* const vpath, TestableGraph const* const graph);

    /**
     * @brief Checks if a VertexPath contains a vertex.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     */
    bool contains_vpath(VertexPath const* const vpath, uint32_t const vertexId);

    /**
     * @brief Dumps a VertexPath.
     * @param vpath A pointer to the VertexPath.
     * @param output A pointer to the output FILE.
     */
    void dump_vpath(VertexPath const* const vpath, FILE* const output);

    /**
     * @brief Attempts to extend a VertexPath with a vertex.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     * @param preserveSimplicity If this is 1, the implementation won't allow extensions that make the VertexPath non-simple.
     */
    bool extend_vpath(VertexPath* const vpath, uint32_t const vertexId, bool const preserveSimplicity);

    /**
     * @brief Finds the largest overlap between two vertex paths and returns the starting position of the overlap.
     * @param head The first VertexPath.
     * @param tail The second VertexPath.
     */
    uint32_t findLargestOverlap_vpath(VertexPath const* const head, VertexPath const* const tail);

    /**
     * @brief Flushes a VertexPath. Makes an invalidated VertexPath valid again.
     * @param vpath A pointer to the VertexPath.
     */
    void flush_vpath(VertexPath* const vpath);

    /**
     * @brief Frees a VertexPath.
     * @param vpath A pointer to the VertexPath.
     */
    void free_vpath(VertexPath* const vpath);

    /**
     * @brief Increases the capacity of a VertexPath if it is necessary.
     * @param vpath A pointer to the VertexPath.
     */
    void increaseCapIfNecessary_vpath(VertexPath* const vpath);

    /**
     * @brief Invalidates a VertexPath by assigning an invalid value to its length.
     * @param vpath A pointer to the VertexPath.
     */
    void invalidate_vpath(VertexPath* const vpath);

    /**
     * @brief Checks if the first path is a sub path of the second.
     * @param sub The first path.
     * @param super The second path.
     */
    bool isSubPath_vpath(VertexPath const* const sub, VertexPath const* const super);

    /**
     * @brief Checks if a VertexPath is valid.
     * @param vpath A pointer to the VertexPath.
     */
    bool isValid_vpath(VertexPath const* const vpath);

    /**
     * @brief Performs a rightmorst binary search on a VertexPath and returns the hypothetical sorted position of a vertex index.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     */
    uint32_t search_vpath(VertexPath const* const vpath, uint32_t const vertexId);
#endif