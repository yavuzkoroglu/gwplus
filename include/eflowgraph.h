/**
 * @file eflowgraph.h
 * @brief Defines ExpandedFlowGraph and related functions.
 * @author Yavuz Koroglu
 */
#ifndef EFLOWGRAPH_H
    #define EFLOWGRAPH_H
    #include "vpath.h"
    #include "padkit/graphmatrix.h"

    /**
     * @struct ExpandedFlowGraph
     * @brief A minimum network flow that ensures no test requirement is redundantly covered twice.
     *
     * @var ExpandedFlowGraph::size
     *   The number of hyperpaths, test requirements, and +1 for the start vertex "s".
     * @var ExpandedFlowGraph::s_id
     *   The initial vertex index.
     * @var ExpandedFlowGraph::size_activeVertices
     *   The number of vertices reachable from "s".
     * @var ExpandedFlowGraph::activeVertices
     *   A pointer to the first vertex index in the array of active vertex indices, sorted in ascending order.
     * @var ExpandedFlowGraph::flowMtx
     *   A pointer to the first row of a matrix of flow values between vertices.
     * @var ExpandedFlowGraph::adjMtx
     *   The adjacency matrix.
     */
    typedef struct ExpandedFlowGraphBody {
        uint32_t    size;
        uint32_t    s_id;
        uint32_t    size_activeVertices;
        uint32_t*   activeVertices;
        uint32_t**  flowMtx;
        GraphMatrix adjMtx[1];
    } ExpandedFlowGraph;

    /**
     * @def NOT_AN_EFG
     *   A special ExpandedFlowGraph that cannot pass the isValid_efg() test.
     */
    #define NOT_AN_EFG ((ExpandedFlowGraph){ 0, 0, 0, NULL, NULL, { NOT_A_GRAPH_MATRIX } })

    /**
     * @def EFG_PRIME
     *   Converts a vertex index to its prime vertex, i.e., a hyperpath/test requirement that is about to be covered twice.
     */
    #define EFG_PRIME(efg, v)   (v + (efg->size))

    /**
     * @def EFG_PLUS
     *   Converts a vertex index to its plus vertex, i.e., its duplicate required to perform the minimum flow algorithm.
     */
    #define EFG_PLUS(efg, v)    (v + (efg->size << 1))

    /**
     * @brief Computes an arbitrary feasible flow (not necessarily minimum) for an ExpandedFlowGraph.
     * @param expandedFlowGraph A pointer to the SGI of the ExpandedFlowGraph.
     */
    void computeFeasibleFlow_efg(SimpleGraph* const expandedFlowGraph);

    /**
     * @brief Constructs an ExpandedFlowGraph from a NetworkFlowGraph of a HyperPathGraph.
     * @param expandedFlowGraph A pointer to the SGI of the ExpandedFlowGraph.
     * @param efg A pointer to the ExpandedFlowGraph.
     * @param flowGraph A pointer to the constant SGI of the NetworkFlowGraph.
     * @param hyperPathGraph A pointer to the constant SGI of the HyperPathGraph.
     */
    void construct_efg(
        SimpleGraph* const expandedFlowGraph, ExpandedFlowGraph* const efg,
        SimpleGraph const* const flowGraph, SimpleGraph const* const hyperPathGraph
    );

    /**
     * @brief Generates and consumes one path trace from a test plan.
     * @param pathTrace A pointer to the path trace.
     * @param testPlan A pointer to the SGI of the test plan.
     * @param pathGraph A pointer to the constant SGI of the pathGraph.
     */
    bool consumePathTrace_efg(VertexPath* const pathTrace, SimpleGraph* const testPlan, SimpleGraph const* const pathGraph);

    /**
     * @brief (SGI-compatible) Counts the number of active edges in an ExpandedFlowGraph.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     */
    uint32_t countEdges_efg(void const* const graphPtr);

    /**
     * @brief Counts the number of tests within a test plan.
     * @param testPlan A pointer to the constant SGI of the testPlan.
     */
    uint32_t countTests_efg(SimpleGraph const* const testPlan);

    /**
     * @brief (SGI-compatible) Counts the number of active edges in an ExpandedFlowGraph.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     */
    uint32_t countVertices_efg(void const* const graphPtr);

    /**
     * @brief (SGI-compatible) Dumps an ExpandedFlowGraph to an output FILE.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     * @param output A pointer to the FILE.
     */
    void dump_efg(void const* const graphPtr, FILE* const output);

    /**
     * @brief (SGI-compatible?) Dumps an edge of an ExpandedFlowGraph to an output FILE.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     * @param output A pointer to the FILE.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    void dumpEdge_efg(
        void const* const graphPtr, FILE* const output,
        uint32_t const sourceVertexId, uint32_t const targetVertexId
    );

    /**
     * @brief (SGI-compatible) Dumps a vertex of an ExpandedFlowGraph.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     * @param output A pointer to the FILE.
     * @param vertexId The vertex index.
     */
    void dumpVertex_efg(void const* const graphPtr, FILE* const output, uint32_t const vertexId);

    /**
     * @brief (SGI-compatible) Frees an ExpandedFlowGraph.
     * @param graphPtr A pointer to the ExpandedFlowGraph.
     */
    void free_efg(void* const graphPtr);

    /**
     * @brief Converts a minimized ExpandedFlowGraph into a test plan.
     * @param expandedFlowGraph A pointer to the SGI of the ExpandedFlowGraph.
     */
    void generateTestPlan_efg(SimpleGraph* const expandedFlowGraph);

    /**
     * @brief (SGI-compatible) Returns the highest active vertex index of an ExpandedFlowGraph.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     */
    uint32_t highestVertexId_efg(void const* const graphPtr);

    /**
     * @brief Initializes an infeasible s-t flow with negative values denoting coverage criteria for an ExpandedFlowGraph.
     * @param expandedFlowGraph A pointer to the SGI of the ExpandedFlowGraph.
     */
    void initializeFlow_efg(SimpleGraph* const expandedFlowGraph);

    /**
     * @brief (SGI-compatible) Checks if an ExpandedFlowGraph is valid.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     */
    bool isValid_efg(void const* const graphPtr);

    /**
     * @brief Checks if a NeighborIterator for a ExpandedFlowGraph is valid.
     * @param itr A pointer to the constant NeighborIterator.
     */
    bool isValid_nitr_efg(NeighborIterator const* const itr);

    /**
     * @brief Checks if a StartVertexIterator for a ExpandedFlowGraph is valid.
     * @param itr A pointer to the constant StartVertexIterator.
     */
    bool isValid_svitr_efg(StartVertexIterator const* const itr);

    /**
     * @brief Checks if a VertexIterator for a ExpandedFlowGraph is valid.
     * @param itr A pointer to the constant VertexIterator.
     */
    bool isValid_vitr_efg(VertexIterator const* const itr);

    /**
     * @brief Checks if an edge of an ExpandedFlowGraph is valid.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    bool isValidEdge_efg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Checks if a vertex of a ExpandedFlowGraph is valid.
     * @param graphPtr A pointer to the constant ExpandedFlowGraph.
     * @param vertexId The vertex index.
     */
    bool isValidVertex_efg(void const* const graphPtr, uint32_t const vertexId);

    /**
     * @brief Minimizes a feasible s-t flow in an ExpandedFlowGraph.
     * @param expandedFlowGraph A pointer to the SGI of the ExpandedFlowGraph.
     */
    void minimizeFlow_efg(SimpleGraph* const expandedFlowGraph);

    /**
     * @brief Iterates a NeighborIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the NeighborIterator.
     */
    uint32_t nextVertexId_nitr_efg(NeighborIterator* const itr);

    /**
     * @brief Iterates a StartVertexIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the StartVertexIterator.
     */
    uint32_t nextVertexId_svitr_efg(StartVertexIterator* const itr);

    /**
     * @brief Iterates a VertexIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the VertexIterator.
     */
    uint32_t nextVertexId_vitr_efg(VertexIterator* const itr);

    /**
     * @brief Initializes a NeighborIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the NeighborIterator.
     */
    void setFirstNextId_nitr_efg(NeighborIterator* const itr);

    /**
     * @brief Initializes a StartVertexIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the StartVertexIterator.
     */
    void setFirstNextId_svitr_efg(StartVertexIterator* const itr);

    /**
     * @brief Initializes a VertexIterator for an ExpandedFlowGraph.
     * @param itr A pointer to the VertexIterator.
     */
    void setFirstNextId_vitr_efg(VertexIterator* const itr);
#endif
