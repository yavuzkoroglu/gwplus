/**
 * @file vpath.h
 * @brief Defines a TGI-compatible vertex path.
 * @see tgi.h
 * @author Yavuz Koroglu
 */
#ifndef VPATH_H
    #define VPATH_H
    #include "tgi.h"

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

    #define NOT_A_VPATH ((VertexPath){ NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL })

    void clone_vpath(VertexPath* const clone, VertexPath const* const original);

    bool computeShortest_vpath(
        VertexPath* const shortestPath,
        TestableGraph const* const graph,
        uint32_t const from,
        uint32_t const to
    );

    void concat_vpath(VertexPath* const head, VertexPath const* const tail);

    void constructEmpty_vpath(VertexPath* const vpath, TestableGraph const* const graph);

    bool contains_vpath(VertexPath const* const vpath, uint32_t const vertexId);

    void dump_vpath(VertexPath const* const vpath, FILE* const output);

    bool extend_vpath(
        VertexPath* const vpath,
        uint32_t const vertexId,
        bool const preserveSimplicity
    );

    uint32_t findLargestOverlap_vpath(
        VertexPath const* const head,
        VertexPath const* const tail
    );

    void free_vpath(VertexPath* const vpath);

    void flush_vpath(VertexPath* const vpath);

    void increaseCapIfNecessary_vpath(VertexPath* const vpath);

    void invalidate_vpath(VertexPath* const vpath);

    bool isSubPath_vpath(VertexPath const* const sub, VertexPath const* const super);

    bool isValid_vpath(VertexPath const* const vpath);

    uint32_t search_vpath(VertexPath const* const vpath, uint32_t const vertexId);
#endif
