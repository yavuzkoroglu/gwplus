/**
 * @file vpathgraph.h
 * @brief Defines SGI-compatible VertexPathGraph and related function.
 * @author Yavuz Koroglu
 */
#ifndef VPATHGRAPH_H
    #define VPATHGRAPH_H
    #include "padkit/graphmatrix.h"
    #include "vpatharray.h"

    /**
     * @struct VertexPathGraph
     * @brief A VertexPathGraph is a directed graph of VertexPath objects where every edge is a splice.
     *
     * @var VertexPathGraph::graph
     *   Every VertexPath must be on the same SimpleGraph.
     * @var VertexPathGraph::vpaths
     *   The constant VertexPathArray.
     * @var VertexPathGraph::spliceMtx
     *   The splice matrix.
     */
    typedef struct VertexPathGraphBody {
        SimpleGraph const*      graph;
        VertexPathArray const*  vpaths;
        GraphMatrix             spliceMtx[1];
    } VertexPathGraph;

    /**
     * @def NOT_A_VPATH_GRAPH
     *   A special VertexPathGraph denoting NOT-VertexPathGraph. This graph fails the isValid_vpg() test.
     */
    #define NOT_A_VPATH_GRAPH ((VertexPathGraph){ NULL, NULL, {NOT_A_GRAPH_MATRIX} })

    /**
     * @brief Constructs a VertexPathGraph from a VertexPathArray.
     * @param pathGraph A pointer to the SGI of the VertexPathGraph.
     * @param vpgraph A pointer to the VertexPathGraph.
     * @param graph A pointer to the constant graph the path graph is being constructed from.
     * @param vpaths A pointer to the constant VertexPathArray.
     * @param optimizationLevel Performance optimization level for the path graph generation algorithm.
     */
    void construct_vpg(
        SimpleGraph* const pathGraph, VertexPathGraph* const vpgraph,
        SimpleGraph const* const graph, VertexPathArray const* const vpaths,
        int const optimizationLevel
    );

    /**
     * @brief Constructs a SimpleGraph from a VertexPathGraph. Note that this is a graph of paths.
     * @param graph A pointer to the SimpleGraph.
     * @param vpgraph A pointer to the VertexPathGraph.
     */
    void construct_sgi_vpg(SimpleGraph* const graph, VertexPathGraph* const vpgraph);

    /**
     * @brief Counts the number of edges in a VertexPathGraph.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     */
    uint32_t countEdges_vpg(void const* const graphPtr);

    /**
     * @brief Counts the number of vertices in a VertexPathGraph.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     */
    uint32_t countVertices_vpg(void const* const graphPtr);

    /**
     * @brief Dumps a VertexPathGraph
     * @param graphPtr A pointer to the constant VertexPathGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_vpg(void const* const graphPtr, FILE* const output);

    /**
     * @brief Dumps one VertexPath from a VertexPathGraph.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The VertexPath index.
     */
    void dumpVertex_vpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId);

    /**
     * @brief Frees a VertexPathGraph.
     * @param graphPtr A pointer to the VertexPathGraph.
     */
    void free_vpg(void* const graphPtr);

    /**
     * @brief Returns the highest vertex index in a VertexPathGraph.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     */
    uint32_t highestVertexId_vpg(void const* const graphPtr);

    /**
     * @brief Checks if a VertexPathGraph is valid.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     */
    bool isValid_vpg(void const* const graphPtr);

    /**
     * @brief Checks if a VertexPathGraph's NeighborIterator is valid.
     * @param itr A pointer to the constant NeighborIterator.
     */
    bool isValid_nitr_vpg(NeighborIterator const* const itr);

    /**
     * @brief Checks if a VertexPathGraph's StartVertexIterator is valid.
     * @param itr A pointer to the constant StartVertexIterator.
     */
    bool isValid_svitr_vpg(StartVertexIterator const* const itr);

    /**
     * @brief Checks if a VertexPathGraph's VertexIterator is valid.
     * @param itr A pointer to the constant VertexIterator.
     */
    bool isValid_vitr_vpg(VertexIterator const* const itr);

    /**
     * @brief Checks if two VertexPaths form an edge in a VertexPathGraph.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     * @param sourceVertexId The source VertexPath index.
     * @param targetVertexId The target VertexPath index.
     */
    bool isValidEdge_vpg(void const* const graphPtr, uint32_t sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Checks if a VertexPathGraph's StartVertexIterator is valid.
     * @param graphPtr A pointer to the constant VertexPathGraph.
     * @param vertexId The VertexPath index.
     */
    bool isValidVertex_vpg(void const* const graphPtr, uint32_t const vertexId);

    /**
     * @brief Gets the next vertex from a NeighborIterator.
     * @param itr A pointer to the NeighborIterator.
     */
    uint32_t nextVertexId_nitr_vpg(NeighborIterator* const itr);

    /**
     * @brief Gets the next vertex from a StartVertexIterator.
     * @param itr A pointer to the StartVertexIterator.
     */
    uint32_t nextVertexId_svitr_vpg(StartVertexIterator* const itr);

    /**
     * @brief Gets the next vertex from a VertexIterator.
     * @param itr A pointer to the VertexIterator.
     */
    uint32_t nextVertexId_vitr_vpg(VertexIterator* const itr);

    /**
     * @brief Sets the first neighbor index of a NeighborIterator.
     * @param itr A pointer to the NeighborIterator.
     */
    void setFirstNextId_nitr_vpg(NeighborIterator* const itr);

    /**
     * @brief Sets the first vertex index of a StartVertexIterator.
     * @param itr A pointer to the StartVertexIterator.
     */
    void setFirstNextId_svitr_vpg(StartVertexIterator* const itr);

    /**
     * @brief Sets the first vertex index of a VertexIterator.
     * @param itr A pointer to the VertexIterator.
     */
    void setFirstNextId_vitr_vpg(VertexIterator* const itr);
#endif
