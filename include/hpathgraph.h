/**
 * @file hpathgraph.h
 * @brief Defines SGI compatible HyperPath, HyperPathGraph, and related functions.
 * @author Yavuz Koroglu
 */
#ifndef HPGRAPH_H
    #define HPGRAPH_H
    #include "padkit/graphmatrix.h"
    #include "vpathgraph.h"

    /**
     * @struct HyperPathGraph
     * @brief A graph of HyperPath objects.
     *
     * @var HyperPathGraph::graph
     *   A pointer to the constant VertexPathGraph.
     * @var HyperPathGraph::hpaths
     *   A pointer to the first HyperPath in the HyperPathGraph.
     */
    typedef struct HyperPathGraphBody {
        VertexPathGraph const*  vpgraph;
        GraphMatrix             edgeMtx[1];
        uint32_t                cap;
        uint32_t                size;
        /**
         * @struct HyperPath
         * @brief A HyperPath is either one VertexPath or a cycle of HyperPaths.
         *
         * @var HyperPath::pathId
         *   If a HyperPath is just one VertexPath, this is a valid path index.
         * @var HyperPath::parentId
         *   If a parent HyperPath traverses this HyperPath, this is a valied parent index.
         * @var HyperPath::hpath
         *   This is a path of HyperPath indices.
         */
        struct HyperPath {
            uint32_t            pathId;
            uint32_t            parentId;
            VertexPath          hpath[1];
        } *hpaths;
    } HyperPathGraph;

    #define NOT_A_HPATH ((struct HyperPath){ 0xFFFFFFFF, 0xFFFFFFFF, {NOT_A_VPATH} })

    #define NOT_A_HPATH_GRAPH ((HyperPathGraph){ NULL, 0, 0, NULL })

    uint32_t countEdges_hpg(void const* const graphPtr);

    uint32_t countVertices_hpg(void const* const graphPtr);

    void construct_hpg(HyperPathGraph* const hpgraph, VertexPathGraph const* const vpgraph);

    void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph const* const hpgraph);

    void constructAcyclic_hpg(HyperPathGraph* const hpgraph, VertexPathGraph const* const vpgraph);

    void dump_hpg(void const* const graphPtr, FILE* const output);

    void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId);

    void free_hpg(HyperPathGraph* const hpgraph);

    bool generateTestPaths_hpg(VertexPathArray* const testPaths, HyperPathGraph const* const hpgraph);

    bool isValid_hpg(void const* const graphPtr);

    bool isValid_nitr_hpg(NeighborIterator const* const itr);

    bool isValid_svitr_hpg(StartVertexIterator const* const itr);

    bool isValid_vitr_hpg(VertexIterator const* const itr);

    bool isValidVertex_hpg(void const* const graphPtr, uint32_t const vertexId);

    uint32_t nextVertexId_nitr_hpg(NeighborIterator* const itr);

    uint32_t nextVertexId_svitr_hpg(StartVertexIterator* const itr);

    uint32_t nextVertexId_vitr_hpg(VertexIterator* const itr);

    uint32_t setFirstNextId_nitr_hpg(NeighborIterator* const itr);

    uint32_t setFirstNextId_svitr_hpg(StartVertexIterator* const itr);

    uint32_t setFirstNextId_vitr_hpg(VertexIterator* const itr);
#endif
