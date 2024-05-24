/**
 * @file eflowgraph.c
 * @brief Implements ExpandedFlowGraph and related functions.
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <string.h>
#include "eflowgraph.h"
#include "hpathgraph.h"
#include "nflowgraph.h"
#include "padkit/reallocate.h"

static void activateVertex_efg(ExpandedFlowGraph* const efg, uint32_t const v);
static void construct_sgi_efg(SimpleGraph* const expandedFlowGraph, ExpandedFlowGraph* const efg);
static void deactivateVertex_efg(ExpandedFlowGraph* const efg, uint32_t const v);
static bool hasPlusVertices_efg(ExpandedFlowGraph const* const efg);
static bool isEdgeBackwards_efg(ExpandedFlowGraph const* const efg, uint32_t const v0, uint32_t const v1);

static void activateVertex_efg(ExpandedFlowGraph* const efg, uint32_t const v) {
    DEBUG_ERROR_IF(efg == NULL)
    DEBUG_ASSERT(efg->size > 0)
    DEBUG_ASSERT(efg->size < 0xFFFFFFFF)
    DEBUG_ASSERT(v < EFG_PRIME(efg, EFG_PLUS(efg, efg->size)))
    DEBUG_ERROR_IF(isConnected_gmtx(efg->adjMtx, v, v))

    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v, v))

    uint32_t l = 0;
    uint32_t r = efg->size_activeVertices;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (efg->activeVertices[m] > v) r = m; else l = m + 1;
    }
    if (r == 0 || efg->activeVertices[r - 1] != v) {
        memmove(
            efg->activeVertices + r + 1,
            efg->activeVertices + r,
            (size_t)(efg->size_activeVertices - r) * sizeof(uint32_t)
        );
        efg->activeVertices[r] = v;
        efg->size_activeVertices++;
    }
}

void computeFeasibleFlow_efg(SimpleGraph* const expandedFlowGraph) {
    DEBUG_ASSERT(isValid_sg(expandedFlowGraph))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)expandedFlowGraph->graphPtr;

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    VertexPathArray stacks[2] = { NOT_A_VPATH_ARRAY, NOT_A_VPATH_ARRAY };
    VertexPathArray* stack_A = stacks;
    VertexPathArray* stack_B = stack_A + 1;

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    constructEmpty_vpa(stack_A, trueSize);
    constructEmpty_vpa(stack_B, trueSize);

    VertexPath* const firstPath = pushEmpty_vpa(stack_A, expandedFlowGraph);
    DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(firstPath, s, 1))

    while (stack_A->size > 0) {
        if (stack_A < stack_B) {
            stack_A++;
            stack_B--;
        } else {
            stack_A--;
            stack_B++;
        }

        while (stack_B->size > 0) {
            VertexPath* const path = pop_vpa(stack_B);
            DEBUG_ASSERT(isValid_vpath(path))
            DEBUG_ASSERT(path->len > 0)

            uint32_t const v0 = path->array[path->len - 1];

            if (v0 == t) {
                for (uint32_t i = 0; i < path->len - 1; i++) {
                    if (efg->flowMtx[path->array[i]][path->array[i + 1]] != 0xFFFFFFFF)
                        continue;

                    for (uint32_t j = 0; j < path->len - 1; j++) {
                        efg->flowMtx[path->array[j]][path->array[j + 1]]++;
                        efg->flowMtx[path->array[j + 1]][path->array[j]]--;
                    }
                    break;
                }
            } else {
                /*for (uint32_t i = efg->size_activeVertices - 1; i != 0xFFFFFFFF; i--) {*/
                for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
                    uint32_t const v1 = efg->activeVertices[i];
                    if (v0 == v1)                       continue;
                    if (!isValidEdge_efg(efg, v0, v1))  continue;

                    VertexPath* const path_to_extend = pushClone_vpa(stack_A, path);

                    if (!extend_vpath(path_to_extend, v1, 1))
                        pop_vpa(stack_A);
                }
            }
        }
    }

    free_vpa(stack_A);
    free_vpa(stack_B);
}

void construct_efg(
    SimpleGraph* const expandedFlowGraph, ExpandedFlowGraph* const efg,
    SimpleGraph const* const flowGraph, SimpleGraph const* const hyperPathGraph
) {
    DEBUG_ERROR_IF(expandedFlowGraph == NULL)
    DEBUG_ERROR_IF(efg == NULL)
    DEBUG_ASSERT(isValid_sg(flowGraph))
    DEBUG_ASSERT(isValid_sg(hyperPathGraph))

    NetworkFlowGraph const* const nfg   = (NetworkFlowGraph const*)flowGraph->graphPtr;
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hyperPathGraph->graphPtr;

    efg->size               = hpgraph->hpaths->size;
    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hyperPathGraph);
    uint32_t const s = (efg->s_id = hyperPathGraph->nextVertexId_svitr(svitr));

    efg->size_activeVertices    = 0;
    efg->activeVertices         = malloc((size_t)trueSize * sizeof(uint32_t));
    DEBUG_ERROR_IF(efg->activeVertices == NULL)

    efg->flowMtx = malloc((size_t)trueSize * sizeof(uint32_t*));
    DEBUG_ERROR_IF(efg->flowMtx == NULL)

    for (uint32_t i = 0; i < trueSize; i++) {
        efg->flowMtx[i] = calloc(trueSize, sizeof(uint32_t));
        DEBUG_ERROR_IF(efg->flowMtx[i] == NULL)
    }

    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(efg->adjMtx, trueSize, trueSize))

    uint32_t const t_nfg    = NFG_TERMINAL_VERTEX(nfg);
    uint32_t const t        = EFG_PRIME(efg, s);
    activateVertex_efg(efg, t);

    NeighborIterator nitr[1];
    for (uint32_t i = 0; i < nfg->countVertices; i++) {
        uint32_t const v0 = nfg->originalVertexIds[i];

        activateVertex_efg(efg, v0);
        construct_nitr_sg(nitr, flowGraph, i);
        for (
            uint32_t j;
            flowGraph->isValidVertex(nfg, (j = flowGraph->nextVertexId_nitr(nitr)));
        ) {
            if (nfg->flowMtx[i][j] == 0) continue;

            if (j == t_nfg) {
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0, t))
            } else {
                uint32_t const v1 = nfg->originalVertexIds[j];
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0, v1))
            }
        }
    }

    for (uint32_t h = efg->size - 1; h > s; h--) {
        VertexPath const* const hpath = hpgraph->hpaths->array + h;
        DEBUG_ASSERT(isValid_vpath(hpath))

        deactivateVertex_efg(efg, h);

        for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
            uint32_t const v0 = efg->activeVertices[i];

            for (uint32_t j = 0; j < hpath->len; j++) {
                uint32_t const v1       = hpath->array[j];
                uint32_t const v1_prime = EFG_PRIME(efg, v1);

                if (
                    isConnected_gmtx(efg->adjMtx, v0, h) &&
                    isConnected_gmtx(hpgraph->edgeMtx, v0, v1)
                ) {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0, v1))
                } else if (
                    isConnected_gmtx(efg->adjMtx, h, v0) &&
                    (v0 == t || isConnected_gmtx(hpgraph->edgeMtx, v1, v0))
                ) {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v1, v0))
                    if (v0 < EFG_PRIME(efg, 0))
                        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v1_prime, v0))
                }
            }
        }

        uint32_t first_id = 0;
        while (first_id < hpath->len) {
            uint32_t const p    = hpath->array[first_id];
            bool validFirst     = 0;
            for (uint32_t i = 0; i < efg->size_activeVertices && !validFirst; i++) {
                uint32_t const v = efg->activeVertices[i];
                validFirst |= isConnected_gmtx(efg->adjMtx, v, p);
            }
            if (validFirst) break;

            first_id++;
        }

        for (uint32_t i = 0; i < hpath->len - 1; i++) {
            uint32_t const id0      = (first_id + i) % hpath->len;
            uint32_t const id1      = (first_id + i + 1) % hpath->len;
            uint32_t const p0       = hpath->array[id0];
            uint32_t const p0_prime = EFG_PRIME(efg, p0);
            uint32_t const p1       = hpath->array[id1];
            uint32_t const p1_prime = EFG_PRIME(efg, p1);
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, p0, p1))
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, p0_prime, p1_prime))
        }
        uint32_t p_last         = hpath->array[(first_id + hpath->len - 1) % hpath->len];
        uint32_t p_first_prime  = EFG_PRIME(efg, hpath->array[first_id % hpath->len]);
        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, p_last, p_first_prime))

        for (uint32_t i = 0; i < hpath->len; i++) {
            uint32_t const p        = hpath->array[i];
            uint32_t const p_prime  = EFG_PRIME(efg, p);
            activateVertex_efg(efg, p);
            activateVertex_efg(efg, p_prime);
        }
        /*
        dump_efg(efg, stdout);
        puts("");
        */
    }

    construct_sgi_efg(expandedFlowGraph, efg);
}

static void construct_sgi_efg(SimpleGraph* const expandedFlowGraph, ExpandedFlowGraph* const efg) {
    DEBUG_ERROR_IF(expandedFlowGraph == NULL)
    DEBUG_ASSERT(isValid_efg(efg))

    *expandedFlowGraph = (SimpleGraph){
        efg,
        countEdges_efg,
        countVertices_efg,
        dump_efg,
        dumpVertex_efg,
        free_efg,
        highestVertexId_efg,
        isValid_efg,
        isValid_nitr_efg,
        isValid_svitr_efg,
        isValid_vitr_efg,
        isValidEdge_efg,
        isValidVertex_efg,
        nextVertexId_nitr_efg,
        nextVertexId_svitr_efg,
        nextVertexId_vitr_efg,
        setFirstNextId_nitr_efg,
        setFirstNextId_svitr_efg,
        setFirstNextId_vitr_efg
    };
}

bool consumePathTrace_efg(VertexPath* const pathTrace, SimpleGraph* const testPlan, SimpleGraph const* const pathGraph) {
    DEBUG_ERROR_IF(pathTrace == NULL)
    DEBUG_ASSERT(isValid_sg(testPlan))
    DEBUG_ASSERT(isValid_sg(pathGraph))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)testPlan->graphPtr;

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    VertexPath connector[1] = { NOT_A_VPATH };

    VertexPathArray stacks[2] = { NOT_A_VPATH_ARRAY, NOT_A_VPATH_ARRAY };
    VertexPathArray* stack_A = stacks;
    VertexPathArray* stack_B = stack_A + 1;

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    constructEmpty_vpa(stack_A, trueSize);
    constructEmpty_vpa(stack_B, trueSize);

    VertexPath* firstPath = pushEmpty_vpa(stack_A, testPlan);
    DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(firstPath, s, 1))

    while (stack_A->size > 0) {
        if (stack_A < stack_B) {
            stack_A++;
            stack_B--;
        } else {
            stack_A--;
            stack_B++;
        }

        while (stack_B->size > 0) {
            VertexPath* const path = pop_vpa(stack_B);
            DEBUG_ASSERT(isValid_vpath(path))
            DEBUG_ASSERT(path->len > 0)

            uint32_t const v0 = path->array[path->len - 1];

            if (v0 == t) {
                if (pathTrace->isAllocated) {
                    flush_vpath(pathTrace);
                    pathTrace->graph = pathGraph;
                } else {
                    constructEmpty_vpath(pathTrace, pathGraph);
                }
                for (uint32_t i = 1; i < path->len - 1; i++) {
                    efg->flowMtx[path->array[i - 1]][path->array[i]]--;
                    if (path->array[i] < EFG_PRIME(efg, 0)) {
                        DEBUG_ERROR_IF(path->array[i] > s)
                        extend_vpath(pathTrace, path->array[i], 0);
                    } else if (path->array[i] > EFG_PRIME(efg, s)) {
                        DEBUG_ASSERT(pathTrace->len > 0)
                        DEBUG_ASSERT(i < path->len - 2)
                        uint32_t const from = pathTrace->array[pathTrace->len - 1];
                        while (path->array[i] > EFG_PRIME(efg, s)) {
                            DEBUG_ASSERT(i < path->len - 2)
                            i++;
                        }
                        uint32_t const to = (path->array[i] < EFG_PRIME(efg, 0))
                            ? path->array[i]
                            : path->array[i] - EFG_PRIME(efg, 0);
                        i--;
                        cacheComputeShortest_vpath(connector, pathGraph, from, to);
                        splice_vpath(pathTrace, connector);
                    } else {
                        extend_vpath(pathTrace, path->array[i] - EFG_PRIME(efg, 0), 0);
                    }
                }
                efg->flowMtx[path->array[path->len - 2]][t]--;
                if (connector->isAllocated)
                    free_vpath(connector);
                free_vpa(stack_A);
                free_vpa(stack_B);
                return 1;
            } else {
                for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
                    uint32_t const v1 = efg->activeVertices[i];
                    if (v0 == v1)                       continue;
                    if (!isValidEdge_efg(efg, v0, v1))  continue;
                    if (efg->flowMtx[v0][v1] == 0)      continue;

                    VertexPath* const path_to_extend = pushClone_vpa(stack_A, path);

                    if (!extend_vpath(path_to_extend, v1, 1))
                        pop_vpa(stack_A);
                }
            }
        }
    }

    DEBUG_ASSERT(!connector->isAllocated)
    if (isValid_vpath(pathTrace))
        invalidate_vpath(pathTrace);
    free_vpa(stack_A);
    free_vpa(stack_B);
    return 0;
}

uint32_t countEdges_efg(void const* const graphPtr) {
    static ExpandedFlowGraph const* cached_efg  = NULL;
    static uint32_t cached_count                = 0;

    DEBUG_ASSERT(isValid_efg(graphPtr))

    if (graphPtr == cached_efg) return cached_count;

    cached_efg      = (ExpandedFlowGraph const*)graphPtr;
    cached_count    = 0;

    for (uint32_t i = 0; i < cached_efg->size_activeVertices; i++) {
        uint32_t const v0 = cached_efg->activeVertices[i];
        for (uint32_t j = 0; j < cached_efg->size_activeVertices; j++) {
            if (i == j) continue;
            uint32_t const v1 = cached_efg->activeVertices[j];
            cached_count += isValidEdge_efg(graphPtr, v0, v1);
        }
    }

    return cached_count;
}

uint32_t countTests_efg(SimpleGraph const* const testPlan) {
    DEBUG_ASSERT(isValid_sg(testPlan))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)testPlan->graphPtr;

    uint32_t const s = efg->s_id;

    uint32_t nTests = 0;
    for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
        uint32_t const v = efg->activeVertices[i];
        nTests += efg->flowMtx[s][v];
    }

    return nTests;
}

uint32_t countVertices_efg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;
    return efg->size_activeVertices;
}

static void deactivateVertex_efg(ExpandedFlowGraph* const efg, uint32_t const v) {
    DEBUG_ERROR_IF(efg == NULL)
    DEBUG_ASSERT(efg->size > 0)
    DEBUG_ASSERT(efg->size < 0xFFFFFFFF)
    DEBUG_ASSERT(v < EFG_PRIME(efg, EFG_PLUS(efg, efg->size)))
    DEBUG_ASSERT(isConnected_gmtx(efg->adjMtx, v, v))

    DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v, v))

    uint32_t l = 0;
    uint32_t r = efg->size_activeVertices;
    while (l < r) {
        uint32_t m = (l + r) >> 1;
        if (efg->activeVertices[m] > v) r = m; else l = m + 1;
    }
    DEBUG_ASSERT(r > 0)
    DEBUG_ASSERT(efg->activeVertices[r - 1] == v)

    memmove(
        efg->activeVertices + r - 1,
        efg->activeVertices + r,
        (size_t)(efg->size_activeVertices - r) * sizeof(uint32_t)
    );
    efg->size_activeVertices--;
}

void dump_efg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;

    fputs(
        "digraph EFG {\n"
        "    rankdir=LR;\n",
        output
    );

    for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
        uint32_t const v0 = efg->activeVertices[i];

        for (uint32_t j = 0; j < efg->size_activeVertices; j++) {
            if (i == j) continue;

            uint32_t const v1 = efg->activeVertices[j];

            if (!isConnected_gmtx(efg->adjMtx, v0, v1)) continue;

            fputs("    ", output);
            dumpEdge_efg(graphPtr, output, v0, v1);
            fprintf(output, " [label=\"%"PRIi32"\"", efg->flowMtx[v0][v1]);
            if (hasPlusVertices_efg(efg) && isEdgeBackwards_efg(efg, v0, v1))
                fputs(",style=\"dashed\"", output);
            fputs("];\n", output);
        }
    }

    fputs("}", output);
}

void dumpEdge_efg(
    void const* const graphPtr, FILE* const output,
    uint32_t const sourceVertexId, uint32_t const targetVertexId
) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_efg(graphPtr, sourceVertexId))
    DEBUG_ASSERT(isValidVertex_efg(graphPtr, targetVertexId))
    DEBUG_ASSERT(isValidEdge_efg(graphPtr, sourceVertexId, targetVertexId))

    dumpVertex_efg(graphPtr, output, sourceVertexId);
    fputs(" -> ", output);
    dumpVertex_efg(graphPtr, output, targetVertexId);
}

void dumpVertex_efg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_efg(graphPtr, vertexId))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    if (vertexId == s) {
        fputs("\"s\"", output);
    } else if (vertexId == t) {
        fputs("\"t\"", output);
    } else if (!hasPlusVertices_efg(efg)) {
        if (vertexId < s) {
            fprintf(output, "\"p%"PRIu32"\"", vertexId);
        } else if (vertexId < EFG_PRIME(efg, 0)) {
            fprintf(output, "\"h%"PRIu32"\"", vertexId - s - 1);
        } else if (vertexId < EFG_PRIME(efg, s)) {
            fprintf(output, "\"p%"PRIu32"'\"", vertexId - EFG_PRIME(efg, 0));
        } else {
            fprintf(output, "\"h%"PRIu32"'\"", vertexId - EFG_PRIME(efg, 0) - s - 1);
        }
    } else if (vertexId < s) {
        fprintf(output, "\"p%"PRIu32"+\"", vertexId);
    } else if (vertexId < EFG_PRIME(efg, 0)) {
        fprintf(output, "\"h%"PRIu32"+\"", vertexId - s - 1);
    } else if (vertexId < t) {
        fprintf(output, "\"p%"PRIu32"'+\"", vertexId - EFG_PRIME(efg, 0));
    } else if (vertexId < EFG_PLUS(efg, 0)) {
        fprintf(output, "\"h%"PRIu32"'+\"", vertexId - EFG_PRIME(efg, 0) - s - 1);
    } else if (vertexId < EFG_PLUS(efg, s)) {
        fprintf(output, "\"p%"PRIu32"++\"", vertexId - EFG_PLUS(efg, 0));
    } else if (vertexId < EFG_PRIME(efg, EFG_PLUS(efg, 0))) {
        fprintf(output, "\"h%"PRIu32"++\"", vertexId - EFG_PLUS(efg, 0) - s - 1);
    } else if (vertexId < EFG_PRIME(efg, EFG_PLUS(efg, s))) {
        fprintf(output, "\"p%"PRIu32"'++\"", vertexId - EFG_PLUS(efg, EFG_PRIME(efg, 0)));
    } else {
        fprintf(output, "\"h%"PRIu32"'++\"", vertexId - EFG_PLUS(efg, EFG_PRIME(efg, 0)) - s - 1);
    }
}

void free_efg(void* const graphPtr) {
    DEBUG_ASSERT(isValid_efg(graphPtr))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)graphPtr;

    free(efg->activeVertices);

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    for (uint32_t i = 0; i < trueSize; i++)
        free(efg->flowMtx[i]);

    free(efg->flowMtx);

    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(efg->adjMtx))
}

void generateTestPlan_efg(SimpleGraph* const expandedFlowGraph) {
    DEBUG_ASSERT(isValid_sg(expandedFlowGraph))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)expandedFlowGraph->graphPtr;

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    for (uint32_t i = 0; i < efg->size_activeVertices - 1; i++) {
        uint32_t const v0 = efg->activeVertices[i];

        for (uint32_t j = i + 1; j < efg->size_activeVertices; j++) {
            uint32_t const v1 = efg->activeVertices[j];

            if (!isValidEdge_efg(efg, v0, v1)) continue;

            if (isEdgeBackwards_efg(efg, v0, v1)) {
                DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v0, v1))
            } else {
                DEBUG_ASSERT(isValidEdge_efg(efg, v1, v0))
                DEBUG_ASSERT(isEdgeBackwards_efg(efg, v1, v0))

                DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v1, v0))
            }
        }
    }

    for (uint32_t i = 0; efg->activeVertices[i] < EFG_PLUS(efg, 0); i++) {
        uint32_t const v0 = efg->activeVertices[i];

        if (v0 == s || v0 == t) continue;

        uint32_t const v0_plus = EFG_PLUS(efg, v0);

        DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v0, v0_plus))

        for (uint32_t j = 0; efg->activeVertices[j] < EFG_PLUS(efg, 0); j++) {
            if (i == j) continue;

            uint32_t const v1 = efg->activeVertices[j];

            if (!isValidEdge_efg(efg, v0_plus, v1)) continue;

            DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v0_plus, v1))
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0, v1))

            efg->flowMtx[v0][v1] = efg->flowMtx[v0_plus][v1];
        }

        deactivateVertex_efg(efg, v0_plus);
    }

    for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
        uint32_t const v0 = efg->activeVertices[i];

        for (uint32_t j = 0; j < efg->size_activeVertices; j++) {
            if (i == j) continue;

            uint32_t const v1 = efg->activeVertices[j];

            if (!isValidEdge_efg(efg, v0, v1))  continue;
            if (efg->flowMtx[v0][v1] > 0)       continue;

            DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v0, v1))
        }
    }
}

static bool hasPlusVertices_efg(ExpandedFlowGraph const* const efg) {
    DEBUG_ASSERT(isValid_efg(efg))
    return efg->activeVertices[efg->size_activeVertices - 1] >= EFG_PLUS(efg, 0);
}

uint32_t highestVertexId_efg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;
    return efg->activeVertices[efg->size_activeVertices - 1];
}

void initializeFlow_efg(SimpleGraph* const expandedFlowGraph) {
    DEBUG_ASSERT(isValid_sg(expandedFlowGraph))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)expandedFlowGraph->graphPtr;

    DEBUG_ASSERT(highestVertexId_efg(efg) < EFG_PLUS(efg, 0))

    uint32_t const flowCapacity = countVertices_efg(efg) - 1;
    DEBUG_ERROR_IF(flowCapacity == 0)
    DEBUG_ERROR_IF(flowCapacity == 0xFFFFFFFF)

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    for (uint32_t i = 0; i <= flowCapacity; i++) {
        uint32_t const v0       = efg->activeVertices[i];
        uint32_t const v0_plus  = EFG_PLUS(efg, v0);

        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0, v0_plus))
        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0_plus, v0))

        if (v0 < EFG_PRIME(efg, 0)) {
            efg->flowMtx[v0][v0_plus] = 0xFFFFFFFF;
            efg->flowMtx[v0_plus][v0] = flowCapacity + 1;
        } else {
            efg->flowMtx[v0][v0_plus] = 0;
            efg->flowMtx[v0_plus][v0] = flowCapacity;
        }

        for (uint32_t j = 0; j <= flowCapacity; j++) {
            if (i == j) continue;

            uint32_t const v1 = efg->activeVertices[j];

            if (!isValidEdge_efg(efg, v0, v1))  continue;

            if (v0 == s) {
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v1, s))

                efg->flowMtx[s][v1] = 0;
                efg->flowMtx[v1][s] = flowCapacity;
            } else {
                DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(efg->adjMtx, v0, v1))
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v0_plus, v1))
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(efg->adjMtx, v1, v0_plus))

                efg->flowMtx[v0_plus][v1] = 0;
                efg->flowMtx[v1][v0_plus] = flowCapacity;
            }
        }

        if (v0 != s && v0 != t)
            activateVertex_efg(efg, v0_plus);
    }
}

static bool isEdgeBackwards_efg(ExpandedFlowGraph const* const efg, uint32_t const v0, uint32_t const v1) {
    DEBUG_ASSERT(isValid_efg(efg))
    DEBUG_ASSERT(isValidEdge_efg(efg, v0, v1))

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    if (v0 == t)                                                        return 1;
    if (v1 == s)                                                        return 1;
    if (v0 != s && v0 < EFG_PLUS(efg, 0) && v1 != EFG_PLUS(efg, v0))    return 1;
    if (v0 >= EFG_PLUS(efg, 0) && v0 == EFG_PLUS(efg, v1))              return 1;

    return 0;
}

bool isValid_efg(void const* const graphPtr) {
    if (graphPtr == NULL) return 0;

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;

    if (efg->size < 2)                          return 0;
    if (efg->size == 0xFFFFFFFF)                return 0;
    if (efg->s_id >= efg->size)                 return 0;
    if (efg->size_activeVertices < 2)           return 0;

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    if (efg->size_activeVertices > trueSize)    return 0;
    if (efg->activeVertices == NULL)            return 0;
    if (efg->flowMtx == NULL)                   return 0;
    if (!isValid_gmtx(efg->adjMtx))             return 0;

    return 1;
}

bool isValid_nitr_efg(NeighborIterator const* const itr) {
    if (itr == NULL)                                        return 0;
    if (!isValid_efg(itr->graphPtr))                        return 0;
    if (!isValidVertex_efg(itr->graphPtr, itr->vertexId))   return 0;
    return 1;
}

bool isValid_svitr_efg(StartVertexIterator const* const itr) {
    if (itr == NULL)                    return 0;
    if (!isValid_efg(itr->graphPtr))    return 0;
    return 1;
}

bool isValid_vitr_efg(VertexIterator const* const itr) {
    if (itr == NULL)                    return 0;
    if (!isValid_efg(itr->graphPtr))    return 0;
    return 1;
}

bool isValidEdge_efg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_efg(graphPtr))
    DEBUG_ASSERT(isValidVertex_efg(graphPtr, sourceVertexId))
    DEBUG_ASSERT(isValidVertex_efg(graphPtr, targetVertexId))
    DEBUG_ASSERT(sourceVertexId != targetVertexId)

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;

    if (!isConnected_gmtx(efg->adjMtx, sourceVertexId, targetVertexId)) return 0;

    return 1;
}

bool isValidVertex_efg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_efg(graphPtr))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)graphPtr;

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    uint32_t const s = efg->s_id;

    if (vertexId >= trueSize)                               return 0;
    if (vertexId == EFG_PLUS(efg, s))                       return 0;
    if (vertexId == EFG_PRIME(efg, EFG_PLUS(efg, s)))       return 0;
    if (!isConnected_gmtx(efg->adjMtx, vertexId, vertexId)) return 0;

    return 1;
}

void minimizeFlow_efg(SimpleGraph* const expandedFlowGraph) {
    DEBUG_ASSERT(isValid_sg(expandedFlowGraph))

    ExpandedFlowGraph* const efg = (ExpandedFlowGraph*)expandedFlowGraph->graphPtr;

    uint32_t const s = efg->s_id;
    uint32_t const t = EFG_PRIME(efg, s);

    VertexPathArray stacks[2] = { NOT_A_VPATH_ARRAY, NOT_A_VPATH_ARRAY };
    VertexPathArray* stack_A = stacks;
    VertexPathArray* stack_B = stack_A + 1;

    uint32_t const trueSize = EFG_PRIME(efg, EFG_PLUS(efg, efg->size));
    DEBUG_ASSERT(trueSize > efg->size)

    constructEmpty_vpa(stack_A, trueSize);
    constructEmpty_vpa(stack_B, trueSize);

    VertexPath* firstPath = pushEmpty_vpa(stack_A, expandedFlowGraph);
    DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(firstPath, s, 1))

    while (stack_A->size > 0) {
        if (stack_A < stack_B) {
            stack_A++;
            stack_B--;
        } else {
            stack_A--;
            stack_B++;
        }

        while (stack_B->size > 0) {
            VertexPath* const path = pop_vpa(stack_B);
            DEBUG_ASSERT(isValid_vpath(path))
            DEBUG_ASSERT(path->len > 0)

            uint32_t const v0 = path->array[path->len - 1];

            if (v0 == t) {
                uint32_t minFlow = 0xFFFFFFFF;
                for (uint32_t i = 0; i < path->len - 1; i++) {
                    uint32_t candidateFlow = efg->flowMtx[path->array[i]][path->array[i + 1]];
                    if (candidateFlow < minFlow)
                        minFlow = candidateFlow;
                }

                DEBUG_ASSERT(minFlow > 0)
                for (uint32_t i = 0; i < path->len - 1; i++) {
                    efg->flowMtx[path->array[i]][path->array[i + 1]] += minFlow;
                    efg->flowMtx[path->array[i + 1]][path->array[i]] -= minFlow;
                }

                flush_vpa(stack_A);
                flush_vpa(stack_B);

                firstPath = pushEmpty_vpa(stack_A, expandedFlowGraph);
                DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(firstPath, s, 1))
            } else {
                /* for (uint32_t i = efg->size_activeVertices - 1; i != 0xFFFFFFFF; i--) { */
                for (uint32_t i = 0; i < efg->size_activeVertices; i++) {
                    uint32_t const v1 = efg->activeVertices[i];
                    if (v0 == v1)                       continue;
                    if (!isValidEdge_efg(efg, v0, v1))  continue;
                    if (efg->flowMtx[v0][v1] == 0)      continue;

                    VertexPath* const path_to_extend = pushClone_vpa(stack_A, path);

                    if (!extend_vpath(path_to_extend, v1, 1))
                        pop_vpa(stack_A);
                }
            }
        }
    }

    free_vpa(stack_A);
    free_vpa(stack_B);
}

uint32_t nextVertexId_nitr_efg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_efg(itr))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)itr->graphPtr;

    while (
        itr->nextNeighborId < efg->size_activeVertices                                  &&
        !isValidEdge_efg(efg, itr->vertexId, efg->activeVertices[itr->nextNeighborId])
    ) itr->nextNeighborId++;

    if (itr->nextNeighborId >= efg->size_activeVertices)
        return 0xFFFFFFFF;

    return efg->activeVertices[itr->nextNeighborId++];
}

uint32_t nextVertexId_svitr_efg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_efg(itr))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)itr->graphPtr;

    if (itr->nextVertexId == efg->s_id) {
        itr->nextVertexId = 0xFFFFFFFF;
        return efg->s_id;
    } else {
        return 0xFFFFFFFF;
    }
}

uint32_t nextVertexId_vitr_efg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_efg(itr))

    ExpandedFlowGraph const* const efg = (ExpandedFlowGraph const*)itr->graphPtr;

    if (itr->nextVertexId < efg->size_activeVertices) {
        return efg->activeVertices[itr->nextVertexId++];
    } else {
        return 0xFFFFFFFF;
    }
}

void setFirstNextId_nitr_efg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_efg(itr))
    itr->nextNeighborId = 0;
}

void setFirstNextId_svitr_efg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_efg(itr))
    ExpandedFlowGraph const* const efg  = (ExpandedFlowGraph const*)itr->graphPtr;
    itr->nextVertexId                   = efg->s_id;
}

void setFirstNextId_vitr_efg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_efg(itr))
    itr->nextVertexId = 0;
}
