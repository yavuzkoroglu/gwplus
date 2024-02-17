/**
 * @file hpathgraph.c
 * @brief Implements the functions defined in hpathgraph.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "hpathgraph.h"

uint32_t countEdges_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hpgraph;

    SimpleGraph graph[1];
    construct_sgi_hpg(graph, hpgraph);

    return countEdges_default_sg(graph);
}

uint32_t countVertices_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hpgraph;

    SimpleGraph graph[1];
    construct_sgi_hpg(graph, hpgraph);

    return countVertices_default_sg(graph);
}

void construct_hpg(HyperPathGraph* const hpgraph, VertexPathGraph const* const vpgraph) {
    
}

void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph const* const hpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    graph = (SimpleGraph){
        hpgraph,
        countEdges_hpg,
        countVertices_hpg,
        dump_hpg,
        dumpVertex_hpg,
        isValid_hpg,
        isValid_nitr_hpg,
        isValid_svitr_hpg,
        isValid_vitr_hpg,
        isValidVertex_hpg,
        nextVertexId_nitr_hpg,
        nextVertexId_svitr_hpg,
        nextVertexId_vitr_hpg,
        setFirstNextId_nitr_hpg,
        setFirstNextId_svitr_hpg,
        setFirstNextId_vitr_hpg
    };
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

void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    DEBUG_ASSERT(isValidVertex_hpg(graphPtr, vertexId))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hpgraph;

    SimpleGraph graph[1];
    construct_sgi_hpg(graph, hpgraph);

    StartVertexIterator itr[1];
    construct_svitr_sg(itr, graph);
    for (
        uint32_t startVertexId;
        (startVertexId = graph->nextVertexId_svitr(itr)) != 0xFFFFFFFF;
    ) {
        if (startVertexId == vertexId) {
            fputs(" s", output);
            return;
        }
    }
    fprintf(output, " h%"PRIu32, vertexId);
}

void free_hpg(HyperPathGraph* const hpgraph) {
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    free_gmtx(hpgraph->edgeMtx);
    for (uint32_t i = 0; i < hpgraph->size; i++)
        free_vpath(hpaths[i].hpath);

    free(hpgraph->hpaths);
    *hpgraph = NOT_A_HPATH_GRAPH;
}

bool isValid_hpg(void const* const graphPtr) {
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hpgraph;
    return  hpgraph != NULL                 &&
            isValid_vpg(hpgraph->vpgraph)   &&
            isValid_gmtx(hpgraph->edgeMtx)  &&
            hpgraph->cap != 0               &&
            hpgraph->cap != 0xFFFFFFFF      &&
            hpgraph->size <= hpgraph->cap   &&
            hpgraph->hpats != NULL;
}

bool isValid_nitr_hpg(NeighborIterator* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr) && isValidVertex_hpg(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_hpg(StartVertexIterator* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValid_vitr_hpg(VertexIterator* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValidVertex_hpg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hpgraph;
    return vertexId < hpgraph->size;
}
