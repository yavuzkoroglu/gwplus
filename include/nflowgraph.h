7/**
 * @file nflowgraph.h
 * @brief Defines NetworkFlowTransition, NetworkFlowGraph, and related functions.
 * @author Yavuz Koroglu
 */
#ifndef NFLOWGRAPH_H
    #define NFLOWGRAPH_H
    #include "vpatharray.h"

    /**
     * @struct NetworkFlowTransition
     * @brief A NetworkFlowTransition consists four values that enable or disable the transition in a NetworkFlowGraph.
     *
     * @var NetworkFlowTransition::capacity
     *    The amount of flow cannot exceed this capacity.
     * @var NetworkFlowTransition::flow
     *    A value between the lowerBound and capacity, inclusive.
     * @var NetworkFlowTransition::lowerBound
     *    The amount of flow cannot be lower than this.
     * @var NetworkFlowTransition::residualCapacity
     *    The remaining capacity which the flow does not utilize (negative value means the flow must utilize some capacity).
     */
    typedef struct NetworkFlowEdgeBody {
        uint32_t capacity;
        uint32_t flow;
        uint32_t lowerBound;
        int32_t residualCapacity;
    } NetworkFlowTransition;

    /**
     * @struct NetworkFlowGraph
     * @brief A NetworkFlowGraph solves the node coverage problem.
     *
     * @var NetworkFlowGraph::acyclicGraph
     *    The underlying SimpleGraph must be acyclic.
     * @var NetworkFlowGraph::forwardTransitionMtx
     *    A 2-D NetworkFlowTransition matrix representing forward-flow.
     * @var NetworkFlowGraph::backwardTransitionMtx
     *    A 2-D NetworkFlowTransition matrix representing backward-flow.
     */
    typedef struct NetworkFlowGraphBody {
        SimpleGraph const*      acyclicGraph;
        uint32_t                countVertices;
        uint32_t                size;
        uint32_t*               originalVertexIds;
        uint32_t*               vertexIds;
        NetworkFlowTransition** transitionMtx;
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
    #define NOT_AN_NFG ((NetworkFlowGraph){ NULL, NULL, NULL })

    /**
     * @def NOT_AN_NFT
     *   A special NetworkFlowTransition which cannot pass the isValid_nft() test.
     */
    #define NOT_AN_NFT ((NetworkFlowTransition){ 0, 0, 0, 0 })

    /**
     * @brief Constructs a NetworkFlowGraph from an acyclic SimpleGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param acyclicGraph A pointer to the constant acyclic SimpleGraph.
     */
    void construct_nfg(NetworkFlowGraph* const nfg, SimpleGraph const* const acyclicGraph);

    /**
     * @brief Constructs a SimpleGraph from a NetworkFlowGraph.
     * @param graph A pointer to the SimpleGraph.
     * @param nfg A pointer to the constant NetworkFlowGraph.
     */
    void construct_sgi_nfg(SimpleGraph* const graph, NetworkFlowGraph const* const nfg);

    /**
     * @brief Constructs a flow stack that satisfies the flow of a NetworkFlowGraph.
     * @param stack A pointer to the flow stack.
     * @param nfg A pointer to the constant NetworkFlowGraph.
     */
    void constructFlowStack_nfg(VertexPathArray* const stack, NetworkFlowGraph const* const nfg);

    /**
     * @brief Constructs a VertexPathArray that satisfies the flow of a NetworkFlowGraph.
     * @param paths A pointer to the VertexPathArray.
     * @param nfg A pointer to the constant NetworkFlowGraph.
     */
    void constructPaths_nfg(VertexPathArray* const paths, NetworkFlowGraph const* const nfg);

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
     * @param nfg A pointer to the NetworkFlowGraph.
     */
    void free_nfg(NetworkFlowGraph* const nfg);

    /**
     * @brief Checks if a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     */
    bool isValid_nfg(void const* const graphPtr);

    /**
     * @brief Checks if a NetworkFlowTransition is valid.
     * @param transition A pointer to the constant NetworkFlowTransition.
     */
    bool isValid_nft(NetworkFlowTransition const* const transition);

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
     * @brief Checks if a NetworkFlowTransition is valid backward transition.
     * @param transition A pointer to the constant NetworkFlowTransition.
     */
    bool isValidBackward_nft(NetworkFlowTransition const* const transition);

    /**
     * @brief Checks if an edge of a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    bool isValidEdge_nfg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Checks if a NetworkFlowTransition is valid forward transition.
     * @param transition A pointer to the constant NetworkFlowTransition.
     */
    bool isValidForward_nft(NetworkFlowTransition const* const transition);

    /**
     * @brief Checks if a vertex of a NetworkFlowGraph is valid.
     * @param graphPtr A pointer to the constant NetworkFlowGraph.
     * @param vertexId The vertex index.
     */
    bool isValidVertex_nfg(void const* const graphPtr, uint32_t const vertexId);

    /**
     * @brief Optimizes individual flows to minimize the total flow of a NetworkFlowGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     */
    void minimizeTotalFlow_nfg(NetworkFlowGraph* const nfg);

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
#endif
