#include <inttypes.h>
#include <stdlib.h>
#include "padkit/debug.h"
#include "vpathgraph.h"

void construct_vpg(VertexPathGraph* const vpgraph, VertexPathArray const* const vpaths) {
    DEBUG_ERROR_IF(vpgraph == NULL)
    DEBUG_ASSERT(isValid_vpa(vpaths))

    uint32_t const sz = vpaths->size;

    vpgraph->vpaths     = vpaths;
    vpgraph->splices    = malloc((size_t)(sz + 1) * sizeof(VertexPath*));
    DEBUG_ERROR_IF(vpgraph->splices == NULL)

    VertexPath connector[1] = {NOT_A_VPATH};
    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i = vpaths->array + i;
        DEBUG_ASSERT(p_i->len > 0)

        vpgraph->splices[i] = calloc((size_t)sz, sizeof(VertexPath));
        DEBUG_ERROR_IF(vpgraph->splices[i] == NULL)

        for (uint32_t j = 0; j < sz; j++) {
            if (i == j) continue;

            VertexPath* const p_j = vpaths->array + j;
            DEBUG_ASSERT(p_j->len > 0)

            VertexPath* const splice_ij = vpgraph->splices[i] + j;

            if (!splice_vpath(splice_ij, p_i, p_j)) continue;

            clone_vpath(connector, splice_ij);
            concat_vpath(connector, p_j);
            for (uint32_t k = 0; k < sz; k++) {
                if (k == i || k == j) continue;

                VertexPath* const p_k = vpaths->array + k;
                DEBUG_ASSERT(p_k->len > 0)

                if (isSubPath_vpath(p_k, connector)) {
                    invalidate_vpath(splice_ij);
                    break;
                }
            }
        }
    }

    vpgraph->splices[sz] = calloc((size_t)sz, sizeof(VertexPath));
    DEBUG_ERROR_IF(vpgraph->splices[sz] == NULL)
    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i       = vpaths->array + i;
        uint32_t const target       = p_i->array[0];
        VertexPath* const splice_si = vpgraph->splices[sz] + i;

        if (!computeShortestInitializer_vpath(splice_si, vpaths->graph, target))
            continue;

        DEBUG_ASSERT(isValid_vpath(splice_si))

        clone_vpath(connector, splice_si);
        concat_vpath(connector, p_i);
        for (uint32_t k = 0; k < sz; k++) {
            if (k == i) continue;

            VertexPath* const p_k = vpaths->array + k;
            DEBUG_ASSERT(p_k->len > 0)

            if (isSubPath_vpath(p_k, connector)) {
                invalidate_vpath(splice_si);
                break;
            }
        }
    }

    if (connector->isAllocated)
        free_vpath(connector);
}

void constructTgi_vpg(TestableGraph* const graph, VertexPathGraph const* const vpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_vpg(vpgraph))

    graph->graphPtr             = vpgraph;
    graph->countEdges           = countEdges_vpg;
    graph->countVertices        = countVertices_vpg;
    graph->dump                 = dump_vpg;
    graph->dumpVertex           = dumpVertex_vpg;
    graph->isValid              = isValid_vpg;
    graph->isValid_nitr         = isValid_nitr_vpg;
    graph->isValid_svitr        = isValid_svitr_vpg;
    graph->isValid_vitr         = isValid_vitr_vpg;
    graph->isValidVertex        = isValidVertex_vpg;
    graph->nextVertexId_nitr    = nextVertexId_nitr_vpg;
    graph->nextVertexId_svitr   = nextVertexId_svitr_vpg;
    graph->nextVertexId_vitr    = nextVertexId_vitr_vpg;
    graph->setFirstNextId_nitr  = setFirstNextId_nitr_vpg;
    graph->setFirstNextId_svitr = setFirstNextId_svitr_vpg;
    graph->setFirstNextId_vitr  = setFirstNextId_vitr_vpg;
}

uint32_t countEdges_vpg(void const* const graphPtr) {
    static VertexPathGraph const* graph = NULL;
    static uint32_t countEdges          = 0xFFFFFFFF;

    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;

    if (vpgraph == graph) return countEdges;

    graph = vpgraph;
    uint32_t const sz = graph->vpaths->size;

    countEdges = 0;
    for (uint32_t i = 0; i <= sz; i++) {
        for (uint32_t j = 0; j < sz; j++) {
            if (i == j) continue;

            VertexPath* const splice_ij = vpgraph->splices[i] + j;
            countEdges += isValid_vpath(splice_ij);
        }
    }

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

    for (uint32_t i = sz - 1; i != 0xFFFFFFFF; i--) {
        VertexPath* const splice_si = vpgraph->splices[sz] + i;
        if (!isValid_vpath(splice_si)) continue;

        fprintf(output, "s -> p%"PRIu32";\n", i);
    }

    for (uint32_t i = sz - 1; i != 0xFFFFFFFF; i--) {
        for (uint32_t j = sz - 1; j != 0xFFFFFFFF; j--) {
            if (i == j) continue;

            VertexPath* const splice_ij = vpgraph->splices[i] + j;
            if (!isValid_vpath(splice_ij)) continue;

            fprintf(output, "p%"PRIu32" -> p%"PRIu32";\n", i, j);
        }
    }
}

void dumpVertex_vpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_vpg(vpgraph, vertexId))

    if (vertexId == vpgraph->vpaths->size) {
        fputs("s\n", output);
    } else {
        fprintf(output, "p%"PRIu32":", vertexId);
        dump_vpath(vpgraph->vpaths->array + vertexId, output);
    }
}

void free_vpg(VertexPathGraph* const vpgraph) {
    DEBUG_ASSERT(isValid_vpg(vpgraph))

    uint32_t const sz = vpgraph->vpaths->size;

    for (uint32_t i = 0; i <= sz; i++) {
        for (uint32_t j = 0; j < sz; j++) {
            VertexPath* const splice_ij = vpgraph->splices[i] + j;
            if (splice_ij->isAllocated)
                free_vpath(splice_ij);
        }
        free(vpgraph->splices[i]);
    }
    free(vpgraph->splices);
    vpgraph->splices = NULL;
}

bool isValid_vpg(void const* const graphPtr) {
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;
    return vpgraph != NULL && vpgraph->splices != NULL && isValid_vpa(vpgraph->vpaths);
}

bool isValid_nitr_vpg(NeighborIterator const* const itr) {
    return itr != NULL && isValid_vpg(itr->graphPtr) && isValidVertex_vpg(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_vpg(StartVertexIterator const* const itr) {
    return itr != NULL && itr->graphPtr != NULL;
}

bool isValid_vitr_vpg(VertexIterator const* const itr) {
    return itr != NULL && isValid_vpg(itr->graphPtr);
}

bool isValidVertex_vpg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpg(graphPtr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)graphPtr;

    return vertexId <= vpgraph->vpaths->size;
}

uint32_t nextVertexId_nitr_vpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_vpg(itr))
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;

    if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;

    VertexPath const* splice_ij = vpgraph->splices[itr->vertexId] + itr->nextNeighborId--;
    while (!isValid_vpath(splice_ij) && itr->nextNeighborId)
        splice_ij = vpgraph->splices[itr->vertexId] + itr->nextNeighborId--;

    return itr->nextNeighborId;
}

uint32_t nextVertexId_svitr_vpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_vpg(itr))

    if (itr->nextVertexId == 0xFFFFFFFF) return 0xFFFFFFFF;

    itr->nextVertexId = 0xFFFFFFFF;
    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;
    return vpgraph->vpaths->size;
}

uint32_t nextVertexId_vitr_vpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_vpg(itr))

    if (itr->nextVertexId == 0xFFFFFFFF) return 0xFFFFFFFF;

    return itr->nextVertexId--;
}

void setFirstNextId_nitr_vpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_vpg(itr))

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;
    itr->nextNeighborId = vpgraph->vpaths->size - 1;
}

void setFirstNextId_svitr_vpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_vpg(itr))

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;
    itr->nextVertexId = vpgraph->vpaths->size;
}

void setFirstNextId_vitr_vpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_vpg(itr))

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)itr->graphPtr;
    itr->nextVertexId = vpgraph->vpaths->size;
}
