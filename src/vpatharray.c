/**
 * @file vpatharray.c
 * @brief Implements the functions defined in vpatharray.h
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <string.h>
#include "padkit/debug.h"
#include "padkit/reallocate.h"
#include "padkit/timestamp.h"
#include "vpatharray.h"

void constructAllKPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph, uint32_t const k) {
    DEBUG_ERROR_IF(vpaths == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(k == 0)
    DEBUG_ERROR_IF(k == 0xFFFFFFFF)

    if (k == 1) {
        constructVerticesAsPaths_vpa(vpaths, graph);
        return;
    }

    constructEmpty_vpa(vpaths, VPATH_ARRAY_DEFAULT_INITIAL_CAP);

    VertexPathArray stack[1] = {NOT_A_VPATH_ARRAY};
    constructVerticesAsPaths_vpa(stack, graph);

    VertexPath vpath[1] = {NOT_A_VPATH};
    while (stack->size > 0) {
        clone_vpath(vpath, pop_vpa(stack));
        DEBUG_ASSERT(vpath->len > 0)

        NeighborIterator itr[1];
        construct_nitr_sg(itr, graph, vpath->array[vpath->len - 1]);
        for (
            uint32_t neighborId;
            graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
        ) {
            VertexPath* const clone = pushClone_vpa(stack, vpath);
            extend_vpath(clone, neighborId, 0);
            if (clone->len == k) {
                pushClone_vpa(vpaths, clone);
                pop_vpa(stack);
            }
        }
    }

    free_vpa(stack);
    if (vpath->isAllocated) free_vpath(vpath);
}

#define VERBOSE_MSG(...) if (verbose) { printf("[%s] - ", get_timestamp()); printf(__VA_ARGS__); puts(""); }
void constructAllPrimePaths_vpa(VertexPathArray* const primePaths, SimpleGraph const* const graph, bool const verbose) {
    DEBUG_ERROR_IF(primePaths == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    constructEmpty_vpa(primePaths, VPATH_ARRAY_DEFAULT_INITIAL_CAP);

    if (graph->countVertices(graph->graphPtr) == 0) return;

    VertexPathArray stack[1] = {NOT_A_VPATH_ARRAY};
    constructVerticesAsPaths_vpa(stack, graph);

    VertexPath vpath[1] = {NOT_A_VPATH};
    uint32_t maxLen     = 0;
    uint32_t nPrimes    = 0;
    while (stack->size > 0) {
        clone_vpath(vpath, pop_vpa(stack));
        DEBUG_ASSERT(vpath->len > 0)

        if (verbose) {
            if (maxLen < vpath->len) {
                VERBOSE_MSG("maxLen(primes) = %"PRIu32, (maxLen = vpath->len))
            }

            if (nPrimes + 100000 < primePaths->size) {
                VERBOSE_MSG("# Prime Paths  > %"PRIu32, (nPrimes = primePaths->size - 1))
            }
        }

        NeighborIterator itr[1];
        construct_nitr_sg(itr, graph, vpath->array[vpath->len - 1]);
        size_t extensions_count = 0;
        for (
            uint32_t neighborId;
            graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
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

                        if (!p_i->isCycle && isSubPath_vpath(p_i, primePath))
                            removePath_vpa(primePaths, i);
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
#undef VERBOSE_MSG

void constructAllUpToKPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph, uint32_t const k) {
    DEBUG_ERROR_IF(vpaths == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ERROR_IF(k == 0)
    DEBUG_ERROR_IF(k == 0xFFFFFFFF)

    constructVerticesAsPaths_vpa(vpaths, graph);

    for (uint32_t i = 0; i < vpaths->size; i++) {
        VertexPath* const vpath = vpaths->array + i;
        DEBUG_ASSERT(isValid_vpath(vpath))
        DEBUG_ASSERT(vpath->len > 0)

        if (vpath->len == k) continue;

        NeighborIterator itr[1];
        construct_nitr_sg(itr, graph, vpath->array[vpath->len - 1]);
        for (
            uint32_t neighborId;
            graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
        ) {
            VertexPath* const clone = pushClone_vpa(vpaths, vpath);
            extend_vpath(clone, neighborId, 0);
        }
    }
}

void constructEmpty_vpa(VertexPathArray* const vpaths, uint32_t const initial_cap) {
    DEBUG_ERROR_IF(vpaths == NULL)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == 0xFFFFFFFF)

    vpaths->cap     = initial_cap;
    vpaths->size    = 0;
    vpaths->array   = calloc((size_t)initial_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(vpaths->array == NULL)
}

void constructVerticesAsPaths_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(vpaths == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    uint32_t const vertex_count = graph->countVertices(graph->graphPtr);
    uint32_t const initial_cap  = vertex_count > VPATH_ARRAY_DEFAULT_INITIAL_CAP ? vertex_count : VPATH_ARRAY_DEFAULT_INITIAL_CAP;

    constructEmpty_vpa(vpaths, initial_cap);

    VertexIterator itr[1];
    construct_vitr_sg(itr, graph);
    for (
        uint32_t vertexId;
        graph->isValidVertex(graph->graphPtr, (vertexId = graph->nextVertexId_vitr(itr)));
    ) {
        VertexPath* const vpath = pushEmpty_vpa(vpaths, graph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(vpath, vertexId, 1))
    }
}

void dump_vpa(VertexPathArray const* const vpaths, FILE* const output) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    DEBUG_ERROR_IF(output == NULL)

    for (uint32_t i = 0; i < vpaths->size; i++) {
        VertexPath const* const vpath = vpaths->array + i;
        DEBUG_ASSERT(isValid_vpath(vpath))

        fprintf(output, " p%"PRIu32":", i);
        dump_vpath(vpath, output);
    }
}

void eliminateSubPaths_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))

    if (vpaths->size < 2) return;

    VertexPath* v_last = vpaths->array + vpaths->size - 1;
    DEBUG_ASSERT(isValid_vpath(v_last))

    VertexPath tmp[1];
    for (VertexPath* v_i = vpaths->array; v_i < v_last; v_i++) {
        DEBUG_ASSERT(isValid_vpath(v_i))

        for (VertexPath* v_j = v_last; v_j > v_i; v_j--) {
            DEBUG_ASSERT(isValid_vpath(v_j))

            if (isSubPath_vpath(v_j, v_i)) {
                size_t const size_in_bytes = (size_t)(v_last - v_j) * sizeof(VertexPath);
                memcpy(tmp, v_j, sizeof(VertexPath));
                memcpy(v_j, v_j + 1, size_in_bytes);
                memcpy(v_last--, tmp, sizeof(VertexPath));
                vpaths->size--;
            } else if (isSubPath_vpath(v_i, v_j)) {
                size_t const size_in_bytes = (size_t)(v_last - v_i) * sizeof(VertexPath);
                memcpy(tmp, v_i, sizeof(VertexPath));
                memcpy(v_i, v_i + 1, size_in_bytes);
                memcpy(v_last--, tmp, sizeof(VertexPath));
                vpaths->size--;
                v_i--;
                break;
            }
        }
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
    *vpaths = NOT_A_VPATH_ARRAY;
}

void increaseCapIfNecessary_vpa(VertexPathArray* const vpaths) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    RECALLOC_IF_NECESSARY(VertexPath, vpaths->array, uint32_t, vpaths->cap, vpaths->size)
}

bool isValid_vpa(VertexPathArray const* const vpaths) {
    return  vpaths != NULL                                  &&
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

    increaseCapIfNecessary_vpa(vpaths);
    VertexPath* const clone = vpaths->array + vpaths->size++;
    clone_vpath(clone, vpath);
    return clone;
}

VertexPath* pushEmpty_vpa(VertexPathArray* const vpaths, SimpleGraph const* const graph) {
    DEBUG_ASSERT(isValid_vpa(vpaths))
    DEBUG_ASSERT(isValid_sg(graph))

    increaseCapIfNecessary_vpa(vpaths);
    VertexPath* const vpath = vpaths->array + vpaths->size++;

    if (vpath->isAllocated) {
        vpath->graph = graph;
        flush_vpath(vpath);
    } else {
        constructEmpty_vpath(vpath, graph);
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
