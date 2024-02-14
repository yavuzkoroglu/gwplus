/**
 * @file tgi.h
 * @brief Testable Graph Interface (TGI).
 * @author Yavuz Koroglu
 */
#ifndef TGI_H
    #define TGI_H
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @struct NeighborIterator
     * @brief Iterates through the neighbors of a vertex in a TestableGraph.
     *
     * @var NeighborIterator::graphPtr
     *   A pointer to the constant graph.
     * @var NeighborIterator::vertexId
     *   The source vertex index.
     * @var NeighborIterator::nextNeighborId
     *   The next neighbor vertex index.
     */
    typedef struct NeighborIteratorBody {
        void const* graphPtr;
        uint32_t    vertexId;
        uint32_t    nextNeighborId;
    } NeighborIterator;

    /**
     * @struct VertexIterator
     * @brief Iterates through the vertices of a TestableGraph.
     *
     * @var NeighborIterator::graphPtr
     *   A pointer to the constant graph.
     * @var NeighborIterator::nextVertexId
     *   The next vertex index.
     */
    typedef struct VertexIteratorBody {
        void const* graphPtr;
        uint32_t    nextVertexId;
    } VertexIterator, StartVertexIterator;

    /**
     * @struct TestableGraph
     * @brief A graph is testable if and only if there cannot be more than one edge from any vertex to any vertex.
     *
     * @var TestableGraph::graphPtr
     *   A pointer to the constant graph.
     * @var TestableGraph::countEdges
     *   A function that counts the edges of a graph.
     * @var TestableGraph::countVertices
     *   A function that counts the vertices of a graph.
     * @var TestableGraph::dump
     *   A function that dumps a graph.
     * @var TestableGraph::dumpVertex
     *   A function that dumps a graph's vertex.
     * @var TestableGraph::isValid
     *   A function that checks if a graph is valid.
     * @var TestableGraph::isValid_nitr
     *   A function that checks if a NeighboirIterator is valid.
     * @var TestableGraph::isValid_svitr
     *   A function that checks if a StartVertexIterator is valid.
     * @var TestableGraph::isValid_vitr
     *   A function that checks if a VertexIterator is valid.
     * @var TestableGraph::isValidVertex
     *   A function that checks if a graph's vertex is valid.
     * @var TestableGraph::nextVertexId_nitr
     *   A function that iterates towards the next vertex index of a NeighborIterator.
     * @var TestableGraph::nextVertexId_svitr
     *   A function that iterates towards the next vertex index of a StartVertexIterator.
     * @var TestableGraph::nextVertexId_vitr
     *   A function that iterates towards the next vertex index of a VertexIterator.
     * @var TestableGraph::setFirstNextId_nitr
     *   A function that sets the first vertex index of a NeighborIterator.
     * @var TestableGraph::setFirstNextId_svitr
     *   A function that sets the first vertex index of a StartVertexIterator.
     * @var TestableGraph::setFirstNextId_vitr
     *   A function that sets the first vertex index of a VertexIterator.
     */
    typedef struct TestableGraphInterface {
        void const* graphPtr;
        uint32_t    (*countEdges)           (void const* const graphPtr);
        uint32_t    (*countVertices)        (void const* const graphPtr);
        void        (*dump)                 (void const* const graphPtr, FILE* const output);
        void        (*dumpVertex)           (void const* const graphPtr, FILE* const output, uint32_t const vertexId);
        bool        (*isValid)              (void const* const graphPtr);
        bool        (*isValid_nitr)         (NeighborIterator const* const itr);
        bool        (*isValid_svitr)        (StartVertexIterator const* const itr);
        bool        (*isValid_vitr)         (VertexIterator const* const itr);
        bool        (*isValidVertex)        (void const* const graphPtr, uint32_t const vertexId);
        uint32_t    (*nextVertexId_nitr)    (NeighborIterator* const itr);
        uint32_t    (*nextVertexId_svitr)   (StartVertexIterator* const itr);
        uint32_t    (*nextVertexId_vitr)    (VertexIterator* const itr);
        void        (*setFirstNextId_nitr)  (NeighborIterator* const itr);
        void        (*setFirstNextId_svitr) (StartVertexIterator* const itr);
        void        (*setFirstNextId_vitr)  (VertexIterator* const itr);
   } TestableGraph;

    /**
     * @brief Checks if two vertices are neighbors in a TestableGraph.
     * @param graph A pointer to the constant TestableGraph.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    bool areNeighbors_tg(TestableGraph const* const graph, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Constructs a NeighborIterator for a vertex in a TestableGraph.
     * @param itr A pointer to the NeighborIterator.
     * @param graph A pointer to the constant TestableGraph.
     * @param sourceVertexId The source vertex index.
     */
    void construct_nitr_tg(NeighborIterator* const itr, TestableGraph const* const graph, uint32_t const sourceVertexId);

    /**
     * @brief Constructs a StartVertexIterator for a TestableGraph.
     * @param itr A pointer to the StartVertexIterator.
     * @param graph A pointer to the constant TestableGraph.
     */
    void construct_svitr_tg(StartVertexIterator* const itr, TestableGraph const* const graph);

    /**
     * @brief Constructs a VertexIterator for a TestableGraph.
     * @param itr A pointer to the VertexIterator.
     * @param graph A pointer to the constant TestableGraph.
     */
    void construct_vitr_tg(VertexIterator* const itr, TestableGraph const* const graph);

    /**
     * @brief Counts the total number of edges in a TestableGraph.
     * @param graph A pointer to the constant TestableGraph.
     */
    uint32_t countEdges_tg(TestableGraph const* const graph);

    /**
     * @brief Counts the total number of vertices in a TestableGraph.
     * @param graph A pointer to the constant TestableGraph.
     */
    uint32_t countVertices_tg(TestableGraph const* const graph);

    /**
     * @brief Dumps a TestableGraph.
     * @param graph A pointer to the constant TestableGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_tg(TestableGraph const* const graph, FILE* const output);

    /**
     * @brief Dumps one vertex of a TestableGraph.
     * @param graph A pointer to the constant TestableGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The vertex index.
     */
    void dumpVertex_tg(TestableGraph const* const graph, FILE* const output, uint32_t const vertexId);

    /**
     * @brief Checks if a TestableGraph is valid.
     * @param graph A pointer to the constant TestableGraph.
     */
    bool isValid_tg(TestableGraph const* const graph);

    /**
     * @brief Checks if a TestableGraph vertex is valid.
     * @param graph A pointer to the constant TestableGraph.
     * @param vertexId The vertex index.
     */
    bool isValidVertex_tg(TestableGraph const* const graph, uint32_t const vertexId);
#endif
