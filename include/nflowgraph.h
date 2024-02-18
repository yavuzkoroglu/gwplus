/**
 * @file nflowgraph.h
 * @brief Defines NetworkFlowTransition, NetworkFlowGraph, and related functions.
 * @author Yavuz Koroglu
 */
#ifndef NFLOWGRAPH_H
    #define NFLOWGRAPH_H
    #include "sgi.h"

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
     *    The remaining capacity which the flow does not utilize.
     */
    typedef struct NetworkFlowEdgeBody {
        uint32_t capacity;
        uint32_t flow;
        uint32_t lowerBound;
        uint32_t residualCapacity;
    } NetworkFlowTransition;

    /**
     * @def NOT_AN_NFT
     *   A special NetworkFlowTransition which cannot pass the isValid_nft() test.
     */
    #define NOT_AN_NFT ((NetworkFlowTransition){ 0, 0, 0, 0 })

    /**
     * @brief Checks if a NetworkFlowTransition is valid.
     * @param transition A pointer to the NetworkFlowTransition.
     */
    bool isValid_nft(NetworkFlowTransition const* const transition);

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
        NetworkFlowTransition** forwardTransitionMtx;
        NetworkFlowTransition** backwardTransitionMtx;
    } NetworkFlowGraph;

    /**
     * @def NOT_AN_NFG
     *   A special NetworkFlowGraph that cannot pass the isValid_nfg() test.
     */
    #define NOT_AN_NFG ((NetworkFlowGraph){ NULL, NULL, NULL })

    /**
     * @brief Constructs a NetworkFlowGraph from an acyclic SimpleGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     * @param acyclicGraph A pointer to the constant acyclic SimpleGraph.
     */
    void construct_nfg(NetworkFlowGraph* const nfg, SimpleGraph const* const acyclicGraph);

    /**
     * @brief Checks if a NetworkFlowGraph is valid.
     * @param nfg A pointer to the NetworkFlowGraph.
     */
    bool isValid_nfg(NetworkFlowGraph const* const nfg);

    /**
     * @brief Frees a NetworkFlowGraph.
     * @param nfg A pointer to the NetworkFlowGraph.
     */
    void free_nfg(NetworkFlowGraph* const nfg);
#endif
