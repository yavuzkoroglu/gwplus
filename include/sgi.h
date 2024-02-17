/**
 * @file sgi.h
 * @brief Simple Graph Interface (SGI).
 * @author Yavuz Koroglu
 */
#ifndef SGI_H
    #define SGI_H
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @struct NeighborIterator
     * @brief Iterates through the neighbors of a vertex in a SimpleGraph.
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
     * @brief Iterates through the vertices of a SimpleGraph.
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
     * @struct SimpleGraph
     * @brief A graph is simple if and only if there cannot be more than one edge from any vertex to any vertex.
     *
     * @var SimpleGraph::graphPtr
     *   A pointer to the constant graph.
     * @var SimpleGraph::countEdges
     *   A function that counts the edges of a graph.
     * @var SimpleGraph::countVertices
     *   A function that counts the vertices of a graph.
     * @var SimpleGraph::dump
     *   A function that dumps a graph.
     * @var SimpleGraph::dumpVertex
     *   A function that dumps a graph's vertex.
     * @var SimpleGraph::isValid
     *   A function that checks if a graph is valid.
     * @var SimpleGraph::isValid_nitr
     *   A function that checks if a NeighboirIterator is valid.
     * @var SimpleGraph::isValid_svitr
     *   A function that checks if a StartVertexIterator is valid.
     * @var SimpleGraph::isValid_vitr
     *   A function that checks if a VertexIterator is valid.
     * @var SimpleGraph::isValidVertex
     *   A function that checks if a graph's vertex is valid.
     * @var SimpleGraph::nextVertexId_nitr
     *   A function that iterates towards the next vertex index of a NeighborIterator.
     * @var SimpleGraph::nextVertexId_svitr
     *   A function that iterates towards the next vertex index of a StartVertexIterator.
     * @var SimpleGraph::nextVertexId_vitr
     *   A function that iterates towards the next vertex index of a VertexIterator.
     * @var SimpleGraph::setFirstNextId_nitr
     *   A function that sets the first vertex index of a NeighborIterator.
     * @var SimpleGraph::setFirstNextId_svitr
     *   A function that sets the first vertex index of a StartVertexIterator.
     * @var SimpleGraph::setFirstNextId_vitr
     *   A function that sets the first vertex index of a VertexIterator.
     */
    typedef struct SimpleGraphInterface {
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
   } SimpleGraph;

    /**
     * @brief Checks if two vertices are neighbors in a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     * @param sourceVertexId The source vertex index.
     * @param targetVertexId The target vertex index.
     */
    bool areNeighbors_sg(SimpleGraph const* const graph, uint32_t const sourceVertexId, uint32_t const targetVertexId);

    /**
     * @brief Constructs a NeighborIterator for a vertex in a SimpleGraph.
     * @param itr A pointer to the NeighborIterator.
     * @param graph A pointer to the constant SimpleGraph.
     * @param sourceVertexId The source vertex index.
     */
    void construct_nitr_sg(NeighborIterator* const itr, SimpleGraph const* const graph, uint32_t const sourceVertexId);

    /**
     * @brief Constructs a StartVertexIterator for a SimpleGraph.
     * @param itr A pointer to the StartVertexIterator.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void construct_svitr_sg(StartVertexIterator* const itr, SimpleGraph const* const graph);

    /**
     * @brief Constructs a VertexIterator for a SimpleGraph.
     * @param itr A pointer to the VertexIterator.
     * @param graph A pointer to the constant SimpleGraph.
     */
    void construct_vitr_sg(VertexIterator* const itr, SimpleGraph const* const graph);

    /**
     * @brief The default function to count the total number of edges in a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     */
    uint32_t countEdges_default_sg(SimpleGraph const* const graph);

    /**
     * @brief The default function to counts the total number of vertices in a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     */
    uint32_t countVertices_default_sg(SimpleGraph const* const graph);

    /**
     * @brief Counts the total number of edges in a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     */
    uint32_t countEdges_sg(SimpleGraph const* const graph);

    /**
     * @brief Counts the total number of vertices in a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     */
    uint32_t countVertices_sg(SimpleGraph const* const graph);

    /**
     * @brief Dumps a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_sg(SimpleGraph const* const graph, FILE* const output);

    /**
     * @brief The default function to dump a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     * @param output A pointer to the output FILE.
     */
    void dump_default_sg(SimpleGraph const* const graph, FILE* const output);

    /**
     * @brief Dumps one vertex of a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The vertex index.
     */
    void dumpVertex_sg(SimpleGraph const* const graph, FILE* const output, uint32_t const vertexId);

    /**
     * @brief The default function to dump one vertex of a SimpleGraph.
     * @param graph A pointer to the constant SimpleGraph.
     * @param output A pointer to the output FILE.
     * @param vertexId The vertex index.
     */
    void dumpVertex_default_sg(SimpleGraph const* const graph, FILE* const output, uint32_t const vertexId);

    /**
     * @brief The default function to check if a NeighborIterator is valid.
     * @param graph A pointer to the constant SimpleGraph.
     * @param itr A pointer to the NeighborIterator.
     */
    bool isValid_nitr_default_sg(SimpleGraph const* const graph, NeighborIterator const* const itr);

    /**
     * @brief Checks if a SimpleGraph is valid.
     * @param graph A pointer to the constant SimpleGraph.
     */
    bool isValid_sg(SimpleGraph const* const graph);

    /**
     * @brief The default function to check if a StartVertexIterator is valid.
     * @param graph A pointer to the constant SimpleGraph.
     * @param itr A pointer to the StartVertexIterator.
     */
    bool isValid_svitr_default_sg(SimpleGraph const* const graph, StartVertexIterator const* const itr);

    /**
     * @brief The default function to check if a VertexIterator is valid.
     * @param graph A pointer to the constant SimpleGraph.
     * @param itr A pointer to the VertexIterator.
     */
    bool isValid_vitr_default_sg(SimpleGraph const* const graph, VertexIterator const* const itr);

    /**
     * @brief Checks if a SimpleGraph vertex is valid.
     * @param graph A pointer to the constant SimpleGraph.
     * @param vertexId The vertex index.
     */
    bool isValidVertex_sg(SimpleGraph const* const graph, uint32_t const vertexId);
#endif
