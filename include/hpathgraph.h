/**
 * @file hpathgraph.h
 * @brief Defines SGI compatible HyperPathGraph and related functions.
 * @author Yavuz Koroglu
 */
#ifndef HPGRAPH_H
    #define HPGRAPH_H
    #include "vpathgraph.h"

    /**
     * @struct HyperPathGraph
     * @brief A graph of HyperPath objects.
     *
     * @var HyperPathGraph::pathGraph
     *   A pointer to the constant SGI of a VertexPathGraph.
     * @var HyperPathGraph::hpaths
     *   A pointer to the first hyperpath in the HyperPathGraph.
     * @var HyperPathGraph::edgeMtx
     *   A 2-D adjacency matrix.
     * @var HyperPathGraph::subsumptionMtx
     *   A 1-D matrix marking subsumed hyperpaths.
     */
    typedef struct HyperPathGraphBody {
        SimpleGraph const*      pathGraph;
        VertexPathArray         hpaths[1];
        GraphMatrix             edgeMtx[1];
        GraphMatrix             subsumptionMtx[1];
    } HyperPathGraph;

    /**
     * @def NOT_A_HPATH_GRAPH
     *   A special HyperPathGraph which fails the isValid_hpg() test.
     */
    #define NOT_A_HPATH_GRAPH ((HyperPathGraph){    \
        NULL,                                       \
        {NOT_A_VPATH_ARRAY},                        \
        {NOT_A_GRAPH_MATRIX},                       \
        {NOT_A_GRAPH_MATRIX}                        \
     })

    /**
     * @brief Counts the total number of edges in a HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     */
    uint32_t countEdges_hpg(void const* const graphPtr);

    /**
     * @brief Counts the total number of vertices (hyperpaths) in a HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     */
    uint32_t countVertices_hpg(void const* const graphPtr);

    /**
     * @brief Constructs a HyperPathGraph from a VertexPathGraph.
     * @param hpgraph A pointer to the HyperPathGraph.
     * @param pathGraph A pointer to the constant SGI of a VertexPathGraph.
     */
    void construct_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph);

    /**
     * @brief Constructs a SimpleGraph out of a HyperPathGraph.
     * @param graph A pointer to the SimpleGraph.
     * @param hpgraph A pointer to the constant HyperPathGraph.
     */
    void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph const* const hpgraph);

    /**
     * @brief Constructs an acyclic HyperPathGraph from a SGI-compatible VertexPathGraph.
     * @param hpgraph A pointer to the HyperPathGraph.
     * @param pathGraph A pointer to the constant SGI of a VertexPathGraph.
     */
    void constructAcyclic_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph);

    /**
     * @brief Constructs a path trace from an HyperPath of an HyperPathGraph.
     * @param pathTrace A pointer to the path trace as a VertexPath.
     * @param hpgraph A pointer to the HyperPathGraph (cannot be a constant, subsumptionMtx needs to be disconnected).
     * @param rootId The root hyper path index.
     */
    void constructPathTrace_hpg(VertexPath* const pathTrace, HyperPathGraph* const hpgraph, uint32_t const rootId);

    /**
     * @brief Constructs testpaths from an HyperPathGraph.
     * @param testPaths A pointer to the test paths as a VertexPathArray.
     * @param hpgraph A pointer to the HyperPathGraph.
     */
    void constructTestPaths_hpg(VertexPathArray* const testPaths, HyperPathGraph* const hpgraph);

    /**
     * @brief Dumps an HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_hpg(void const* const graphPtr, FILE* const output);

    /**
     * @brief Dumps one hyperpath of a HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The vertex index of the hyperpath.
     */
    void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId);

    /**
     * @brief Frees a HyperPathGraph.
     * @param hpgraph A pointer to the HyperPathGraph.
     */
    void free_hpg(HyperPathGraph* const hpgraph);

    /**
     * @brief Checks if a HyperPathGraph is valid.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     */
    bool isValid_hpg(void const* const graphPtr);

    /**
     * @brief Checks if a NeighborIterator for a HyperPathGraph is valid.
     * @param itr A pointer to the constant NeighborIterator.
     */
    bool isValid_nitr_hpg(NeighborIterator const* const itr);

    /**
     * @brief Checks if a StartVertexIterator for a HyperPathGraph is valid.
     * @param itr A pointer to the constant StartVertexIterator.
     */
    bool isValid_svitr_hpg(StartVertexIterator const* const itr);

    /**
     * @brief Checks if a VertexIterator for a HyperPathGraph is valid.
     * @param itr A pointer to the constant VertexIterator.
     */
    bool isValid_vitr_hpg(VertexIterator const* const itr);

    /**
     * @brief Checks if two hyperpath indices form a valid edge in a HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     * @param sourceVertexId The vertex index of the source hyperpath.
     * @param targetVertexId The vertex index of the target hyperpath.
     */
    bool isValidEdge_hpg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Checks if a hyperpath index is valid in a HyperPathGraph.
     * @param graphPtr A pointer to the constant HyperPathGraph.
     * @param vertexId The vertex index of the hyperpath.
     */
    bool isValidVertex_hpg(void const* const graphPtr, uint32_t const vertexId);

    /**
     * @brief Gets the next vertex from a NeighborIterator.
     * @param itr A pointer to the NeighborIterator.
     */
    uint32_t nextVertexId_nitr_hpg(NeighborIterator* const itr);

    /**
     * @brief Gets the next vertex from a StartVertexIterator.
     * @param itr A pointer to the StartVertexIterator.
     */
    uint32_t nextVertexId_svitr_hpg(StartVertexIterator* const itr);

    /**
     * @brief Gets the next vertex from a VertexIterator.
     * @param itr A pointer to the VertexIterator.
     */
    uint32_t nextVertexId_vitr_hpg(VertexIterator* const itr);

    /**
     * @brief Sets the first neighbor index of a NeighborIterator.
     * @param itr A pointer to the NeighborIterator.
     */
    void setFirstNextId_nitr_hpg(NeighborIterator* const itr);

    /**
     * @brief Sets the first vertex index of a StartVertexIterator.
     * @param itr A pointer to the StartVertexIterator.
     */
    void setFirstNextId_svitr_hpg(StartVertexIterator* const itr);

    /**
     * @brief Sets the first vertex index of a VertexIterator.
     * @param itr A pointer to the VertexIterator.
     */
    void setFirstNextId_vitr_hpg(VertexIterator* const itr);
#endif
