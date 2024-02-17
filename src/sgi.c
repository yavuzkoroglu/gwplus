/**
 * @file sgi.c
 * @brief Implements the functions defined in sgi.h
 */
#include <inttypes.h>
#include "padkit/debug.h"
#include "sgi.h"

bool areNeighbors_sg(SimpleGraph const* const graph, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValidVertex_sg(graph, sourceVertexId))
    DEBUG_ASSERT(isValidVertex_sg(graph, targetVertexId))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, graph, sourceVertexId);

    for (
        uint32_t neighborId;
        (neighborId = graph->nextVertexId_nitr(itr)) != 0xFFFFFFFF;
    ) if (neighborId == targetVertexId) return 1;

    return 0;
}

void construct_nitr_sg(NeighborIterator* const itr, SimpleGraph const* const graph, uint32_t const sourceVertexId) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    itr->graphPtr = graph->graphPtr;
    itr->vertexId = sourceVertexId;
    graph->setFirstNextId_nitr(itr);
}

void construct_svitr_sg(VertexIterator* const itr, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_vitr(itr);
}

void construct_vitr_sg(StartVertexIterator* const itr, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(itr == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    itr->graphPtr = graph->graphPtr;
    graph->setFirstNextId_svitr(itr);
}

uint32_t countEdges_default_sg(SimpleGraph const* const graph) {
    static void const* old_ptr  = NULL;
    static uint32_t count_edges = 0;

    DEBUG_ASSERT(isValid_sg(graph))
    if (old_ptr == graph->graphPtr)
        return count_edges;

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);

    count_edges = 0;
    for (
        uint32_t vertexId;
        (vertexId = graph->nextVertexId_vitr(vitr)) != 0xFFFFFFFF;
    ) {
        NeighborIterator itr[1];
        construct_nitr_sg(itr, graph);
        for (
            uint32_t neighborId;
            (neighborId = graph->nextVertexId_nitr(itr)) != 0xFFFFFFFF;
        ) count_edges++;
    }
}

uint32_t countVertices_default_sg(SimpleGraph const* const graph) {
    static void const* cached_ptr   = NULL;
    static uint32_t count_vertices  = 0;

    DEBUG_ASSERT(isValid_sg(graph))
    if (cached_ptr == graph->graphPtr)
        return count_vertices;

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);

    count_vertices = 0;
    for (
        uint32_t vertexId;
        (vertexId = graph->nextVertexId_vitr(vitr)) != 0xFFFFFFFF;
    ) count_vertices++;

    return count_vertices;
}

uint32_t countEdges_sg(SimpleGraph const* const graph) {
    DEBUG_ASSERT(isValid_sg(graph))
    return graph->countEdges(graph->graphPtr);
}

uint32_t countVertices_sg(SimpleGraph const* const graph) {
    DEBUG_ASSERT(isValid_sg(graph))
    return graph->countVertices(graph->graphPtr);
}

void dump_sg(SimpleGraph const* const graph, FILE* const output) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)

    graph->dump(graph->graphPtr, output);
}

void dump_default_sg(SimpleGraph const* const graph, FILE* const output) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);
    for (
        uint32_t vertexId;
        (vertexId = graph->nextVertexId_vitr(vitr)) != 0xFFFFFFFF;
    ) {
        NeighborIterator nitr[1];
        construct_nitr_sg(nitr, graph);
        for (
            uint32_t neighborId;
            (neighborId = graph->nextVertexId_nitr(nitr) != 0xFFFFFFFF);
        ) fprintf("%"PRIu32" -> %"PRIu32";\n", vertexId, neighborId);
    }
}

void dumpVertex_sg(SimpleGraph const* const graph, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, vertexId))

    graph->dumpVertex(graph->graphPtr, output, vertexId);
}

void dumpVertex_default_sg(SimpleGraph const* const graph, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, vertexId))

    fprintf(" %"PRIu32, vertexId);
}

bool isValid_sg(SimpleGraph const* const graph) {
    return graph != NULL && graph->isValid(graph->graphPtr);
}

bool isValid_nitr_default_sg(SimpleGraph const* const graph, NeighborIterator const* const itr) {
    return  isValid_sg(graph)                                   &&
            itr != NULL                                         &&
            itr->graphPtr == graph->graphPtr                    &&
            graph->isValidVertex(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_default_sg(SimpleGraph const* const graph, StartVertexIterator const* const itr) {
    return  isValid_sg(graph)                   &&
            itr != NULL                         &&
            itr->graphPtr == graph->graphPtr;
}

bool isValid_vitr_default_sg(SimpleGraph const* const graph, VertexIterator const* const itr) {
    return  isValid_sg(graph)                   &&
            itr != NULL                         &&
            itr->graphPtr == graph->graphPtr;
}

bool isValidVertex_sg(SimpleGraph const* const graph, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_sg(graph))
    return graph->isValidVertex(graph->graphPtr, vertexId);
}
