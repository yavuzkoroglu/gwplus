/**
 * @file hpathgraph.c
 * @brief Implements the functions defined in hpathgraph.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <string.h>
#include "hpathgraph.h"
#include "padkit/debug.h"

void construct_hpg(
    SimpleGraph* const hyperPathGraph, HyperPathGraph* const hpgraph,
    SimpleGraph const* const pathGraph
) {
    DEBUG_ERROR_IF(hyperPathGraph == NULL)
    DEBUG_ERROR_IF(hpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(pathGraph))

    hpgraph->pathGraph = pathGraph;

    uint32_t const sz   = pathGraph->countVertices(pathGraph->graphPtr);
    uint32_t const cap  = sz << 1;
    DEBUG_ASSERT(cap > sz)

    constructVerticesAsPaths_vpa(hpgraph->hpaths, pathGraph);
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(hpgraph->edgeMtx, cap, cap))
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(hpgraph->subsumptionMtx, 1, cap))

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, pathGraph);
    for (
        uint32_t pathId;
        pathGraph->isValidVertex(pathGraph->graphPtr, (pathId = pathGraph->nextVertexId_vitr(vitr)));
    ) {
        #ifndef NDEBUG
            VertexPath* const hpath = hpgraph->hpaths->array + pathId;
            DEBUG_ASSERT(isValid_vpath(hpath))
            DEBUG_ASSERT(hpath->len == 1)
        #endif

        NeighborIterator nitr[1];
        construct_nitr_sg(nitr, pathGraph, pathId);
        for (
            uint32_t neighborId;
            pathGraph->isValidVertex(pathGraph->graphPtr, (neighborId = pathGraph->nextVertexId_nitr(nitr)));
        ) connect_gmtx(hpgraph->edgeMtx, pathId, neighborId);
    }

    construct_sgi_hpg(hyperPathGraph, hpgraph);
}

void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph* const hpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    *graph = (SimpleGraph){
        hpgraph,
        countEdges_hpg,
        countVertices_hpg,
        dump_hpg,
        dumpVertex_hpg,
        free_hpg,
        highestVertexId_hpg,
        isValid_hpg,
        isValid_nitr_hpg,
        isValid_svitr_hpg,
        isValid_vitr_hpg,
        isValidEdge_hpg,
        isValidVertex_hpg,
        nextVertexId_nitr_hpg,
        nextVertexId_svitr_hpg,
        nextVertexId_vitr_hpg,
        setFirstNextId_nitr_hpg,
        setFirstNextId_svitr_hpg,
        setFirstNextId_vitr_hpg
    };
}

void constructAcyclic_hpg(
    SimpleGraph* const hyperPathGraph, HyperPathGraph* const hpgraph,
    SimpleGraph const* const pathGraph
) {
    DEBUG_ERROR_IF(hyperPathGraph == NULL)
    DEBUG_ERROR_IF(hpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(pathGraph))

    construct_hpg(hyperPathGraph, hpgraph, pathGraph);

    for (
        VertexPath* hpath;
        computeShortestCycle_vpath((hpath = pushEmpty_vpa(hpgraph->hpaths, hyperPathGraph)), hyperPathGraph);
    ) {
        uint32_t const parentId = hpgraph->hpaths->size - 1;

        for (uint32_t i = 0; i < hpath->len; i++) {
            uint32_t childId = hpath->array[i];
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->subsumptionMtx, 0, childId))

            VertexIterator itr[1];
            construct_vitr_sg(itr, hyperPathGraph);
            for (
                uint32_t pathId;
                isValidVertex_hpg(hpgraph, (pathId = nextVertexId_vitr_hpg(itr)));
            ) {
                if (pathId == parentId || contains_vpath(hpath, pathId)) continue;
                if (isConnected_gmtx(hpgraph->edgeMtx, childId, pathId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, parentId, pathId))
                if (isConnected_gmtx(hpgraph->edgeMtx, pathId, childId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, pathId, parentId))
            }
        }
    }
    pop_vpa(hpgraph->hpaths);
}

uint32_t countEdges_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    if (hpgraph->hpaths->size == 0)
        return 0;

    uint32_t count = 0;
    for (uint32_t i = 0; i < hpgraph->hpaths->size - 1; i++) {
        if (isConnected_gmtx(hpgraph->subsumptionMtx, 0, i))
            continue;

        for (uint32_t j = i + 1; j < hpgraph->hpaths->size; j++) {
            if (isConnected_gmtx(hpgraph->subsumptionMtx, 0, j))
                continue;

            count += isConnected_gmtx(hpgraph->edgeMtx, i, j);
            count += isConnected_gmtx(hpgraph->edgeMtx, j, i);
        }
    }

    return count;
}

uint32_t countVertices_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    uint32_t count = 0;
    for (uint32_t i = 0; i < hpgraph->hpaths->size; i++)
        count += !isConnected_gmtx(hpgraph->subsumptionMtx, 0, i);

    return count;
}

void dump_hpg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)

    for (uint32_t h0_id = hpgraph->hpaths->size - 1; h0_id != 0xFFFFFFFF; h0_id--) {
        if (isConnected_gmtx(hpgraph->subsumptionMtx, 0, h0_id))
            continue;

        for (uint32_t h1_id = hpgraph->hpaths->size - 1; h1_id != 0xFFFFFFFF; h1_id--) {
            if (h0_id == h1_id || isConnected_gmtx(hpgraph->subsumptionMtx, 0, h1_id))
                continue;

            if (isConnected_gmtx(hpgraph->edgeMtx, h0_id, h1_id)) {
                dumpVertex_hpg(graphPtr, output, h0_id);
                fputs(" -> ", output);
                dumpVertex_hpg(graphPtr, output, h1_id);
                fputs("\n", output);
            }
        }
    }
}

void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    DEBUG_ASSERT(isValidVertex_hpg(graphPtr, vertexId))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    StartVertexIterator itr[1];
    construct_svitr_sg(itr, hpgraph->pathGraph);
    uint32_t const startVertexId = hpgraph->pathGraph->nextVertexId_svitr(itr);
    if (startVertexId == vertexId)
        fputs(" s", output);
    else if (vertexId < startVertexId)
        fprintf(output, " %"PRIu32, vertexId);
    else
        fprintf(output, " %"PRIu32, vertexId);
}

void free_hpg(void* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))

    HyperPathGraph* const hpgraph = (HyperPathGraph*)graphPtr;

    free_vpa(hpgraph->hpaths);
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(hpgraph->edgeMtx))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(hpgraph->subsumptionMtx))
    *hpgraph = NOT_A_HPATH_GRAPH;
}

uint32_t highestVertexId_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    return hpgraph->hpaths->size - 1;
}

bool isValid_hpg(void const* const graphPtr) {
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    return  hpgraph != NULL                         &&
            isValid_sg(hpgraph->pathGraph)          &&
            isValid_vpa(hpgraph->hpaths)            &&
            isValid_gmtx(hpgraph->edgeMtx)          &&
            isValid_gmtx(hpgraph->subsumptionMtx);
}

bool isValid_nitr_hpg(NeighborIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr) && isValidVertex_hpg(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_hpg(StartVertexIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValid_vitr_hpg(VertexIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValidEdge_hpg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    return  isValidVertex_hpg(graphPtr, sourceVertexId)                         &&
            isValidVertex_hpg(graphPtr, targetVertexId)                         &&
            isConnected_gmtx(hpgraph->edgeMtx, sourceVertexId, targetVertexId);
}

bool isValidVertex_hpg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    return vertexId < hpgraph->hpaths->size && !isConnected_gmtx(hpgraph->subsumptionMtx, 0, vertexId);
}

uint32_t nextVertexId_nitr_hpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_hpg(itr))

    while (!isValidEdge_hpg(itr->graphPtr, itr->vertexId, itr->nextNeighborId)) {
        if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextNeighborId--;
    }

    return itr->nextNeighborId--;
}

uint32_t nextVertexId_svitr_hpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_hpg(itr))

    if (!isValidVertex_hpg(itr->graphPtr, itr->nextVertexId)) return 0xFFFFFFFF;

    uint32_t const s_id = itr->nextVertexId;
    itr->nextVertexId = 0xFFFFFFFF;
    return s_id;
}

uint32_t nextVertexId_vitr_hpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_hpg(itr))

    while (!isValidVertex_hpg(itr->graphPtr, itr->nextVertexId)) {
        if (itr->nextVertexId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextVertexId--;
    }

    return itr->nextVertexId--;
}

void setFirstNextId_nitr_hpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_hpg(itr))
    itr->nextNeighborId = highestVertexId_hpg(itr->graphPtr);
}

void setFirstNextId_svitr_hpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_hpg(itr))

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hpgraph->pathGraph);
    itr->nextVertexId = hpgraph->pathGraph->nextVertexId_svitr(svitr);
}

void setFirstNextId_vitr_hpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_hpg(itr))
    itr->nextVertexId = highestVertexId_hpg(itr->graphPtr);
}

