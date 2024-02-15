#include <inttypes.h>
#include <stdlib.h>
#include "padkit/debug.h"
#include "vpathgraph.h"

void construct_vpg(VertexPathGraph* const vpgraph, VertexPathArray const* const vpaths) {
    DEBUG_ERROR_IF(vpgraph == NULL)
    DEBUG_ASSERT(isValid_vpa(vpaths))

    uint32_t const sz = vpaths->size;

    vpgraph->vpaths     = vpaths;
    vpgraph->splices    = malloc((size_t)sz * sizeof(VertexPath*));
    DEBUG_ERROR_IF(vpgraph->splices == NULL)

    VertexPath connector[1] = {NOT_A_VPATH};
    for (uint32_t i = 0; i < sz; i++) {
        VertexPath* const p_i = vpaths->array + i;
        DEBUG_ASSERT(p_i->len > 0)

        uint32_t const from = p_i->array[p_i->len - 1];

        vpgraph->splices[i] = calloc((size_t)sz, sizeof(VertexPath));
        DEBUG_ERROR_IF(vpgraph->splices[i] == NULL)

        for (uint32_t j = 0; j < sz; j++) {
            if (i == j) continue;

            VertexPath* const p_j = vpaths->array + j;
            DEBUG_ASSERT(p_j->len > 0)

            uint32_t const to = p_j->array[0];

            VertexPath* const splice_ij = vpgraph->splices[i] + j;

            uint32_t const overlapStartPosition = findLargestOverlap_vpath(p_i, p_j);
            if (overlapStartPosition != 0xFFFFFFFF) {
                constructEmpty_vpath(splice_ij, vpaths->graph);
                for (uint32_t k = 0; k < overlapStartPosition; k++)
                    extend_vpath(splice_ij, p_i->array[k], 0);
            } else if (computeShortest_vpath(connector, vpaths->graph, from, to)) {
                clone_vpath(splice_ij, p_i);
                concat_vpath(splice_ij, connector);
            }

            if (!isValid_vpath(splice_ij)) continue;

            for (uint32_t k = 0; k < sz; k++) {
                if (k == i || k == j) continue;

                VertexPath* const p_k = vpaths->array + k;
                DEBUG_ASSERT(p_k->len > 0)

                if (isSubPath_vpath(p_k, splice_ij)) {
                    invalidate_vpath(splice_ij);
                    break;
                }
            }
        }
    }
    if (connector->isAllocated)
        free_vpath(connector);
}

void dump_vpg(VertexPathGraph* const vpgraph, FILE* const output) {
    DEBUG_ASSERT(isValid_vpg(vpgraph))
    DEBUG_ERROR_IF(output == NULL)

    uint32_t const sz = vpgraph->vpaths->size;

    for (uint32_t i = 0; i < sz; i++) {
        for (uint32_t j = 0; j < sz; j++) {
            if (i == j) continue;

            VertexPath* const splice_ij = vpgraph->splices[i] + j;
            if (!isValid_vpath(splice_ij)) continue;

            printf("p%"PRIu32" -> p%"PRIu32"\n", i, j);
        }
    }
}

void free_vpg(VertexPathGraph* const vpgraph) {
    DEBUG_ASSERT(isValid_vpg(vpgraph))

    uint32_t const sz = vpgraph->vpaths->size;

    for (uint32_t i = 0; i < sz; i++) {
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

bool isValid_vpg(VertexPathGraph const* const vpgraph) {
    return vpgraph != NULL && vpgraph->splices != NULL && isValid_vpa(vpgraph->vpaths);
}
