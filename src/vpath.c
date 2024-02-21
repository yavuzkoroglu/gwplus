/**
 * @file vpath.c
 * @brief Implements the functions defined in vpath.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/reallocate.h"
#include "padkit/streq.h"
#include "vpath.h"

bool canRotate_vpath(VertexPath* const vpath) {
    DEBUG_ASSERT(isValid_vpath(vpath))

    if (vpath->len < 2) return 0;

    uint32_t const firstVertexId    = vpath->array[0];
    uint32_t const lastVertexId     = vpath->array[vpath->len - 1];

    vpath->isCycle = (firstVertexId == lastVertexId);

    return vpath->isCycle || vpath->graph->isValidEdge(vpath->graph->graphPtr, lastVertexId, firstVertexId);
}

void clone_vpath(VertexPath* const clone, VertexPath const* const original) {
    DEBUG_ERROR_IF(clone == NULL)
    DEBUG_ASSERT(isValid_vpath(original))

    if (clone->isAllocated) {
        flush_vpath(clone);
        clone->graph = original->graph;
        increaseCapIfNecessary_vpath(clone);
    } else {
        constructEmpty_vpath(clone, original->graph);
    }

    size_t const size_in_bytes = (size_t)original->len * sizeof(uint32_t);
    memcpy(clone->array, original->array, size_in_bytes);
    memcpy(clone->sorted, original->sorted, size_in_bytes);

    clone->isSimple = original->isSimple;
    clone->isCycle  = original->isCycle;
    clone->isPrime  = original->isPrime;
    clone->len      = original->len;
}

bool computeShortest_vpath(VertexPath* const shortestPath, SimpleGraph const* const graph, uint32_t const from, uint32_t const to) {
    DEBUG_ERROR_IF(shortestPath == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, from))
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, to))

    if (shortestPath->isAllocated) {
        shortestPath->graph = graph;
        flush_vpath(shortestPath);
    } else {
        constructEmpty_vpath(shortestPath, graph);
    }
    if (from == to) return 1;

    VertexPath* vpath;

    uint32_t    stack_A_cap     = graph->countVertices(graph->graphPtr);
    uint32_t    stack_A_size    = 0;
    VertexPath* stack_A         = calloc((size_t)stack_A_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_A == NULL)

    uint32_t    stack_B_cap     = stack_A_cap;
    uint32_t    stack_B_size    = 0;
    VertexPath* stack_B         = calloc((size_t)stack_B_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_B == NULL)

    NeighborIterator itr[1];
    construct_nitr_sg(itr, graph, from);
    for (
        uint32_t neighborId;
        graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
    ) {
        if (neighborId == to) {
            for (uint32_t i = 0; i < stack_A_cap; i++) {
                vpath = stack_A + i;
                if (vpath->isAllocated) free_vpath(vpath);
            }
            free(stack_A);
            for (uint32_t i = 0; i < stack_B_cap; i++) {
                vpath = stack_B + i;
                if (vpath->isAllocated) free_vpath(vpath);
            }
            free(stack_B);
            return 1;
        }
        vpath = stack_A + stack_A_size++;
        constructEmpty_vpath(vpath, graph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(vpath, neighborId, 1))
    }

    while (stack_A_size > 0) {
        VertexPath* const   tmp_ptr = stack_B;
        stack_B                     = stack_A;
        stack_A                     = tmp_ptr;

        uint32_t const      tmp_cap = stack_B_cap;
        stack_B_cap                 = stack_A_cap;
        stack_A_cap                 = tmp_cap;

        stack_B_size                = stack_A_size;
        stack_A_size                = 0;

        while (stack_B_size > 0) {
            vpath = stack_B + --stack_B_size;
            DEBUG_ASSERT(isValid_vpath(vpath))
            DEBUG_ASSERT(vpath->len > 0)

            uint32_t const lastVertexId = vpath->array[vpath->len - 1];
            construct_nitr_sg(itr, graph, lastVertexId);
            for (
                uint32_t neighborId;
                graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
            ) {
                if (neighborId == to) {
                    clone_vpath(shortestPath, vpath);
                    for (uint32_t i = 0; i < stack_A_cap; i++) {
                        vpath = stack_A + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_A);
                    for (uint32_t i = 0; i < stack_B_cap; i++) {
                        vpath = stack_B + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_B);
                    return 1;
                }

                RECALLOC_IF_NECESSARY(
                    VertexPath, stack_A,
                    uint32_t, stack_A_cap, stack_A_size,
                    RECALLOC_ERROR
                )
                VertexPath* const vpath_to_extend = stack_A + stack_A_size++;
                clone_vpath(vpath_to_extend, vpath);

                stack_A_size -= !extend_vpath(vpath_to_extend, neighborId, 1);
            }
        }
    }

    invalidate_vpath(shortestPath);
    for (uint32_t i = 0; i < stack_A_cap; i++) {
        vpath = stack_A + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_A);
    for (uint32_t i = 0; i < stack_B_cap; i++) {
        vpath = stack_B + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_B);
    return 0;
}

bool computeShortestCycle_vpath(VertexPath* const cycle, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(cycle == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    VertexPath* vpath;

    uint32_t    stack_A_cap     = graph->countVertices(graph->graphPtr);
    uint32_t    stack_A_size    = 0;
    VertexPath* stack_A         = calloc((size_t)stack_A_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_A == NULL)

    uint32_t    stack_B_cap     = stack_A_cap;
    uint32_t    stack_B_size    = 0;
    VertexPath* stack_B         = calloc((size_t)stack_B_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_B == NULL)

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);
    for (
        uint32_t vertexId;
        graph->isValidVertex(graph->graphPtr, (vertexId = graph->nextVertexId_vitr(vitr)));
    ) {
        vpath = stack_A + stack_A_size++;
        constructEmpty_vpath(vpath, graph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(vpath, vertexId, 1))
    }

    while (stack_A_size > 0) {
        VertexPath* const   tmp_ptr = stack_B;
        stack_B                     = stack_A;
        stack_A                     = tmp_ptr;

        uint32_t const      tmp_cap = stack_B_cap;
        stack_B_cap                 = stack_A_cap;
        stack_A_cap                 = tmp_cap;

        stack_B_size                = stack_A_size;
        stack_A_size                = 0;

        while (stack_B_size > 0) {
            vpath = stack_B + --stack_B_size;
            DEBUG_ASSERT(isValid_vpath(vpath))
            DEBUG_ASSERT(vpath->len > 0)

            uint32_t const target       = vpath->array[0];
            uint32_t const lastVertexId = vpath->array[vpath->len - 1];
            NeighborIterator itr[1];
            construct_nitr_sg(itr, graph, lastVertexId);
            for (
                uint32_t neighborId;
                graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
            ) {
                if (neighborId == target) {
                    clone_vpath(cycle, vpath);
                    for (uint32_t i = 0; i < stack_A_cap; i++) {
                        vpath = stack_A + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_A);
                    for (uint32_t i = 0; i < stack_B_cap; i++) {
                        vpath = stack_B + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_B);
                    return 1;
                }

                RECALLOC_IF_NECESSARY(
                    VertexPath, stack_A,
                    uint32_t, stack_A_cap, stack_A_size,
                    RECALLOC_ERROR
                )
                VertexPath* const vpath_to_extend = stack_A + stack_A_size++;
                clone_vpath(vpath_to_extend, vpath);

                stack_A_size -= !extend_vpath(vpath_to_extend, neighborId, 1);
            }
        }
    }

    invalidate_vpath(cycle);
    for (uint32_t i = 0; i < stack_A_cap; i++) {
        vpath = stack_A + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_A);
    for (uint32_t i = 0; i < stack_B_cap; i++) {
        vpath = stack_B + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_B);
    return 0;
}

bool computeShortestInitializer_vpath(VertexPath* const initializer, SimpleGraph const* const graph, uint32_t const target) {
    DEBUG_ERROR_IF(initializer == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(graph->isValidVertex(graph->graphPtr, target))

    VertexPath* vpath;

    uint32_t    stack_A_cap     = graph->countVertices(graph->graphPtr);
    uint32_t    stack_A_size    = 0;
    VertexPath* stack_A         = calloc((size_t)stack_A_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_A == NULL)

    uint32_t    stack_B_cap     = stack_A_cap;
    uint32_t    stack_B_size    = 0;
    VertexPath* stack_B         = calloc((size_t)stack_B_cap, sizeof(VertexPath));
    DEBUG_ERROR_IF(stack_B == NULL)

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, graph);
    for (
        uint32_t s_id;
        graph->isValidVertex(graph->graphPtr, (s_id = graph->nextVertexId_svitr(svitr)));
    ) {
        if (s_id == target) {
            for (uint32_t i = 0; i < stack_A_cap; i++) {
                vpath = stack_A + i;
                if (vpath->isAllocated) free_vpath(vpath);
            }
            free(stack_A);
            for (uint32_t i = 0; i < stack_B_cap; i++) {
                vpath = stack_B + i;
                if (vpath->isAllocated) free_vpath(vpath);
            }
            free(stack_B);

            if (initializer->isAllocated) {
                initializer->graph = graph;
                flush_vpath(initializer);
            } else {
                constructEmpty_vpath(initializer, graph);
            }
            return 1;
        }

        vpath = stack_A + stack_A_size++;
        constructEmpty_vpath(vpath, graph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(vpath, s_id, 1))
    }

    while (stack_A_size > 0) {
        VertexPath* const   tmp_ptr = stack_B;
        stack_B                     = stack_A;
        stack_A                     = tmp_ptr;

        uint32_t const      tmp_cap = stack_B_cap;
        stack_B_cap                 = stack_A_cap;
        stack_A_cap                 = tmp_cap;

        stack_B_size                = stack_A_size;
        stack_A_size                = 0;

        while (stack_B_size > 0) {
            vpath = stack_B + --stack_B_size;
            DEBUG_ASSERT(isValid_vpath(vpath))
            DEBUG_ASSERT(vpath->len > 0)

            uint32_t const lastVertexId = vpath->array[vpath->len - 1];
            NeighborIterator itr[1];
            construct_nitr_sg(itr, graph, lastVertexId);
            for (
                uint32_t neighborId;
                graph->isValidVertex(graph->graphPtr, (neighborId = graph->nextVertexId_nitr(itr)));
            ) {
                if (neighborId == target) {
                    clone_vpath(initializer, vpath);
                    for (uint32_t i = 0; i < stack_A_cap; i++) {
                        vpath = stack_A + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_A);
                    for (uint32_t i = 0; i < stack_B_cap; i++) {
                        vpath = stack_B + i;
                        if (vpath->isAllocated) free_vpath(vpath);
                    }
                    free(stack_B);
                    return 1;
                }

                RECALLOC_IF_NECESSARY(
                    VertexPath, stack_A,
                    uint32_t, stack_A_cap, stack_A_size,
                    RECALLOC_ERROR
                )
                VertexPath* const vpath_to_extend = stack_A + stack_A_size++;
                clone_vpath(vpath_to_extend, vpath);

                stack_A_size -= !extend_vpath(vpath_to_extend, neighborId, 1);
            }
        }
    }

    invalidate_vpath(initializer);
    for (uint32_t i = 0; i < stack_A_cap; i++) {
        vpath = stack_A + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_A);
    for (uint32_t i = 0; i < stack_B_cap; i++) {
        vpath = stack_B + i;
        if (vpath->isAllocated) free_vpath(vpath);
    }
    free(stack_B);
    return 0;
}

void concat_vpath(VertexPath* const head, VertexPath const* const tail) {
    DEBUG_ASSERT(isValid_vpath(head))
    DEBUG_ASSERT(isValid_vpath(tail))
    DEBUG_ASSERT(head->graph->graphPtr == tail->graph->graphPtr)

    if (tail->len == 0) return;
    if (head->len == 0) {
        clone_vpath(head, tail);
        return;
    }

    DEBUG_ASSERT(head->graph->isValidEdge(head->graph->graphPtr, head->array[head->len - 1], tail->array[0]))

    size_t const old_head_sorted_size_in_bytes = (size_t)head->len * sizeof(uint32_t);
    uint32_t* old_head_sorted = malloc(old_head_sorted_size_in_bytes);
    DEBUG_ERROR_IF(old_head_sorted == NULL)

    memcpy(old_head_sorted, head->sorted, old_head_sorted_size_in_bytes);

    uint32_t const tail_start = head->len;
    head->len += tail->len;
    DEBUG_ASSERT(head->len > tail_start)

    increaseCapIfNecessary_vpath(head);

    size_t const tail_size_in_bytes = (size_t)tail->len * sizeof(uint32_t);
    memcpy(head->array + tail_start, tail->array, tail_size_in_bytes);

    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    while (i < tail_start && j < tail->len) {
        if (old_head_sorted[i] < tail->sorted[j])
            head->sorted[k++] = old_head_sorted[i++];
        else
            head->sorted[k++] = tail->sorted[j++];
    }

    size_t const remaining_head_size_in_bytes = (size_t)(tail_start - i) * sizeof(uint32_t);
    memcpy(head->sorted + k, old_head_sorted + i, remaining_head_size_in_bytes);

    size_t const remaining_tail_size_in_bytes = (size_t)(tail->len - j) * sizeof(uint32_t);
    memcpy(head->sorted + k, tail->sorted + j, remaining_tail_size_in_bytes);

    free(old_head_sorted);
}

void constructEmpty_vpath(VertexPath* const vpath, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(vpath == NULL)
    DEBUG_ASSERT(isValid_sg(graph))

    uint32_t const initial_cap = graph->countVertices(graph->graphPtr) + 1;
    DEBUG_ERROR_IF(initial_cap == 0)

    vpath->graph        = graph;
    vpath->isAllocated  = 1;
    vpath->isSimple     = 1;
    vpath->isCycle      = 0;
    vpath->isPrime      = 0;
    vpath->len          = 0;
    vpath->cap          = initial_cap;
    vpath->sorted       = malloc(initial_cap * sizeof(uint32_t));
    vpath->array        = malloc(initial_cap * sizeof(uint32_t));
    DEBUG_ERROR_IF(vpath->array == NULL)
}

bool contains_vpath(VertexPath const* const vpath, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpath(vpath))
    DEBUG_ASSERT(vpath->graph->isValidVertex(vpath->graph->graphPtr, vertexId))

    uint32_t const position = search_vpath(vpath, vertexId);

    return position != 0 && vpath->sorted[position - 1] == vertexId;
}

void dump_vpath(VertexPath const* const vpath, FILE* const output) {
    DEBUG_ASSERT(isValid_vpath(vpath))
    DEBUG_ERROR_IF(output == NULL)

    for (uint32_t i = 0; i < vpath->len; i++)
        vpath->graph->dumpVertex(vpath->graph->graphPtr, output, vpath->array[i]);

    fputs("\n", output);
}

bool extend_vpath(VertexPath* const vpath, uint32_t const vertexId, bool const preserveSimplicity) {
    DEBUG_ASSERT(isValid_vpath(vpath))
    DEBUG_ASSERT(vpath->graph->isValidVertex(vpath->graph->graphPtr, vertexId))

    if (vpath->len == 0) {
        vpath->sorted[0]    = vertexId;
        vpath->array[0]     = vertexId;
        vpath->len++;
        return 1;
    }

    DEBUG_ASSERT(vpath->graph->isValidEdge(vpath->graph->graphPtr, vpath->array[vpath->len - 1], vertexId))

    increaseCapIfNecessary_vpath(vpath);

    uint32_t const hypothetical_sorted_position = search_vpath(vpath, vertexId);
    if (
        vpath->isSimple                                             &&
        hypothetical_sorted_position > 0                            &&
        vpath->sorted[hypothetical_sorted_position - 1] == vertexId
    ) {
        if (vpath->array[0] == vertexId) {
            vpath->isCycle = 1;
            vpath->isPrime = 1;
        } else if (preserveSimplicity) {
            return 0;
        } else {
            vpath->isPrime  = 0;
            vpath->isSimple = 0;
        }
    }

    uint32_t* const position    = vpath->sorted + hypothetical_sorted_position;
    size_t const nElements      = vpath->len - hypothetical_sorted_position;
    memmove(position + 1, position, nElements * sizeof(uint32_t));
    *position = vertexId;

    vpath->array[vpath->len++] = vertexId;

    vpath->isPrime |= (vpath->isSimple && vpath->len > vpath->graph->countVertices(vpath->graph->graphPtr));

    return 1;
}

uint32_t findLargestOverlap_vpath(VertexPath const* const head, VertexPath const* const tail) {
    DEBUG_ASSERT(isValid_vpath(head))
    DEBUG_ASSERT(isValid_vpath(tail))
    DEBUG_ASSERT(head->graph->graphPtr == tail->graph->graphPtr)

    uint32_t overlap_len        = (head->len < tail->len) ? head->len : tail->len;
    uint32_t overlap_start_pos  = head->len - overlap_len;
    size_t overlap_size_bytes   = (size_t)overlap_len * sizeof(uint32_t);

    while (
        overlap_len > 0 &&
        !mem_eq_n(
            (char const*)(head->array + overlap_start_pos),
            (char const*)tail->array,
            overlap_size_bytes
        )
    ) {
        overlap_len--;
        overlap_start_pos++;
        overlap_size_bytes -= sizeof(uint32_t);
    }

    return overlap_len;
}

void flush_vpath(VertexPath* const vpath) {
    DEBUG_ERROR_IF(vpath == NULL)
    DEBUG_ASSERT(vpath->isAllocated)

    vpath->isSimple = 1;
    vpath->isCycle  = 0;
    vpath->isPrime  = 0;
    vpath->len      = 0;
}

void free_vpath(VertexPath* const vpath) {
    DEBUG_ERROR_IF(vpath == NULL)
    DEBUG_ASSERT(vpath->isAllocated)

    free(vpath->sorted);
    vpath->sorted = NULL;

    free(vpath->array);
    vpath->array = NULL;

    vpath->isAllocated = 0;
}

void increaseCapIfNecessary_vpath(VertexPath* const vpath) {
    DEBUG_ERROR_IF(vpath == NULL)
    DEBUG_ASSERT(vpath->isAllocated)

    uint32_t len = vpath->graph->countVertices(vpath->graph->graphPtr);
    if (vpath->len > len) len = vpath->len;

    if (vpath->cap > len) return;

    uint32_t new_cap = vpath->cap << 1;
    DEBUG_ASSERT(new_cap > vpath->cap)
    while (new_cap <= len) {
        new_cap <<= 1;
        DEBUG_ASSERT(new_cap > vpath->cap)
    }

    if (REALLOCATE(vpath->array, vpath->cap, new_cap, sizeof(uint32_t)) == NULL)
        REALLOC_ERROR

    if (REALLOCATE(vpath->sorted, vpath->cap, new_cap, sizeof(uint32_t)) == NULL)
        REALLOC_ERROR

    vpath->cap = new_cap;
}

void invalidate_vpath(VertexPath* const vpath) {
    DEBUG_ASSERT(isValid_vpath(vpath))

    vpath->len = 0xFFFFFFFF;
}

bool isSubPath_vpath(VertexPath const* const sub, VertexPath const* const super) {
    DEBUG_ASSERT(isValid_vpath(sub))
    DEBUG_ASSERT(isValid_vpath(super))
    DEBUG_ASSERT(sub->graph->graphPtr == super->graph->graphPtr)

    if (sub->len > super->len) return 0;

    size_t const sub_size_in_bytes  = (size_t)sub->len * sizeof(uint32_t);
    uint32_t* const super_end       = super->array + super->len - sub->len;

    for (uint32_t* ptr = super_end; ptr >= super->array; ptr--)
        if (mem_eq_n((char const*)ptr, (char const*)sub->array, sub_size_in_bytes))
            return 1;

    return 0;
}

bool isValid_vpath(VertexPath const* const vpath) {
    return  vpath != NULL                           &&
            isValid_sg(vpath->graph)                &&
            vpath->isAllocated                      &&
            (!vpath->isPrime || vpath->isSimple)    &&
            vpath->len <= vpath->cap                &&
            vpath->cap != 0                         &&
            vpath->cap != 0xFFFFFFFF                &&
            vpath->array != NULL;
}

bool rotate_vpath(VertexPath* const vpath) {
    DEBUG_ASSERT(isValid_vpath(vpath))

    if (vpath->len < 2) return 1;

    size_t size_in_bytes, r;

    vpath->isCycle = (vpath->array[0] == vpath->array[vpath->len - 1]);

    if (vpath->isCycle) {
        size_in_bytes = (size_t)(vpath->len - 1) * sizeof(uint32_t);
        memmove(vpath->array + 1, vpath->array, size_in_bytes);
        vpath->array[0] = vpath->array[vpath->len - 1];

        r = search_vpath(vpath, vpath->array[1]);
        DEBUG_ASSERT(r > 0)
        size_in_bytes = (size_t)(vpath->len - r) * sizeof(uint32_t);
        memmove(vpath->sorted + r - 1, vpath->sorted + r, size_in_bytes);

        vpath->len--;

        r = search_vpath(vpath, vpath->array[0]);
        DEBUG_ASSERT(r > 0)
        size_in_bytes = (size_t)(vpath->len - r) * sizeof(uint32_t);
        memmove(vpath->sorted + r + 1, vpath->sorted + r, size_in_bytes);
        vpath->sorted[r] = vpath->array[0];

        vpath->len++;

        return 1;
    } else if (vpath->graph->isValidEdge(vpath->graph->graphPtr, vpath->array[vpath->len - 1], vpath->array[0])) {
        uint32_t const tmp = vpath->array[vpath->len - 1];
        size_in_bytes = (size_t)(vpath->len - 1) * sizeof(uint32_t);
        memmove(vpath->array + 1, vpath->array, size_in_bytes);
        vpath->array[0] = tmp;
        return 1;
    } else {
        return 0;
    }
}

uint32_t search_vpath(VertexPath const* const vpath, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_vpath(vpath))
    DEBUG_ASSERT(vpath->graph->isValidVertex(vpath->graph->graphPtr, vertexId))

    /* Perform rightmost binary search amongst the sorted indices */
    uint32_t l = 0;
    uint32_t r = vpath->len;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (vpath->sorted[m] > vertexId) r = m; else l = m + 1;
    }

    return r;
}

bool splice_vpath(VertexPath* const head, VertexPath const* const tail) {
    DEBUG_ASSERT(isValid_vpath(head))
    DEBUG_ASSERT(isValid_vpath(tail))
    DEBUG_ASSERT(head->graph->graphPtr == tail->graph->graphPtr)

    if (tail->len == 0) {
        return 1;
    } else if (head->len == 0) {
        clone_vpath(head, tail);
        return 1;
    }

    VertexPath connector[1] = {NOT_A_VPATH};
    uint32_t const overlapLen = findLargestOverlap_vpath(head, tail);
    if (overlapLen > 0) {
        for (uint32_t i = overlapLen; i < tail->len; i++)
            extend_vpath(head, tail->array[i], 0);
        return 1;
    } else if (computeShortest_vpath(connector, head->graph, head->array[head->len - 1], tail->array[0])) {
        concat_vpath(head, connector);
        concat_vpath(head, tail);
        free_vpath(connector);
        return 1;
    } else {
        invalidate_vpath(head);
        if (connector->isAllocated) free_vpath(connector);
        return 0;
    }
}

bool subsumes_vpath(VertexPath const* const subsumer, VertexPath const* const subsumed) {
    DEBUG_ASSERT(isValid_vpath(subsumer))
    DEBUG_ASSERT(isValid_vpath(subsumed))

    if (subsumer->len == 0) return 0;

    uint32_t i = 0;
    uint32_t j = 0;
    while (i < subsumed->len) {
        uint32_t const vertexId = subsumed->sorted[i];

        while (subsumer->sorted[j] != vertexId) {
            if (j == subsumer->len || subsumer->sorted[j] > vertexId)
                return 0;
            j++;
        }

        while (subsumed->sorted[++i] == vertexId) {}
        while (subsumer->sorted[++j] == vertexId) {}
    }

    return 1;
}
