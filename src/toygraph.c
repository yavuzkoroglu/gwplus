/**
 * @file toygraph.c
 * @brief Implements the Testable Graph Interface (TGI) in the dummiest way.
 * @see tgi.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "padkit/debug.h"
#include "vpathgraph.h"

/*
 * 0: 0 -> 1
 * 1: 1 -> 2
 * 2: 2 -> 0
 * 3: 2 -> 2
 * 4: 2 -> 3
 * 5: 3 -> 2
 * 6: 3 -> 4
 * 7: 4 -> 3
 */
static unsigned char toy_graph[5][5] = {
    { 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 1, 0, 1, 1, 0 },
    { 0, 0, 1, 0, 1 },
    { 0, 0, 0, 1, 0 }
};

static uint32_t countEdges_toy(void const* const graphPtr);
static uint32_t countVertices_toy(void const* const graphPtr);
static void dump_toy(void const* const graphPtr, FILE* const output);
static void dumpVertex_toy(void const* const graphPtr, FILE* const output, uint32_t const vertexId);
static bool isValid_toy(void const* const graphPtr);
static bool isValid_nitr_toy(NeighborIterator const* const itr);
static bool isValid_svitr_toy(StartVertexIterator const* const itr);
static bool isValid_vitr_toy(VertexIterator const* const itr);
static bool isValidVertex_toy(void const* const graphPtr, uint32_t const vertexId);
static uint32_t nextVertexId_nitr_toy(NeighborIterator* const itr);
static uint32_t nextVertexId_svitr_toy(StartVertexIterator* const itr);
static uint32_t nextVertexId_vitr_toy(VertexIterator* const itr);
static void setFirstNextId_nitr_toy(NeighborIterator* const itr);
static void setFirstNextId_svitr_toy(StartVertexIterator* const itr);
static void setFirstNextId_vitr_toy(VertexIterator* const itr);

uint32_t countEdges_toy(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_toy(graphPtr))

    uint32_t count = 0;
    for (uint32_t i = 0; i < 5; i++)
        for (uint32_t j = 0; j < 5; j++)
            count += toy_graph[i][j];

    return count;
}

static uint32_t countVertices_toy(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_toy(graphPtr))
    return 5;
}

void dump_toy(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_toy(graphPtr))
    DEBUG_ERROR_IF(output == NULL)

    uint32_t const vertex_count = countVertices_toy(graphPtr);

    for (uint32_t i = 0; i < vertex_count; i++)
        for (uint32_t j = 0; j < vertex_count; j++)
            if (toy_graph[i][j])
                fprintf(output, "%"PRIu32" -> %"PRIu32"\n", i, j);
}

void dumpVertex_toy(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_toy(graphPtr))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_toy(graphPtr, vertexId))

    fprintf(output, " %"PRIu32, vertexId);
}

static bool isValid_toy(void const* const graphPtr) {
    return graphPtr == toy_graph;
}

static bool isValid_nitr_toy(NeighborIterator const* const itr) {
    return itr != NULL && isValid_toy(itr->graphPtr) && isValidVertex_toy(itr->graphPtr, itr->vertexId);
}

static bool isValid_svitr_toy(StartVertexIterator const* const itr) {
    return itr != NULL && isValid_toy(itr->graphPtr);
}

static bool isValid_vitr_toy(VertexIterator const* const itr) {
    return itr != NULL && isValid_toy(itr->graphPtr);
}

static bool isValidVertex_toy(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_toy(graphPtr))
    return vertexId < countVertices_toy(graphPtr);
}

static uint32_t nextVertexId_nitr_toy(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_toy(itr))

    if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;

    uint32_t const vertex_count = countVertices_toy(itr->graphPtr);
    while (itr->nextNeighborId < vertex_count) {
        if (toy_graph[itr->vertexId][itr->nextNeighborId])
            return itr->nextNeighborId++;

        itr->nextNeighborId++;
    }

    return (itr->nextNeighborId = 0xFFFFFFFF);
}

static uint32_t nextVertexId_svitr_toy(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_toy(itr))

    switch (itr->nextVertexId) {
        case 0:
            itr->nextVertexId = 0xFFFFFFFF;
            return 0;
        default:
            return 0xFFFFFFFF;
    }
}

static uint32_t nextVertexId_vitr_toy(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_toy(itr))

    if (isValidVertex_toy(itr->graphPtr, itr->nextVertexId)) {
        return itr->nextVertexId++;
    } else {
        return 0xFFFFFFFF;
    }
}

void setFirstNextId_nitr_toy(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_toy(itr))
    itr->nextNeighborId = 0;
}

void setFirstNextId_svitr_toy(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_toy(itr))
    itr->nextVertexId = 0;
}

void setFirstNextId_vitr_toy(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_toy(itr))
    itr->nextVertexId = 0;
}

int main(void) {
    TestableGraph graph[1] = { (TestableGraph){
        toy_graph,
        countEdges_toy,
        countVertices_toy,
        dump_toy,
        dumpVertex_toy,
        isValid_toy,
        isValid_nitr_toy,
        isValid_svitr_toy,
        isValid_vitr_toy,
        isValidVertex_toy,
        nextVertexId_nitr_toy,
        nextVertexId_svitr_toy,
        nextVertexId_vitr_toy,
        setFirstNextId_nitr_toy,
        setFirstNextId_svitr_toy,
        setFirstNextId_vitr_toy
    }};

    dump_tg(graph, stdout);

    VertexPathArray primePaths[1];
    constructAllPrimePaths_vpa(primePaths, graph, VPATH_ARRAY_DEFAULT_INITIAL_CAP);

    dump_vpa(primePaths, stdout);

    VertexPathGraph vpgraph[1];
    construct_vpg(vpgraph, primePaths);

    dump_vpg(vpgraph, stdout);

    free_vpg(vpgraph);
    free_vpa(primePaths);

    return 0;
}
