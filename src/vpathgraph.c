/**
 * @file vpathgraph.c
 * @brief Implements the functions defined in vpathgraph.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <stdlib.h>
#include "padkit/debug.h"
#include "vpathgraph.h"

void construct_vpg(
    SimpleGraph* const pathGraph, VertexPathGraph* const vpgraph,
    SimpleGraph const* const graph, VertexPathArray const* const vpaths,
    int const optimizationLevel
) {
    DEBUG_ERROR_IF(pathGraph == NULL)
    DEBUG_ERROR_IF(vpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_vpa(vpaths))

    uint32_t const sz   = vpaths->size;
    vpgraph->graph      = graph;
    vpgraph->vpaths     = vpaths;
    construct_gmtx(vpgraph->spliceMtx, sz + 1, sz);

    VertexPath splice[1] = {NOT_A_VPATH};

    switch (optimizationLevel) {
        case 2:
            for (uint32_t i = 0; i < sz - 1; i++) {
                VertexPath* const p_i = vpaths->array + i;
                DEBUG_ASSERT(p_i->len == 1)
                DEBUG_ASSERT(p_i->graph == graph)

                uint32_t const v_i = p_i->array[0];

                for (uint32_t j = i + 1; j < sz; j++) {
                    VertexPath* const p_j = vpaths->array + j;
                    DEBUG_ASSERT(p_j->len == 1)
                    DEBUG_ASSERT(p_j->graph == graph)

                    uint32_t const v_j = p_j->array[0];

                    if (graph->isValidEdge(graph->graphPtr, v_i, v_j))
                        connect_gmtx(vpgraph->spliceMtx, i, j);

                    if (graph->isValidEdge(graph->graphPtr, v_j, v_i))
                        connect_gmtx(vpgraph->spliceMtx, j, i);
                }
            }
            break;
        case 1:
            for (uint32_t i = 0; i < sz; i++) {
                VertexPath* const p_i = vpaths->array + i;
                DEBUG_ASSERT(p_i->len > 1)
                DEBUG_ASSERT(p_i->graph == graph)

                for (uint32_t j = 0; j < sz; j++) {
                    if (i == j) continue;

                    VertexPath* const p_j = vpaths->array + j;
                    DEBUG_ASSERT(p_j->len > 1)
                    DEBUG_ASSERT(p_j->graph == graph)

                    if (p_i->array[1] == p_j->array[0])
                        connect_gmtx(vpgraph->spliceMtx, i, j);
                }
            }
            break;
        case 0:
        default:
            for (uint32_t i = 0; i < sz; i++) {
                VertexPath* const p_i = vpaths->array + i;
                DEBUG_ASSERT(p_i->len > 0)
                DEBUG_ASSERT(p_i->graph == graph)

                for (uint32_t j = 0; j < sz; j++) {
                    if (i == j) continue;

                    VertexPath* const p_j = vpaths->array + j;
                    DEBUG_ASSERT(p_j->len > 0)
                    DEBUG_ASSERT(p_j->graph == graph)

                    clone_vpath(splice, p_i);
                    if (!splice_vpath(splice, p_j)) continue;

                    connect_gmtx(vpgraph->spliceMtx, i, j);
                    if (splice->len <= p_i->len + 1) continue;

                    for (uint32_t k = 0; k < sz; k++) {
                        if (k == i || k == j) continue;

                        VertexPath* const p_k = vpaths->array + k;
                        DEBUG_ASSERT(p_k->len > 0)
                        DEBUG_ASSERT(p_k->graph == graph)

                        if (isSubPath_vpath(p_k, splice)) {
                            disconnect_gmtx(vpgraph->spliceMtx, i, j);
                            break;
                        }
                    }
                }
            }
    }

    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i = vpaths->array + i;
        DEBUG_ASSERT(p_i->len > 0)
        DEBUG_ASSERT(p_i->graph == graph)

        uint32_t const target = p_i->array[0];

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

    construct_sgi_vpg(pathGraph, vpgraph);
}

void construct_sgi_vpg(SimpleGraph* const graph, VertexPathGraph* const vpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_vpg(vpgraph))

    *graph = (SimpleGraph){
        vpgraph,
        countEdges_vpg,
        countVertices_vpg,
        dump_vpg,
        dumpVertex_vpg,
        free_vpg,
        highestVertexId_vpg,
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

void free_vpg(void* const graphPtr) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph* const vpgraph = (VertexPathGraph*)graphPtr;
    free_gmtx(vpgraph->spliceMtx);
    *vpgraph = NOT_A_VPATH_GRAPH;
}

uint32_t highestVertexId_vpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    return vpgraph->vpaths->size;
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
    return  vpgraph != NULL                 &&
            isValid_sg(vpgraph->graph)      &&
            isValid_vpa(vpgraph->vpaths)    &&
            isValid_gmtx(vpgraph->spliceMtx);
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
