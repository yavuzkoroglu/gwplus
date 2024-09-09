#include <assert.h>
#include <inttypes.h>
#include "sgi.h"

void construct_nitr_sg(
    NeighborIterator itr[static const 1],
    SimpleGraph const graph[static const 1],
    uint32_t const sourceVertexId
) {
    assert(isValid_sg(graph));
    assert(graph->isValidVertex(graph->graphPtr, sourceVertexId));

    itr->graphPtr = graph->graphPtr;
    itr->vertexId = sourceVertexId;
    graph->setFirstNextId_nitr(itr);
}

void construct_svitr_sg(VertexIterator itr[static const 1], SimpleGraph const graph[static const 1]) {
    assert(isValid_sg(graph));
    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_svitr(itr);
}

void construct_vitr_sg(StartVertexIterator itr[static const 1], SimpleGraph const graph[static const 1]) {
    assert(isValid_sg(graph));
    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_vitr(itr);
}

void free_sg(SimpleGraph graph[static const 1]) {
    assert(isValid_sg(graph));
    graph->free(graph->graphPtr);
    graph[0] = NOT_AN_SG;
}

bool isValid_sg(SimpleGraph const graph[static const 1]) {
    if (graph->graphPtr == NULL) return 0;

    return graph->isValid(graph->graphPtr);
}
