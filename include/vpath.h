/**
 * @file vpath.h
 * @brief Defines a SGI-compatible vertex path.
 * @see tgi.h
 * @author Yavuz Koroglu
 */
#ifndef VPATH_H
    #define VPATH_H
    #include "sgi.h"

    /**
     * @struct VertexPath
     * @brief A VertexPath is an array of vertices, where every two consecutive vertices are neighbors in a SimpleGraph.
     *
     * @var VertexPath::graph
     *   A pointer to the constant SimpleGraph.
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
        SimpleGraph const*  graph;
        uint64_t            isAllocated :1;
        uint64_t            isSimple    :1;
        uint64_t            isCycle     :1;
        uint64_t            isPrime     :1;
        uint64_t            _moreFlags  :60;
        uint32_t            cap;
        uint32_t            len;
        uint32_t*           sorted;
        uint32_t*           array;
    } VertexPath;

    /**
     * @def NOT_A_VPATH
     *   A special VertexPath denoting a NOT-VertexPath. This VertexPath cannot pass the isValid_vpath test.
     */
    #define NOT_A_VPATH ((VertexPath){ NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL })

    /**
     * @brief Checks if a VertexPath can rotate.
     * @param vpath A pointer to the VertexPath.
     */
    bool canRotate_vpath(VertexPath* const vpath);

    /**
     * @brief Clones a VertexPath.
     * @param clone A pointer to the clone VertexPath.
     * @param original A pointer to the original VertexPath.
     */
    void clone_vpath(VertexPath* const clone, VertexPath const* const original);

    /**
     * @brief Computes and caches the shortest path between two vertices. If these vertices are the same, the shortest path is empty.
     * @param shortestPath A pointer to the shortestPath.
     * @param graph A pointer to the SimpleGraph.
     * @param from The vertex index of the source vertex.
     * @param to The vertex index of the target vertex.
     */
    bool cacheComputeShortest_vpath(VertexPath* const shortestPath, SimpleGraph const* const graph, uint32_t const from, uint32_t const to);

    /**
     * @brief Computes the shortest path between two vertices. If these vertices are the same, the shortest path is empty.
     * @param shortestPath A pointer to the shortestPath.
     * @param graph A pointer to the constant SimpleGraph.
     * @param from The vertex index of the source vertex.
     * @param to The vertex index of the target vertex.
     */
    bool computeShortest_vpath(VertexPath* const shortestPath, SimpleGraph const* const graph, uint32_t const from, uint32_t const to);

    /**
     * @brief Computes the shortest path between two vertices, while avoiding another vertex.
     * @param shortestPath A pointer to the shortestPath.
     * @param graph A pointer to the constant SimpleGraph.
     * @param from The vertex index of the source vertex.
     * @param to The vertex index of the target vertex.
     * @param n The number of vertices to avoid.
     */
    bool computeShortestAvoidVertices_vpath(
        VertexPath* const shortestPath, SimpleGraph const* const graph,
        uint32_t const from, uint32_t const to,
        size_t const n, ...
    );

    /**
     * @brief Computes the shortest path between two vertices, while avoiding all the vertices of another path.
     * @param shortestPath A pointer to the shortestPath.
     * @param graph A pointer to the constant SimpleGraph.
     * @param from The vertex index of the source vertex.
     * @param to The vertex index of the target vertex.
     * @param avoid A pointer to the constant VertexPath to avoid.
     */
    bool computeShortestAvoidPath_vpath(
        VertexPath* const shortestPath, SimpleGraph const* const graph,
        uint32_t const from, uint32_t const to,
        VertexPath const* const avoid
    );

    /**
     * @brief Computes a shortest cycle in a SimpleGraph (but does NOT complete the cycle).
     * @param cycle A pointer to the cycle.
     * @param graph A pointer to the SimpleGraph.
     */
    bool computeShortestCycle_vpath(VertexPath* const cycle, SimpleGraph const* const graph);

    /**
     * @brief Computes a shortest cycle in a SimpleGraph starting from a given vertex.
     * @param cycle A pointer to the cycle.
     * @param graph A pointer to the SimpleGraph.
     * @param pivot The vertex index of the first vertex in the cycle.
     */
    bool computeShortestCyclePivot_vpath(VertexPath* const cycle, SimpleGraph const* const graph, uint32_t const pivot);

    /**
     * @brief Computes the shortest path from any start vertex to target. If target is a start vertex, the initializer is empty.
     * @param initializer A pointer to the initializer path.
     * @param graph A pointer to the SimpleGraph.
     * @param target The vertex index of the target vertex.
     */
    bool computeShortestInitializer_vpath(VertexPath* const initializer, SimpleGraph const* const graph, uint32_t const target);

    /**
     * @brief Concatenates two paths. The first vertex of the tail must be a neighbor of the last vertex of the head.
     * @param head The first VertexPath.
     * @param tail The second VertexPath.
     */
    void concat_vpath(VertexPath* const head, VertexPath const* const tail);

    /**
     * @brief Constructs an empty VertexPath under a SimpleGraph.
     * @param vpath A pointer to the VertexPath.
     * @param graph A pointer to the SimpleGraph.
     */
    void constructEmpty_vpath(VertexPath* const vpath, SimpleGraph const* const graph);

    /**
     * @brief Constructs an empty VertexPath under a SimpleGraph with an arbitrary initial capacity.
     * @param vpath A pointer to the VertexPath.
     * @param graph A pointer to the SimpleGraph.
     * @param initialCap The initial capacity.
     */
    void constructEmptyCapped_vpath(VertexPath* const vpath, SimpleGraph const* const graph, uint32_t const initialCap);

    /**
     * @brief Checks if a VertexPath contains a vertex.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     */
    bool contains_vpath(VertexPath const* const vpath, uint32_t const vertexId);

    /**
     * @brief Checks if a VertexPath contains a vertex twice.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     */
    bool containsTwice_vpath(VertexPath const* const vpath, uint32_t const vertexId);

    /**
     * @brief Counts the number of times a path is covered by another.
     * @param covered The covered path.
     * @param cover The cover path.
     */
    uint32_t countCoverTimes_vpath(VertexPath const* const covered, VertexPath const* const cover);

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
     * @brief Finds the largest overlap between two vertex paths and returns the overlap length.
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
     * @brief Frees static caches if they are allocated for performance.
     */
    void freeStaticCaches_vpath(void);

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
     * @brief If a VertexPath's last and first vertices form a valid edge, rotating the path is possible
     * @param vpath A pointer to the VertexPath.
     */
    bool rotate_vpath(VertexPath* const vpath);

    /**
     * @brief Performs a rightmorst binary search on a VertexPath and returns the hypothetical sorted position of a vertex index.
     * @param vpath A pointer to the VertexPath.
     * @param vertexId The vertex index.
     */
    uint32_t search_vpath(VertexPath const* const vpath, uint32_t const vertexId);

    /**
     * @brief Splices a tail VertexPath onto a head VertexPath.
     * @param head A pointer to the head VertexPath.
     * @param tail A pointer to the tail VertexPath.
     */
    bool splice_vpath(VertexPath* const head, VertexPath const* const tail);

    /**
     * @brief A VertexPath subsumes another if it traverses every vertex of that VertexPath.
     * @param subsumer A pointer to the subsumer VertexPath.
     * @param subsumed A pointer to the subsumed VertexPath.
     */
    bool subsumes_vpath(VertexPath const* const subsumer, VertexPath const* const subsumed);
#endif
