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

    typedef struct NeighborIteratorBody {
        void const* graphPtr;
        uint32_t    vertexId;
        uint32_t    nextNeighborId;
    } NeighborIterator;

    typedef struct StartVertexIteratorBody {
        void const* graphPtr;
        uint32_t    nextVertexId;
    } StartVertexIterator;

    typedef struct TestableGraphInterface {
        void const* graphPtr;
        uint32_t    (*countEdges)           (void const* const graphPtr);
        uint32_t    (*countVertices)        (void const* const graphPtr);
        void        (*dump)                 (void const* const graphPtr, FILE* const output);
        void        (*dumpVertex)           (void const* const graphPtr, FILE* const output, uint32_t const vertexId);
        void        (*setFirstNextId_nitr)  (NeighborIterator* const itr);
        void        (*setFirstNextId_svitr) (StartVertexIterator* const itr);
        bool        (*isValid)              (void const* const graphPtr);
        bool        (*isValid_nitr)         (NeighborIterator const* const itr);
        bool        (*isValid_svitr)        (StartVertexIterator const* const itr);
        bool        (*isValidVertex)        (void const* const graphPtr, uint32_t const vertexId);
        uint32_t    (*nextVertexId_nitr)    (NeighborIterator* const itr);
        uint32_t    (*nextVertexId_svitr)   (StartVertexIterator* const itr);
    } TestableGraph;

    void construct_nitr_tg(NeighborIterator* const itr, TestableGraph const* const graph, uint32_t const sourceVertexId);

    void construct_svitr_tg(StartVertexIterator* const itr, TestableGraph const* const graph);

    uint32_t countEdges_tg(TestableGraph const* const graph);

    uint32_t countVertices_tg(TestableGraph const* const graph);

    void dump_tg(TestableGraph const* const graph, FILE* const output);

    void dumpVertex_tg(TestableGraph const* const graph, FILE* const output, uint32_t const vertexId);

    bool isValid_tg(TestableGraph const* const graph);

    bool isValidVertex_tg(TestableGraph const* const graph, uint32_t const vertexId);
#endif
