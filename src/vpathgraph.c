#include <inttypes.h>
#include <stdlib.h>
#include "padkit/debug.h"
#include "vpathgraph.h"

void construct_vpg(VertexPathGraph* const vpgraph, SimpleGraph const* const graph, VertexPathArray const* const vpaths) {
    DEBUG_ERROR_IF(vpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_vpa(vpaths))

    uint32_t const sz   = vpaths->size;
    vpgraph->graph      = graph;
    vpgraph->vpaths     = vpaths;
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(vpgraph->spliceMtx, sz + 1, sz))

    VertexPath splice[1] = {NOT_A_VPATH};
    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i = vpaths->array + i;
        DEBUG_ASSERT(p_i->len > 0)
        DEBUG_ASSERT(p_i->graph == graph)

        for (uint32_t j = 0; j < sz; j++) {
            if (i == j) continue;

            VertexPath* const p_j = vpaths->array + j;
            DEBUG_ASSERT(p_j->len > 0)

            clone_vpath(splice, p_i);
            if (!splice_vpath(splice, p_j)) continue;

            connect_gmtx(vpgraph->spliceMtx, i, j);
            for (uint32_t k = 0; k < sz; k++) {
                if (k == i || k == j) continue;

                VertexPath* const p_k = vpaths->array + k;
                DEBUG_ASSERT(p_k->len > 0)

                if (isSubPath_vpath(p_k, splice)) {
                    disconnect_gmtx(vpgraph->spliceMtx, i, j);
                    break;
                }
            }
        }
    }

    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i       = vpaths->array + i;
        uint32_t const target       = p_i->array[0];

        if (!computeShortestInitializer_vpath(splice, graph, target))
            continue;

        DEBUG_ASSERT(isValid_vpath(splice))

        concat_vpath(splice, p_i);
        connect_gmtx(vpgraph->spliceMtx, sz, i);
        for (uint32_t k = 0; k < sz; k++) {
            if (k == i) continue;

            VertexPath* const p_k = vpaths->array + k;
            DEBUG_ASSERT(p_k->len > 0)

            if (isSubPath_vpath(p_k, splice)) {
                disconnect_gmtx(vpgraph->spliceMtx, sz, i);
                break;
            }
        }
    }

    if (splice->isAllocated)
        free_vpath(splice);
}

void construct_sgi_vpg(SimpleGraph* const graph, VertexPathGraph const* const vpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_vpg(vpgraph))

    *graph = (SimpleGraph){
        vpgraph,
        countEdges_vpg,
        countVertices_vpg,
        dump_vpg,
        dumpVertex_vpg,
        isValid_vpg,
        isValid_nitr_vpg,
        isValid_svitr_vpg,
        isValid_vitr_vpg,
        isValidEdge_vpg,
        isValidVertex_vpg,
        nextVertexId_nitr_vpg,
        nextVertexId_svitr_vpg,
        nextVertexId_vitr_vpg,
        setFirstNextId_nitr_vpg,
        setFirstNextId_svitr_vpg,
        setFirstNextId_vitr_vpg
    };
}

uint32_t countEdges_vpg(void const* const graphPtr) {
    static VertexPathGraph const* vpgraph   = NULL;
    static uint32_t countEdges              = 0xFFFFFFFF;

    DEBUG_ASSERT(isValid_vpg(graphPtr))
    if (vpgraph == graphPtr) return countEdges;

    vpgraph = (VertexPathGraph const*)graphPtr;

    uint32_t const sz = vpgraph->vpaths->size;

    countEdges = 0;
    for (uint32_t i = 0; i <= sz; i++)
        for (uint32_t j = 0; j < sz; j++)
            countEdges += isValidEdge_vpg(graphPtr, i, j);

    return countEdges;
}

uint32_t countVertices_vpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    return vpgraph->vpaths->size + 1;
}

void dump_vpg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)

    uint32_t const sz = vpgraph->vpaths->size;

    for (uint32_t i = 0; i < sz; i--) {
        if (isValidEdge_vpg(vpgraph, sz, i)) {
            dumpVertex_vpg(graphPtr, output, sz);
            fputs(" ->", output);
            dumpVertex_vpg(graphPtr, output, i);
            fputs(";\n", output);
        }
    }

    for (uint32_t i = 0; i < sz; i++) {
        for (uint32_t j = 0; j < sz; j++) {
            if (isValidEdge_vpg(vpgraph, i, j)) {
                dumpVertex_vpg(graphPtr, output, i);
                fputs(" ->", output);
                dumpVertex_vpg(graphPtr, output, j);
                fputs(";\n", output);
            }
        }
    }
}

void dumpVertex_vpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_vpg(vpgraph, vertexId))

    if (vertexId == vpgraph->vpaths->size)
        fputs(" s", output);
    else
        fprintf(output, " p%"PRIu32, vertexId);
}

void free_vpg(VertexPathGraph* const vpgraph) {
    DEBUG_ASSERT(isValid_vpg(vpgraph))
    free_gmtx(vpgraph->spliceMtx);
    *vpgraph = NOT_A_VPATH_GRAPH;
}

bool isValid_nitr_vpg(NeighborIterator const* const itr) {
    return itr != NULL && isValid_vpg(itr->graphPtr) && isValidVertex_vpg(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_vpg(StartVertexIterator const* const itr) {
    return itr != NULL && isValid_vpg(itr->graphPtr);
}

bool isValid_vitr_vpg(VertexIterator const* const itr) {
    return itr != NULL && isValid_vpg(itr->graphPtr);
}

bool isValid_vpg(void const* const graphPtr) {
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    return vpgraph != NULL && isValid_sg(vpgraph->graph) && isValid_vpa(vpgraph->vpaths) && isValid_gmtx(vpgraph->spliceMtx);
}

bool isValidEdge_vpg(void const* const graphPtr, uint32_t sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;

    return  isValidVertex_vpg(graphPtr, sourceVertexId)                             &&
            isValidVertex_vpg(graphPtr, targetVertexId)                             &&
            isConnected_gmtx(vpgraph->spliceMtx, sourceVertexId, targetVertexId);
}

bool isValidVertex_vpg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;

    return vertexId <= vpgraph->vpaths->size;
}

uint32_t nextVertexId_nitr_vpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_vpg(itr))

    while (!isValidEdge_vpg(itr->graphPtr, itr->vertexId, itr->nextNeighborId)) {
        if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextNeighborId--;
    }

    return itr->nextNeighborId--;
}

uint32_t nextVertexId_svitr_vpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_vpg(itr))

    if (isValidVertex_vpg(itr->graphPtr, itr->nextVertexId)) {
        itr->nextVertexId = 0xFFFFFFFF;
        VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;
        return vpgraph->vpaths->size;
    } else {
        return 0xFFFFFFFF;
    }
}

uint32_t nextVertexId_vitr_vpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_vpg(itr))

    if (isValidVertex_vpg(itr->graphPtr, itr->nextVertexId))
        return itr->nextVertexId--;
    else
        return 0xFFFFFFFF;
}

void setFirstNextId_nitr_vpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_vpg(itr))

    VertexPathGraph const* const vpgraph    = (VertexPathGraph const*)itr->graphPtr;
    itr->nextNeighborId                     = vpgraph->vpaths->size - 1;
}

void setFirstNextId_svitr_vpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_vpg(itr))

    VertexPathGraph const* const vpgraph    = (VertexPathGraph const*)itr->graphPtr;
    itr->nextVertexId                       = vpgraph->vpaths->size;
}

void setFirstNextId_vitr_vpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_vpg(itr))

    VertexPathGraph const* const vpgraph    = (VertexPathGraph const*)itr->graphPtr;
    itr->nextVertexId                       = vpgraph->vpaths->size;
}

void splicePathTraces_vpg(VertexPath* const splice, VertexPathGraph const* const vpgraph, VertexPathArray const* const pathTraces) {
    DEBUG_ERROR_IF(splice == NULL)
    DEBUG_ASSERT(isValid_vpg(vpgraph))
    DEBUG_ASSERT(isValid_vpa(pathTraces))

    if (splice->isAllocated) {
        flush_vpath(splice);
        splice->graph = vpgraph->graph;
    } else {
        constructEmpty_vpath(splice, vpgraph->graph);
    }

    VertexPath const* firstTrace        = pathTraces->array;
    VertexPath const* const lastTrace   = pathTraces->array + pathTraces->size - 1;

    if (firstTrace > lastTrace) return;
    DEBUG_ASSERT(isValid_vpath(firstTrace))
    while (firstTrace->len == 0) {
        firstTrace++;
        if (firstTrace > lastTrace) return;
        DEBUG_ASSERT(isValid_vpath(firstTrace))
    }

    uint32_t const firstPathId = firstTrace->array[0];
    DEBUG_ASSERT(firstTrace->graph->isValidVertex(firstTrace->graph->graphPtr, firstPathId))

    VertexPath const* const firstPath = vpgraph->vpaths->array + firstPathId;
    DEBUG_ASSERT(isValid_vpath(firstPath))

    DEBUG_ASSERT(firstPath->len > 0)
    uint32_t const firstVertexId = firstPath->array[0];
    DEBUG_ASSERT(firstPath->graph->isValidVertex(firstPath->graph->graphPtr, firstVertexId))

    DEBUG_ASSERT_NDEBUG_EXECUTE(computeShortestInitializer_vpath(splice, vpgraph->graph, firstVertexId))
    concat_vpath(splice, firstPath);

    GraphMatrix coverMtx[1];
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(coverMtx, 1, vpgraph->vpaths->size))
    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, firstPathId))

    for (uint32_t candidateId = 0; candidateId < vpgraph->vpaths->size; candidateId++) {
        if (candidateId == firstPathId || isConnected_gmtx(coverMtx, 0, candidateId)) continue;

        VertexPath const* const candidate = vpgraph->vpaths->array + candidateId;

        if (isSubPath_vpath(candidate, splice))
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, candidateId))
    }

    VertexPath subsplice[1] = {NOT_A_VPATH};

    uint32_t lastSplicedPathId = firstPathId;
    bool pathSkipped = 1;
    VertexPath const* pathTrace;
    for (pathTrace = firstTrace; pathTrace <= lastTrace; pathTrace++) {
        DEBUG_ASSERT(isValid_vpath(pathTrace))

        for (uint32_t i = !(pathTrace > firstTrace); i < pathTrace->len; i++){
            uint32_t const vpathId          = pathTrace->array[i];
            VertexPath const* const vpath   = vpgraph->vpaths->array + vpathId;
            if (isConnected_gmtx(coverMtx, 0, vpathId)) {
                pathSkipped = 1;
                continue;
            }

            splice_vpath(splice, vpath);
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, vpathId))

            if (pathSkipped) {
                VertexPath const* const lastSplicedPath = vpgraph->vpaths->array + lastSplicedPathId;
                clone_vpath(subsplice, lastSplicedPath);
                splice_vpath(subsplice, vpath);

                for (uint32_t candidateId = 0; candidateId < vpgraph->vpaths->size; candidateId++) {
                    if (candidateId == vpathId || isConnected_gmtx(coverMtx, 0, candidateId)) continue;

                    VertexPath const* const candidate = vpgraph->vpaths->array + candidateId;

                    if (isSubPath_vpath(candidate, subsplice))
                        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, candidateId))
                }
            }

            lastSplicedPathId = vpathId;
            pathSkipped = 0;
        }

        pathSkipped = 1;
    }

    free_gmtx(coverMtx);
    if (subsplice->isAllocated) free_vpath(subsplice);
}
