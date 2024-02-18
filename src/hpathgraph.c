/**
 * @file hpathgraph.c
 * @brief Implements the functions defined in hpathgraph.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
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

void constructPathTrace_hpg(VertexPath* const pathTrace, HyperPathGraph const* const hpgraph, uint32_t const rootId) {
    DEBUG_ERROR_IF(pathTrace == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))
    DEBUG_ASSERT(rootId < hpgraph->hpaths->size)

    if (pathTrace->isAllocated) {
        flush_vpath(pathTrace);
        pathTrace->graph = hpgraph->pathGraph;
    } else {
        constructEmpty_vpath(pathTrace, hpgraph->pathGraph);
    }

    if (hpgraph->pathGraph->isValidVertex(hpgraph->pathGraph->graphPtr, rootId)) {
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(pathTrace, rootId, 1))
        return;
    }

    VertexPath const* const hpath = hpgraph->hpaths->array + rootId;
    DEBUG_ASSERT(hpath->len > 1)

    constructPathTrace_hpg(pathTrace, hpgraph, hpath->array[0]);
    DEBUG_ASSERT(pathTrace->len > 0)

    VertexPath nextTrace[1] = {NOT_A_VPATH};
    for (uint32_t i = 1; i < hpath->len; i++) {
        constructPathTrace_hpg(nextTrace, hpgraph, hpath->array[i]);
        DEBUG_ASSERT(nextTrace->len > 0)

        uint32_t from = pathTrace->array[pathTrace->len - 1];
        uint32_t to   = nextTrace->array[0];

        if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, from, to)) {
            concat_vpath(pathTrace, nextTrace);
            continue;
        }

        bool spliceEstablished = 0;
        if (canRotate_vpath(pathTrace)) {
            if (canRotate_vpath(nextTrace)) {
                for (uint32_t n = 1; !spliceEstablished && n <= pathTrace->len; n++) {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(pathTrace))
                    from = pathTrace->array[pathTrace->len - 1];
                    if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, from, to)) {
                        concat_vpath(pathTrace, nextTrace);
                        spliceEstablished = 1;
                    }
                    for (uint32_t m = 1; !spliceEstablished && m <= nextTrace->len; m++) {
                        DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(nextTrace))
                        to = nextTrace->array[0];
                        if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, from, to)) {
                            concat_vpath(pathTrace, nextTrace);
                            spliceEstablished = 1;
                        }
                    }
                }
            } else {
                for (uint32_t n = 1; !spliceEstablished && n <= pathTrace->len; n++) {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(pathTrace))
                    from = pathTrace->array[pathTrace->len - 1];
                    if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, from, to)) {
                        concat_vpath(pathTrace, nextTrace);
                        spliceEstablished = 1;
                    }
                }
            }
        } else {
            DEBUG_ASSERT(canRotate_vpath(nextTrace))
            for (uint32_t m = 1; !spliceEstablished && m <= nextTrace->len; m++) {
                DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(nextTrace))
                to = nextTrace->array[0];
                if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, from, to)) {
                    concat_vpath(pathTrace, nextTrace);
                    spliceEstablished = 1;
                }
            }
        }
        DEBUG_ASSERT(spliceEstablished)
    }
    if (nextTrace->isAllocated)
        free_vpath(nextTrace);
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
