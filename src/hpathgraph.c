/**
 * @file hpathgraph.c
 * @brief Implements the functions defined in hpathgraph.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <string.h>
#include "hpathgraph.h"
#include "padkit/debug.h"

uint32_t countEdges_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    return countEdges_sg(hyperPathGraph);
}

uint32_t countVertices_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    return countVertices_sg(hyperPathGraph);
}

void construct_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph) {
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
        VertexPath* const hpath = hpgraph->hpaths->array + pathId;
        DEBUG_ASSERT(isValid_vpath(hpath))
        DEBUG_ASSERT(hpath->len == 1)

        NeighborIterator nitr[1];
        construct_nitr_sg(nitr, pathGraph, pathId);
        for (
            uint32_t neighborId;
            pathGraph->isValidVertex(pathGraph->graphPtr, (neighborId = pathGraph->nextVertexId_nitr(nitr)));
        ) connect_gmtx(hpgraph->edgeMtx, pathId, neighborId);
    }
}

void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph const* const hpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    *graph = (SimpleGraph){
        hpgraph,
        countEdges_hpg,
        countVertices_hpg,
        dump_hpg,
        dumpVertex_hpg,
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

void constructAcyclic_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph) {
    DEBUG_ERROR_IF(hpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(pathGraph))

    construct_hpg(hpgraph, pathGraph);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    for (
        VertexPath* hpath;
        computeShortestCycle_vpath((hpath = pushEmpty_vpa(hpgraph->hpaths, hyperPathGraph)), hyperPathGraph);
    ) {
        uint32_t const parentId = hpgraph->hpaths->size - 1;

        /*
        puts("");
        dumpVertex_hpg(hpgraph, stdout, parentId);
        printf(":");
        dump_vpath(hpath, stdout);
        */

        for (uint32_t i = 0; i < hpath->len; i++) {
            uint32_t childId = hpath->array[i];
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->subsumptionMtx, 0, childId))

            VertexIterator itr[1];
            construct_vitr_sg(itr, hyperPathGraph);
            for (
                uint32_t pathId;
                hyperPathGraph->isValidVertex(hpgraph, (pathId = hyperPathGraph->nextVertexId_vitr(itr)));
            ) {
                if (pathId == parentId || contains_vpath(hpath, pathId)) continue;
                if (isConnected_gmtx(hpgraph->edgeMtx, childId, pathId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, parentId, pathId))
                if (isConnected_gmtx(hpgraph->edgeMtx, pathId, childId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, pathId, parentId))
            }
        }

        /*
        dump_hpg(hpgraph, stdout);
        */
    }
    pop_vpa(hpgraph->hpaths);
}

void constructPathTrace_hpg(VertexPath* const pathTrace, HyperPathGraph* const hpgraph, uint32_t const rootId) {
    DEBUG_ERROR_IF(pathTrace == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))
    DEBUG_ASSERT(rootId < hpgraph->hpaths->size)

    disconnectAll_gmtx(hpgraph->subsumptionMtx);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    if (pathTrace->isAllocated) {
        flush_vpath(pathTrace);
        pathTrace->graph = hyperPathGraph;
    } else {
        constructEmpty_vpath(pathTrace, hyperPathGraph);
    }

    extend_vpath(pathTrace, rootId, 0);

    VertexPath secondTrace[1];
    constructEmpty_vpath(secondTrace, hyperPathGraph);

    VertexPath partialTrace[1] = {NOT_A_VPATH};

    VertexPath* current = pathTrace;
    VertexPath* next    = secondTrace;

    while (current->len != next->len) {
        flush_vpath(next);

        for (uint32_t i = 0; i < current->len; i++) {
            uint32_t const prevPathId   = current->array[(i + current->len - 1) % current->len];
            uint32_t const pathId       = current->array[i];
            uint32_t const nextPathId   = current->array[(i + 1) % current->len];

            if (hpgraph->pathGraph->isValidVertex(hpgraph->pathGraph->graphPtr, pathId)) {
                extend_vpath(next, pathId, 0);
                continue;
            }

            clone_vpath(partialTrace, hpgraph->hpaths->array + pathId);
            DEBUG_ASSERT(partialTrace->len > 0)

            uint32_t nRotations = partialTrace->len << 1;
            while (
                (prevPathId != pathId && !isValidEdge_hpg(hpgraph, prevPathId, partialTrace->array[0])) ||
                (nextPathId != pathId && !isValidEdge_hpg(hpgraph, partialTrace->array[partialTrace->len - 1], nextPathId))
            ) {
                nRotations--;
                DEBUG_ASSERT(nRotations > 0)

                if (nRotations == partialTrace->len) {
                    extend_vpath(partialTrace, partialTrace->array[0], 0);
                } else {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(partialTrace))
                }
            }

            concat_vpath(next, partialTrace);
            while (++i < current->len)
                extend_vpath(next, current->array[i], 0);
            break;
        }

        VertexPath* const tmp   = current;
        current                 = next;
        next                    = tmp;
    }

    free_vpath(secondTrace);
    if (partialTrace->isAllocated)
        free_vpath(partialTrace);

    pathTrace->graph = hpgraph->pathGraph;
}

void constructTestPaths_hpg(VertexPathArray* const testPaths, HyperPathGraph* const hpgraph) {
    DEBUG_ERROR_IF(testPaths == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    constructEmpty_vpa(testPaths, VPATH_ARRAY_DEFAULT_INITIAL_CAP);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)hpgraph->pathGraph->graphPtr;

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hyperPathGraph);
    uint32_t const s_id = nextVertexId_svitr_hpg(svitr);
    DEBUG_ASSERT(isValidVertex_hpg(hpgraph, s_id))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, hyperPathGraph, s_id);
    uint32_t const rootId = nextVertexId_nitr_hpg(itr);

    VertexPath pathTrace[1] = {NOT_A_VPATH};
    constructPathTrace_hpg(pathTrace, hpgraph, rootId);

    uint32_t shortestLen        = 0xFFFFFFFF;
    VertexPath* shortestPath    = NULL;

    for (uint32_t nRotations = pathTrace->len - 1; nRotations > 0; nRotations--) {
        if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, s_id, pathTrace->array[0])) {
            VertexPath* const testPath = pushEmpty_vpa(testPaths, vpgraph->graph);
            constructTestPath_vpg(testPath, vpgraph, pathTrace);

            if (testPath->len < shortestLen) {
                shortestLen     = testPath->len;
                shortestPath    = testPath;
            }
        }

        DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(pathTrace))
    }

    DEBUG_ERROR_IF(shortestPath == NULL)

    if (shortestPath > testPaths->array) {
        VertexPath tmp[1];
        memcpy(tmp, testPaths->array, sizeof(VertexPath));
        memcpy(testPaths->array, shortestPath, sizeof(VertexPath));
        memcpy(shortestPath, tmp, sizeof(VertexPath));
    }
    testPaths->size = 1;

    free_vpath(pathTrace);
}

void dump_hpg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hyperPathGraph);
    uint32_t const s_id = hyperPathGraph->nextVertexId_svitr(svitr);
    DEBUG_ASSERT(hyperPathGraph->isValidVertex(graphPtr, s_id))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, hyperPathGraph, s_id);
    for (
        uint32_t neighborId;
        hyperPathGraph->isValidVertex(graphPtr, (neighborId = hyperPathGraph->nextVertexId_nitr(itr)));
    ) {
        hyperPathGraph->dumpVertex(graphPtr, output, s_id);
        fputs(" ->", output);
        hyperPathGraph->dumpVertex(graphPtr, output, neighborId);
        fputs(";\n", output);
    }

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, hyperPathGraph);
    for (
        uint32_t vertexId;
        hyperPathGraph->isValidVertex(graphPtr, (vertexId = hyperPathGraph->nextVertexId_vitr(vitr)));
    ) {
        if (vertexId == s_id) continue;
        construct_nitr_sg(itr, hyperPathGraph, vertexId);

        for (
            uint32_t neighborId;
            hyperPathGraph->isValidVertex(graphPtr, (neighborId = hyperPathGraph->nextVertexId_nitr(itr)));
        ) {
            hyperPathGraph->dumpVertex(graphPtr, output, vertexId);
            fputs(" ->", output);
            hyperPathGraph->dumpVertex(graphPtr, output, neighborId);
            fputs(";\n", output);
        }
    }
}

void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    DEBUG_ASSERT(isValidVertex_hpg(graphPtr, vertexId))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    StartVertexIterator itr[1];
    construct_svitr_sg(itr, hyperPathGraph);
    uint32_t const startVertexId = hyperPathGraph->nextVertexId_svitr(itr);
    if (startVertexId == vertexId)
        fputs(" s", output);
    else if (vertexId < startVertexId)
        fprintf(output, " p%"PRIu32, vertexId);
    else
        fprintf(output, " h%"PRIu32, vertexId - startVertexId - 1);
}

void free_hpg(HyperPathGraph* const hpgraph) {
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    free_vpa(hpgraph->hpaths);
    free_gmtx(hpgraph->edgeMtx);
    free_gmtx(hpgraph->subsumptionMtx);
    *hpgraph = NOT_A_HPATH_GRAPH;
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

    return  sourceVertexId < hpgraph->hpaths->size                              &&
            targetVertexId < hpgraph->hpaths->size                              &&
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

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;
    itr->nextNeighborId                 = hpgraph->hpaths->size - 1;
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

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;
    itr->nextVertexId                   = hpgraph->hpaths->size - 1;
}

