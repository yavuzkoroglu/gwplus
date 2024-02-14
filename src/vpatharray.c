/**
 * @file vpatharray.c
 * @brief Implements the functions defined in vpatharray.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/reallocate.h"
#include "vpatharray.h"

void constructAllPrimePaths_vpa(VertexPathArray* const primePaths, TestableGraph const* const graph, uint32_t const initial_cap) {
    DEBUG_ERROR_IF(primePaths == NULL)
    DEBUG_ASSERT(isValid_tg(graph))
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    constructEmpty_vpa(primePaths, graph, initial_cap);

    if (countVertices_tg(graph) == 0) return;

    VertexPathArray stack[1];
    constructEmpty_vpa(stack, graph, initial_cap);

    VertexIterator vitr[1];
    construct_vitr_tg(vitr, graph);
    for (
        uint32_t vertexId;
        (vertexId = graph->nextVertexId_vitr(vitr)) != 0xFFFFFFFF;
    ) {
        VertexPath* const vpath = pushEmpty_vpa(stack);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(vpath, vertexId, 1))
    }

    VertexPath vpath[1] = {NOT_A_VPATH};
    while (stack->size > 0) {
        clone_vpath(vpath, pop_vpa(stack));

        DEBUG_ASSERT(vpath->len > 0)
        uint32_t const lastVertexId = vpath->array[vpath->len - 1];

        NeighborIterator nitr[1];
        construct_nitr_tg(nitr, graph, lastVertexId);
        size_t extensions_count = 0;
        for (
            uint32_t neighborId;
            (neighborId = graph->nextVertexId_nitr(nitr)) != 0xFFFFFFFF;
        ) {
            VertexPath* const clone = pushClone_vpa(stack, vpath);
            if (extend_vpath(clone, neighborId, 1)) {
                extensions_count++;
                if (clone->isCycle) {
                    pushClone_vpa(primePaths, pop_vpa(stack));
                } else if (clone->isPrime) {
                    VertexPath const* const primePath = pop_vpa(stack);
                    for (uint32_t i = primePaths->size - 1; i != 0xFFFFFFFF; i--) {
                        VertexPath* const p_i = primePaths->array + i;
                        DEBUG_ASSERT(isValid_vpath(p_i))

                        if (!p_i->isCycle && isSubPath_vpath(p_i, primePath)) {
                            removePath_vpa(primePaths, i);
                        }
                    }
                    pushClone_vpa(primePaths, primePath);
                }
            } else {
                pop_vpa(stack);
            }
        }

        if (extensions_count > 0) continue;

        vpath->isPrime = 1;
        for (uint32_t i = primePaths->size - 1; i != 0xFFFFFFFF; i--) {
            VertexPath* const p_i = primePaths->array + i;
            DEBUG_ASSERT(isValid_vpath(p_i))

            if (isSubPath_vpath(vpath, p_i)) {
                vpath->isPrime = 0;
                break;
            } else if (!p_i->isCycle && isSubPath_vpath(p_i, vpath)) {
                removePath_vpa(primePaths, i);
            }
        }

        if (vpath->isPrime)
            pushClone_vpa(primePaths, vpath);
    }

    free_vpa(stack);
    free_vpath(vpath);
}

void constructEmpty_vpa(VertexPathArray* const vpaths, TestableGraph const* const graph, uint32_t const initial_cap) {
    DEBUG_ERROR_IF(vpaths == NULL)
    DEBUG_ASSERT(isValid_tg(graph))
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    vpaths->graph   = graph;
    vpaths->cap     = initial_cap;
    vpaths->size    = 0;
    vpaths->array   = calloc(initial_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(vpaths->array == NULL)
}

void dump_vpa(VertexPathArray const* const vpaths, FILE* const output) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    DEBUG_ERROR_IF(output == NULL)

    for (uint32_t i = 0; i < vpaths->size; i++) {
        VertexPath const* const vpath = vpaths->array + i;
        DEBUG_ASSERT(isValid_vpath(vpath))

        dump_vpath(vpath, output);
    }
}

void flush_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    vpaths->size = 0;
}

void free_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))

    for (VertexPath* vpath = vpaths->array; vpath < vpaths->array + vpaths->cap; vpath++)
        if (vpath->isAllocated)
            free_vpath(vpath);

    free(vpaths->array);
    vpaths->array = NULL;
}

void increaseCapIfNecessary_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    RECALLOC_IF_NECESSARY(VertexPath, vpaths->array, uint32_t, vpaths->cap, vpaths->size, RECALLOC_ERROR)
}

bool isValid_vpa(VertexPathArray const* const vpaths) {
    return  vpaths != NULL                                  &&
            isValid_tg(vpaths->graph)                       &&
            vpaths->cap != 0 && vpaths->cap != 0xFFFFFFFF   &&
            vpaths->size <= vpaths->cap                     &&
            vpaths->array != NULL;
}

VertexPath* pop_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))

    if (vpaths->size == 0) return NULL;

    return vpaths->array + --vpaths->size;
}

VertexPath* pushClone_vpa(VertexPathArray* const vpaths, VertexPath const* const vpath) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    DEBUG_ASSERT(isValid_vpath(vpath))
    DEBUG_ASSERT(vpaths->graph == vpath->graph)

    increaseCapIfNecessary_vpa(vpaths);
    VertexPath* const clone = vpaths->array + vpaths->size++;
    clone_vpath(clone, vpath);
    return clone;
}

VertexPath* pushEmpty_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))

    increaseCapIfNecessary_vpa(vpaths);
    VertexPath* const vpath = vpaths->array + vpaths->size++;

    if (vpath->isAllocated) {
        DEBUG_ASSERT(vpath->graph == vpaths->graph)
        flush_vpath(vpath);
    } else {
        constructEmpty_vpath(vpath, vpaths->graph);
    }

    return vpath;
}

void removePath_vpa(VertexPathArray* const vpaths, uint32_t const vpathId) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    DEBUG_ASSERT(vpathId < vpaths->size)

    VertexPath* const vpath = vpaths->array + vpathId;
    invalidate_vpath(vpath);

    VertexPath tmp[1];
    memcpy(tmp, vpath, sizeof(VertexPath));

    size_t const size_in_bytes = (size_t)(--vpaths->size - vpathId) * sizeof(VertexPath);
    memmove(vpath, vpath + 1, size_in_bytes);

    memcpy(vpaths->array + vpaths->size, tmp, sizeof(VertexPath));
}
