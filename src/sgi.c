/**
 * @file sgi.c
 * @brief Implements the functions defined in sgi.h
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

uint32_t countEdges_sg(SimpleGraph const* const graph) {
    static void const* old_ptr  = NULL;
    static uint32_t count_edges = 0;

    DEBUG_ASSERT(isValid_sg(graph))
    if (old_ptr == graph->graphPtr)
        return count_edges;

    old_ptr = graph->graphPtr;

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);

    count_edges = 0;
    for (
        uint32_t vertexId;
        graph->isValidVertex(graph->graphPtr, (vertexId = graph->nextVertexId_vitr(vitr)));
    ) {
        NeighborIterator itr[1];
        construct_nitr_sg(itr, graph, vertexId);
        for (
            uint32_t neighborId;
            graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
        ) count_edges++;
    }

    return count_edges;
}

uint32_t countVertices_sg(SimpleGraph const* const graph) {
    static void const* cached_ptr   = NULL;
    static uint32_t count_vertices  = 0;

    DEBUG_ASSERT(isValid_sg(graph))
    if (cached_ptr == graph->graphPtr) {
        return count_vertices;
    }

    cached_ptr = graph->graphPtr;

    VertexIterator itr[1];
    construct_vitr_sg(itr, graph);

    count_vertices = 0;
    for (
        uint32_t vertexId;
        graph->isValidVertex(graph->graphPtr, (vertexId = graph->nextVertexId_vitr(itr)));
    ) count_vertices++;

    return count_vertices;
}

void dump_sg(SimpleGraph const* const graph, FILE* const output) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);
    for (
        uint32_t vertexId;
        graph->isValidVertex(graph->graphPtr, (vertexId = graph->nextVertexId_vitr(vitr)));
    ) {
        NeighborIterator nitr[1];
        construct_nitr_sg(nitr, graph, vertexId);
        for (
            uint32_t neighborId;
            graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(nitr)));
        ) {
            graph->dumpVertex(graph->graphPtr, output, vertexId);
            fputs(" ->", output);
            graph->dumpVertex(graph->graphPtr, output, neighborId);
            fputs(";\n", output);
        }
    }
}

void dumpVertex_sg(SimpleGraph const* const graph, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, vertexId))

    fprintf(output, " %"PRIu32, vertexId);
}

bool isValid_sg(SimpleGraph const* const graph) {
    return graph != NULL && graph->graphPtr != NULL && graph->isValid(graph->graphPtr);
}

bool isValidEdge_sg(SimpleGraph const* const graph, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(graph->isValidVertex(graph, sourceVertexId))
    DEBUG_ASSERT(graph->isValidVertex(graph, targetVertexId))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, graph, sourceVertexId);
    for (
        uint32_t neighborId;
        graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
    ) if (neighborId == targetVertexId) return 1;

    return 0;
}
