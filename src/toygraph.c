/**
 * @file toygraph.c
 * @brief Implements the toygraphs given in examples directory.
 * @author Yavuz Koroglu
 */
#include "hpathgraph.h"
#include "padkit/debug.h"

static bool toygraph001[3][3] = {
    { 1, 1, 0 },
    { 0, 0, 1 },
    { 1, 1, 0 }
};

static uint32_t countEdges_toy001(void const* const graphPtr);
static uint32_t countVertices_toy001(void const* const graphPtr);
static void dump_toy001(void const* const graphPtr, FILE* const output);
static void dumpVertex_toy001(void const* const graphPtr, FILE* const output, uint32_t const vertexId);
static bool isValid_toy(void const* const graphPtr);
static bool isValid_nitr_toy001(NeighborIterator const* const itr);
static bool isValid_svitr_toy(StartVertexIterator const* const itr);
static bool isValid_vitr_toy(VertexIterator const* const itr);
static bool isValidEdge_toy001(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId);
static bool isValidVertex_toy001(void const* const graphPtr, uint32_t const vertexId);
static uint32_t nextVertexId_nitr_toy001(NeighborIterator* const itr);
static uint32_t nextVertexId_svitr_toy(StartVertexIterator* const itr);
static uint32_t nextVertexId_vitr_toy(StartVertexIterator* const itr);
static void setFirstNextId_nitr_toy001(NeighborIterator* const itr);
static void setFirstNextId_svitr_toy001(StartVertexIterator* const itr);
static void setFirstNextId_vitr_toy001(VertexIterator* const itr);

static SimpleGraph graph001[1] = { (SimpleGraph){
    toygraph001,
    countEdges_toy001,
    countVertices_toy001,
    dump_toy001,
    dumpVertex_toy001,
    isValid_toy,
    isValid_nitr_toy001,
    isValid_svitr_toy,
    isValid_vitr_toy,
    isValidEdge_toy001,
    isValidVertex_toy001,
    nextVertexId_nitr_toy001,
    nextVertexId_svitr_toy,
    nextVertexId_vitr_toy,
    setFirstNextId_nitr_toy001,
    setFirstNextId_svitr_toy001,
    setFirstNextId_vitr_toy001
}};

static uint32_t countEdges_toy001(void const* const graphPtr) {
    DEBUG_ERROR_IF(graphPtr == NULL)
    return 5;
}
static uint32_t countVertices_toy001(void const* const graphPtr) {
    DEBUG_ERROR_IF(graphPtr == NULL)
    return 3;
}
static void dump_toy001(void const* const graphPtr, FILE* const output) {
    DEBUG_ERROR_IF(graphPtr == NULL)
    dump_sg(graph001, output);
}
static void dumpVertex_toy001(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ERROR_IF(graphPtr == NULL)
    DEBUG_ASSERT(vertexId < 3)
    dumpVertex_sg(graph001, output, vertexId);
}
static bool isValid_toy(void const* const graphPtr) {
    return graphPtr != NULL;
}
static bool isValid_nitr_toy001(NeighborIterator const* const itr) {
    return itr != NULL && itr->graphPtr != NULL && itr->vertexId < 3;
}
static bool isValid_svitr_toy(StartVertexIterator const* const itr) {
    return itr != NULL && itr->graphPtr != NULL;
}
static bool isValid_vitr_toy(VertexIterator const* const itr) {
    return itr != NULL && itr->graphPtr != NULL;
}
static bool isValidEdge_toy001(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    return graphPtr != NULL && sourceVertexId < 3 && targetVertexId < 3 && toygraph001[sourceVertexId][targetVertexId];
}
static bool isValidVertex_toy001(void const* const graphPtr, uint32_t const vertexId) {
    return graphPtr != NULL && vertexId < 3;
}
static uint32_t nextVertexId_nitr_toy001(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_toy001(itr))

    while (!isValidEdge_toy001(itr->graphPtr, itr->vertexId, itr->nextNeighborId)) {
        if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextNeighborId--;
    }

    return itr->nextNeighborId--;
}
static uint32_t nextVertexId_svitr_toy(StartVertexIterator* const itr) {
    DEBUG_ERROR_IF(itr == NULL)

    if (itr->nextVertexId == 0xFFFFFFFF) {
        return 0xFFFFFFFF;
    } else {
        itr->nextVertexId = 0xFFFFFFFF;
        return 0;
    }
}
static uint32_t nextVertexId_vitr_toy(StartVertexIterator* const itr) {
    DEBUG_ERROR_IF(itr == NULL)

    uint32_t const old_id = itr->nextVertexId;
    itr->nextVertexId -= !(itr->nextVertexId == 0xFFFFFFFF);
    return old_id;
}
static void setFirstNextId_nitr_toy001(NeighborIterator* const itr) {
    DEBUG_ERROR_IF(itr == NULL)
    itr->nextNeighborId = 2;
}
static void setFirstNextId_svitr_toy001(StartVertexIterator* const itr) {
    DEBUG_ERROR_IF(itr == NULL)
    itr->nextVertexId = 0;
}
static void setFirstNextId_vitr_toy001(VertexIterator* const itr) {
    DEBUG_ERROR_IF(itr == NULL)
    itr->nextVertexId = 2;
}

int main(void) {
    FILE* const output = stdout;

    fputs(
        "\n"
        "toygraph001 = \n",
        output
    );
    graph001->dump(toygraph001, output);

    VertexPathArray primePaths[1];
    constructAllPrimePaths_vpa(primePaths, graph001);

    fputs(
        "\n"
        "primePaths = \n",
        output
    );
    dump_vpa(primePaths, output);

    VertexPathGraph vpgraph[1];
    construct_vpg(vpgraph, graph001, primePaths);

    SimpleGraph pathGraph[1];
    construct_sgi_vpg(pathGraph, vpgraph);

    fputs(
        "\n"
        "pathGraph = \n",
        output
    );
    pathGraph->dump(vpgraph, output);

    HyperPathGraph hpgraph[1];
    constructAcyclic_hpg(hpgraph, pathGraph);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    fputs(
        "\n"
        "hyperPathGraph = \n",
        output
    );
    hyperPathGraph->dump(hpgraph, output);

    VertexPath pathTrace[1];
    constructPathTrace_hpg(pathTrace, hpgraph, 10);

    fputs(
        "\n"
        "pathTrace = \n",
        output
    );
    dump_vpath(pathTrace, output);

    fputs("\n", output);

    free_vpath(pathTrace);
    free_hpg(hpgraph);
    free_vpg(vpgraph);
    free_vpa(primePaths);

    return 0;
}
