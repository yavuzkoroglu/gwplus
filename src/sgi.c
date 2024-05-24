/**
 * @file sgi.c
 * @brief Implements the functions defined in sgi.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "padkit/debug.h"
#include "sgi.h"

void construct_nitr_sg(NeighborIterator* const itr, SimpleGraph const* const graph, uint32_t const sourceVertexId) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, sourceVertexId))

    itr->graphPtr = graph->graphPtr;
    itr->vertexId = sourceVertexId;
    graph->setFirstNextId_nitr(itr);
}

void construct_svitr_sg(VertexIterator* const itr, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_svitr(itr);
}

void construct_vitr_sg(StartVertexIterator* const itr, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_vitr(itr);
}

void free_sg(SimpleGraph* const graph) {
    DEBUG_ASSERT(isValid_sg(graph))

    graph->free(graph->graphPtr);
    *graph = NOT_AN_SG;
}

bool isValid_sg(SimpleGraph const* const graph) {
    return graph != NULL && graph->graphPtr != NULL && graph->isValid(graph->graphPtr);
}
