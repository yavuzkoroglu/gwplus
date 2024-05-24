/**
 * @file nflowgraph.h
 * @brief Defines NetworkFlowTransition, NetworkFlowGraph, and related functions.
 * @author Yavuz Koroglu
 */
#ifndef NFLOWGRAPH_H
    #define NFLOWGRAPH_H
    #include "vpatharray.h"

    /**
     * @struct NetworkFlowGraph
     * @brief A minimum network flow ensures the minimum number of test paths (restarts).
     *
     * @var NetworkFlowGraph::acyclicGraph
     *    The underlying SimpleGraph must be acyclic.
     * @var NetworkFlowGraph::countVertices
     *    The number of unique vertices in the NetworkFlowGraph.
     * @var NetworkFlowGraph::size
     *    The number of all vertices including PLUS duplicates.
     * @var NetworkFlowGraph::largestOriginalId
     *    The largest original vertex index represented in the NetworkFlowGraph.
     * @var NetworkFlowGraph::originalVertexIds
     *    A pointer to the first original vertex index in an array of original vertex indices.
     * @var NetworkFlowGraph::vertexIds
     *    A pointer to the array of NetworkFlowGraph vertex indices.
     * @var NetworkFlowGraph::adjMtx
     *    A pointer to the first row of an adjacency matrix.
     */
    typedef struct NetworkFlowGraphBody {
        SimpleGraph const*  acyclicGraph;
        uint32_t            countVertices;
        uint32_t            size;
        uint32_t            largestOriginalId;
        uint32_t*           originalVertexIds;
        uint32_t*           vertexIds;
        uint32_t**          flowMtx;
        bool**              adjMtx;
    } NetworkFlowGraph;

    /**
     * @def NFG_IS_MINUS
     *   A Boolean expression checking if a vertex is not a vertex plus.
     */
    #define NFG_IS_MINUS(nfg, v)        (v < nfg->countVertices)

    /**
     * @def NFG_IS_PLUS
     *   A Boolean expression checking if a vertex is a vertex plus.
     */
    #define NFG_IS_PLUS(nfg, v)         (v >= nfg->countVertices)

    /**
     * @def NFG_START_VERTEX
     *   The vertex index of s is always zero.
     */
    #define NFG_START_VERTEX(nfg)       0

    /**
     * @def NFG_TERMINAL_VERTEX
     *   We define t as the vertex+ of s.
     */
    #define NFG_TERMINAL_VERTEX(nfg)    NFG_VERTEX_PLUS(nfg, NFG_START_VERTEX(0))

    /**
     * @def NFG_VERTEX_MINUS
     *   In a NetworkFlowGraph, every vertex of the acyclicGraph is represented by a vertex, and a vertex+.
     */
    #define NFG_VERTEX_MINUS(nfg, vp)   vp - nfg->countVertices

    /**
     * @def NFG_VERTEX_PLUS
     *   In a NetworkFlowGraph, every vertex of the acyclicGraph is represented by a vertex, and a vertex+.
     */
    #define NFG_VERTEX_PLUS(nfg, v)     v + nfg->countVertices

    /**
     * @def NOT_AN_NFG
     *   A special NetworkFlowGraph that cannot pass the isValid_nfg() test.
     */
    #define NOT_AN_NFG ((NetworkFlowGraph){ NULL, 0, 0, 0, NULL, NULL, NULL, NULL })

    /**
     * @brief Computes the total outgoing flow from a vertex of a NetworkFlowGraph.
     * @param flowGraph A pointer to the constant SGI of a NetworkFlowGraph.
     * @param v The vertex index.
     */
    uint32_t computeTotalFlow_nfg(SimpleGraph const* const flowGraph, uint32_t const v);

    /**
     * @brief Constructs a NetworkFlowGraph from an acyclic SimpleGraph.
     * @param flowGraph A pointer to the SGI of the NetworkFlowGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param acyclicGraph A pointer to the constant acyclic SimpleGraph.
     */
    void construct_nfg(SimpleGraph* const flowGraph, NetworkFlowGraph* const nfg, SimpleGraph const* const acyclicGraph);

    /**
     * @brief Constructs a SimpleGraph from a NetworkFlowGraph.
     * @param graph A pointer to the SimpleGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     */
    void construct_sgi_nfg(SimpleGraph* const graph, NetworkFlowGraph* const nfg);

    /**
     * @brief Constructs a clone of a NetworkFlowGraph.
     * @param cloneGraph A pointer to the SGI of the clone.
     * @param clone A pointer to the clone NetworkFlowGraph.
     * @param flowGraph A pointer to the constant SGI of the NetworkFlowGraph.
     */
    void constructClone_nfg(SimpleGraph* const cloneGraph, NetworkFlowGraph* const clone, SimpleGraph const* const flowGraph);

    /**
     * @brief (SGI-compatible) Counts the edges of a NetworkFlowGraph.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     */
    uint32_t countEdges_nfg(void const* const graphPtr);

    /**
     * @brief (SGI-compatible) Counts the vertices of a NetworkFlowGraph.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     */
    uint32_t countVertices_nfg(void const* const graphPtr);

    /**
     * @brief Decrements flow from one vertex to another by some amount.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param from The source vertex index.
     * @param to The target vertex index.
     * @param amount The decrement amount.
     */
    void decrementFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount);

    /**
     * @brief (SGI-compatible) Dumps a NetworkFlowGraph to an output FILE.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_nfg(void const* const graphPtr, FILE* const output);

    /**
     * @brief (SGI-compatible) Dumps one vertex of a NetworkFlowGraph to an output FILE.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The vertex index.
     */
    void dumpVertex_nfg(void const* const graphPtr, FILE* const output, uint32_t const vertexId);

    /**
     * @brief Frees a NetworkFlowGraph.
     * @param graphPtr A pointer to the NetworkFlowGraph.
     */
    void free_nfg(void* const graphPtr);

    /**
     * @brief Returns the highest vertex index of a NetworkFlowGraph.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     */
    uint32_t highestVertexId_nfg(void const* const graphPtr);

    /**
     * @brief Increments flow from one vertex to another by some amount.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param from The source vertex index.
     * @param to The target vertex index.
     * @param amount The increment amount.
     */
    void incrementFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount);

    /**
     * @brief Checks if a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     */
    bool isValid_nfg(void const* const graphPtr);

    /**
     * @brief Checks if a NeighborIterator for a NetworkFlowGraph is valid.
     * @param itr A pointer to the constant NeighborIterator.
     */
    bool isValid_nitr_nfg(NeighborIterator const* const itr);

    /**
     * @brief Checks if a StartVertexIterator for a NetworkFlowGraph is valid.
     * @param itr A pointer to the constant StartVertexIterator.
     */
    bool isValid_svitr_nfg(StartVertexIterator const* const itr);

    /**
     * @brief Checks if a VertexIterator for a NetworkFlowGraph is valid.
     * @param itr A pointer to the constant VertexIterator.
     */
    bool isValid_vitr_nfg(VertexIterator const* const itr);

    /**
     * @brief Checks if an edge of a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    bool isValidEdge_nfg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Checks if a vertex of a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param vertexId The vertex index.
     */
    bool isValidVertex_nfg(void const* const graphPtr, uint32_t const vertexId);

    /**
     * @brief Minimizes the total flow of a NetworkFlowGraph.
     * @param flowGraph A pointer to the constant SimpleGraph representation of the NetworkFlowGraph.
     */
    void minimizeTotalFlow_nfg(SimpleGraph const* const flowGraph);

    /**
     * @brief Iterates a NeighborIterator for a NetworkFlowGraph.
     * @param itr A pointer to the NeighborIterator.
     */
    uint32_t nextVertexId_nitr_nfg(NeighborIterator* const itr);

    /**
     * @brief Iterates a StartVertexIterator for a NetworkFlowGraph.
     * @param itr A pointer to the StartVertexIterator.
     */
    uint32_t nextVertexId_svitr_nfg(StartVertexIterator* const itr);

    /**
     * @brief Iterates a VertexIterator for a NetworkFlowGraph.
     * @param itr A pointer to the VertexIterator.
     */
    uint32_t nextVertexId_vitr_nfg(VertexIterator* const itr);

    /**
     * @brief Initializes a NeighborIterator for a NetworkFlowGraph.
     * @param itr A pointer to the NeighborIterator.
     */
    void setFirstNextId_nitr_nfg(NeighborIterator* const itr);

    /**
     * @brief Initializes a StartVertexIterator for a NetworkFlowGraph.
     * @param itr A pointer to the StartVertexIterator.
     */
    void setFirstNextId_svitr_nfg(StartVertexIterator* const itr);

    /**
     * @brief Initializes a VertexIterator for a NetworkFlowGraph.
     * @param itr A pointer to the VertexIterator.
     */
    void setFirstNextId_vitr_nfg(VertexIterator* const itr);

    /**
     * @brief Sets flow from one vertex to another to a given amount.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param from The source vertex index.
     * @param to The target vertex index.
     * @param amount The flow amount.
     */
    void setFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount);
#endif
