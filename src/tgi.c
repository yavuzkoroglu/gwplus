/**
 * @file tgi.c
 * @brief Implements the functions defined in tgi.h
 */
#include "padkit/debug.h"
#include "tgi.h"

void construct_nitr_tg(NeighborIterator* const itr, TestableGraph const* const graph, uint32_t const sourceVertexId) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_tg(graph))

    itr->graphPtr = graph->graphPtr;
    itr->vertexId = sourceVertexId;
    graph->setFirstNextId_nitr(itr);
}

void construct_svitr_tg(StartVertexIterator* const itr, TestableGraph const* const graph) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_tg(graph))

    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_svitr(itr);
}

uint32_t countEdges_tg(TestableGraph const* const graph) {
    DEBUG_ASSERT(isValid_tg(graph))
    return graph->countEdges(graph->graphPtr);
}

uint32_t countVertices_tg(TestableGraph const* const graph) {
    DEBUG_ASSERT(isValid_tg(graph))
    return graph->countVertices(graph->graphPtr);
}

void dump_tg(TestableGraph const* const graph, FILE* const output) {
    DEBUG_ASSERT(isValid_tg(graph))
    DEBUG_ERROR_IF(output == NULL)

    graph->dump(graph->graphPtr, output);
}

void dumpVertex_tg(TestableGraph const* const graph, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_tg(graph))
    DEBUG_ERROR_IF(output == NULL)

    graph->dumpVertex(graph->graphPtr, output, vertexId);
}

bool isValid_tg(TestableGraph const* const graph) {
    return graph != NULL && graph->isValid(graph->graphPtr);
}

bool isValidVertex_tg(TestableGraph const* const graph, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_tg(graph))
    return graph->isValidVertex(graph->graphPtr, vertexId);
}
