/**
 * @file nflowgraph.c
 * @brief Implements the functions defined in nflowgraph.h.
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include <string.h>
#include "nflowgraph.h"
#include "padkit/debug.h"

uint32_t computeTotalFlow_nfg(SimpleGraph const* const flowGraph, uint32_t const v) {
    DEBUG_ASSERT(isValid_sg(flowGraph))

    NetworkFlowGraph const* const nfg   = (NetworkFlowGraph const*)flowGraph->graphPtr;
    uint32_t totalFlow                  = 0;

    NeighborIterator itr[1];
    construct_nitr_sg(itr, flowGraph, v);
    for (
        uint32_t vp;
        flowGraph->isValidVertex(nfg, (vp = flowGraph->nextVertexId_nitr(itr)));
    ) totalFlow += nfg->flowMtx[v][vp];

    return totalFlow;
}

void construct_nfg(SimpleGraph* const flowGraph, NetworkFlowGraph* const nfg, SimpleGraph const* const acyclicGraph) {
    DEBUG_ERROR_IF(flowGraph == NULL)
    DEBUG_ERROR_IF(nfg == NULL)
    DEBUG_ASSERT(isValid_sg(acyclicGraph))

    nfg->acyclicGraph = acyclicGraph;
    nfg->countVertices = acyclicGraph->countVertices(acyclicGraph->graphPtr);
    DEBUG_ASSERT(nfg->countVertices > 0)

    nfg->size = nfg->countVertices << 1;
    DEBUG_ASSERT(nfg->size > nfg->countVertices)

    nfg->originalVertexIds = malloc((size_t)nfg->size * sizeof(uint32_t));
    DEBUG_ERROR_IF(nfg->originalVertexIds == NULL)

    nfg->flowMtx = malloc((size_t)nfg->size * sizeof(uint32_t*));
    DEBUG_ERROR_IF(nfg->flowMtx == NULL)

    nfg->adjMtx = malloc((size_t)nfg->size * sizeof(bool*));
    DEBUG_ERROR_IF(nfg->adjMtx == NULL)

    for (uint32_t i = 0; i < nfg->size; i++) {
        nfg->flowMtx[i] = calloc(nfg->size, sizeof(uint32_t));
        DEBUG_ERROR_IF(nfg->flowMtx[i] == NULL)

        nfg->adjMtx[i] = calloc(nfg->size, sizeof(bool));
        DEBUG_ERROR_IF(nfg->adjMtx[i] == NULL)
    }

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, acyclicGraph);
    uint32_t const s_original_id = acyclicGraph->nextVertexId_svitr(svitr);
    DEBUG_ASSERT(acyclicGraph->isValidVertex(acyclicGraph->graphPtr, s_original_id))

    uint32_t const s            = NFG_START_VERTEX(nfg);
    uint32_t const t            = NFG_TERMINAL_VERTEX(nfg);
    nfg->originalVertexIds[s]   = s_original_id;
    nfg->originalVertexIds[t]   = s_original_id;
    nfg->largestOriginalId      = s_original_id;
    VertexIterator vitr[1];
    construct_vitr_sg(vitr, acyclicGraph);
    for (
        uint32_t v = 1, v_original_id;
        acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v_original_id = acyclicGraph->nextVertexId_vitr(vitr)));
    ) {
        if (v_original_id == s_original_id) continue;

        nfg->originalVertexIds[NFG_VERTEX_PLUS(nfg, v)] = v_original_id;
        nfg->originalVertexIds[v++]                     = v_original_id;

        if (nfg->largestOriginalId < v_original_id)
            nfg->largestOriginalId = v_original_id;
    }

    nfg->vertexIds = malloc((size_t)(nfg->largestOriginalId + 1) * sizeof(uint32_t));
    DEBUG_ERROR_IF(nfg->vertexIds == NULL)
    memset(nfg->vertexIds, 0xFF, (size_t)(nfg->largestOriginalId + 1) * sizeof(uint32_t));
    for (uint32_t v = 0; v < nfg->countVertices; v++)
        nfg->vertexIds[nfg->originalVertexIds[v]] = v;

    NeighborIterator nitr[1];
    construct_nitr_sg(nitr, acyclicGraph, s_original_id);
    for (
        uint32_t v_original_id;
        acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v_original_id = acyclicGraph->nextVertexId_nitr(nitr)));
    ) {
        uint32_t const v = nfg->vertexIds[v_original_id];

        nfg->adjMtx[s][v] = 1;
        nfg->adjMtx[v][s] = 1;

        setFlow_nfg(nfg, s, v, 0);
    }

    for (uint32_t v0 = 1; v0 < nfg->countVertices; v0++) {
        uint32_t const v0_original_id   = nfg->originalVertexIds[v0];
        uint32_t const v0p              = NFG_VERTEX_PLUS(nfg, v0);

        nfg->adjMtx[v0][v0p]    = 1;
        nfg->adjMtx[v0p][v0]    = 1;
        nfg->adjMtx[v0p][t]     = 1;
        nfg->adjMtx[t][v0p]     = 1;

        setFlow_nfg(nfg, v0, v0p, 0xFFFFFFFF);
        setFlow_nfg(nfg, v0p, t, 0);

        construct_nitr_sg(nitr, acyclicGraph, v0_original_id);
        for (
            uint32_t v1_original_id;
            acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v1_original_id = acyclicGraph->nextVertexId_nitr(nitr)));
        ) {
            uint32_t const v1 = nfg->vertexIds[v1_original_id];

            nfg->adjMtx[v0p][v1] = 1;
            nfg->adjMtx[v1][v0p] = 1;

            setFlow_nfg(nfg, v0p, v1, 0);
        }
    }

    construct_sgi_nfg(flowGraph, nfg);

    VertexPathArray stack[2] = { NOT_A_VPATH_ARRAY, NOT_A_VPATH_ARRAY };
    VertexPathArray* stack_A = stack;
    VertexPathArray* stack_B = stack_A + 1;

    constructEmpty_vpa(stack_A, nfg->size);
    constructEmpty_vpa(stack_B, nfg->size);

    construct_nitr_sg(nitr, flowGraph, s);
    for (
        uint32_t v;
        flowGraph->isValidVertex(nfg, (v = flowGraph->nextVertexId_nitr(nitr)));
    ) {
        VertexPath* const path = pushEmpty_vpa(stack_A, flowGraph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(path, s, 1))
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(path, v, 1))
    }

    while (stack_A->size > 0) {
        if (stack_B > stack_A) {
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
                bool mustFlow = 0;
                for (uint32_t i = 0; i < path->len - 1; i++)
                    mustFlow |= nfg->flowMtx[path->array[i]][path->array[i + 1]] == 0xFFFFFFFF;

                if (!mustFlow) continue;

                for (uint32_t i = path->len - 1; i > 0; i--)
                    incrementFlow_nfg(nfg, path->array[i - 1], path->array[i], 1);
            } else if (NFG_IS_PLUS(nfg, v0)) {
                construct_nitr_sg(nitr, flowGraph, v0);
                for (
                    uint32_t v1;
                    flowGraph->isValidVertex(nfg, (v1 = flowGraph->nextVertexId_nitr(nitr)));
                ) {
                    VertexPath* const clone = pushClone_vpa(stack_A, path);
                    if (!extend_vpath(clone, v1, 1))
                        pop_vpa(stack_A);
                }
            } else if (NFG_IS_MINUS(nfg, v0)) {
                uint32_t const v0p = NFG_VERTEX_PLUS(nfg, v0);
                DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(path, v0p, 1))
                DEBUG_ERROR_IF(pushClone_vpa(stack_A, path) == NULL)
                NDEBUG_EXECUTE(pushClone_vpa(stack_A, path))
            }
        }
    }

    free_vpa(stack_A);
    free_vpa(stack_B);
}

void construct_sgi_nfg(SimpleGraph* const graph, NetworkFlowGraph* const nfg) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_nfg(nfg))

    *graph = (SimpleGraph){
        nfg,
        countEdges_nfg,
        countVertices_nfg,
        dump_nfg,
        dumpVertex_nfg,
        free_nfg,
        highestVertexId_nfg,
        isValid_nfg,
        isValid_nitr_nfg,
        isValid_svitr_nfg,
        isValid_vitr_nfg,
        isValidEdge_nfg,
        isValidVertex_nfg,
        nextVertexId_nitr_nfg,
        nextVertexId_svitr_nfg,
        nextVertexId_vitr_nfg,
        setFirstNextId_nitr_nfg,
        setFirstNextId_svitr_nfg,
        setFirstNextId_vitr_nfg
    };
}

void constructClone_nfg(SimpleGraph* const cloneGraph, NetworkFlowGraph* const clone, SimpleGraph const* const flowGraph) {
    DEBUG_ERROR_IF(cloneGraph == NULL)
    DEBUG_ERROR_IF(clone == NULL)
    DEBUG_ASSERT(isValid_sg(flowGraph))

    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)flowGraph->graphPtr;

    clone->acyclicGraph         = nfg->acyclicGraph;
    clone->countVertices        = nfg->countVertices;
    clone->size                 = nfg->size;
    clone->largestOriginalId    = nfg->largestOriginalId;

    clone->originalVertexIds = malloc((size_t)nfg->size * sizeof(uint32_t));
    DEBUG_ERROR_IF(clone->originalVertexIds == NULL)
    memcpy(clone->originalVertexIds, nfg->originalVertexIds, (size_t)nfg->size * sizeof(uint32_t));

    clone->vertexIds = malloc((size_t)(nfg->largestOriginalId + 1) * sizeof(uint32_t));
    DEBUG_ERROR_IF(clone->vertexIds == NULL)
    memcpy(clone->vertexIds, nfg->vertexIds, (size_t)(nfg->largestOriginalId + 1) * sizeof(uint32_t));

    clone->flowMtx = malloc((size_t)nfg->size * sizeof(uint32_t*));
    DEBUG_ERROR_IF(clone->flowMtx == NULL)

    clone->adjMtx = malloc((size_t)nfg->size * sizeof(bool*));
    DEBUG_ERROR_IF(clone->adjMtx == NULL)

    for (uint32_t i = 0; i < nfg->size; i++) {
        clone->flowMtx[i] = malloc((size_t)nfg->size * sizeof(uint32_t));
        DEBUG_ERROR_IF(clone->flowMtx[i] == NULL)

        clone->adjMtx[i] = malloc((size_t)nfg->size * sizeof(bool));
        DEBUG_ERROR_IF(clone->adjMtx[i] == NULL)

        memcpy(clone->flowMtx[i], nfg->flowMtx[i], (size_t)nfg->size * sizeof(uint32_t));
        memcpy(clone->adjMtx[i], nfg->adjMtx[i], (size_t)nfg->size * sizeof(bool));
    }

    construct_sgi_nfg(cloneGraph, clone);
}

uint32_t countEdges_nfg(void const* const graphPtr) {
    static uint32_t cachedCount         = 0xFFFFFFFF;
    static void const* cachedGraphPtr   = NULL;

    DEBUG_ASSERT(isValid_nfg(graphPtr))

    if (graphPtr == cachedGraphPtr)
        return cachedCount;

    cachedGraphPtr  = graphPtr;
    cachedCount     = 0;

    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    for (uint32_t v0 = 0; v0 < nfg->size - 1; v0++) {
        for (uint32_t v1 = v0 + 1; v1 < nfg->size; v1++) {
            cachedCount += (nfg->flowMtx[v0][v1] > 0);
            cachedCount += (nfg->flowMtx[v1][v0] > 0);
        }
    }

    return cachedCount;
}

uint32_t countVertices_nfg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;
    return nfg->size;
}

void decrementFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount) {
    DEBUG_ASSERT(isValid_nfg(nfg))
    DEBUG_ASSERT(isValidEdge_nfg(nfg, from, to))
    DEBUG_ASSERT(amount > 0)
    DEBUG_ASSERT(amount < 0xFFFFFFFF)

    setFlow_nfg(nfg, from, to, nfg->flowMtx[from][to] - amount);
}

void dump_nfg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)

    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    for (uint32_t v0 = 0; v0 < nfg->size; v0++) {
        for (uint32_t v1 = 0; v1 < nfg->size; v1++) {
            if (!isValidEdge_nfg(graphPtr, v0, v1)) continue;

            dumpVertex_nfg(graphPtr, output, v0);
            fputs(" ->", output);
            dumpVertex_nfg(graphPtr, output, v1);
            fprintf(output, " (%"PRIu32")\n", nfg->flowMtx[v0][v1]);
        }
    }
}

void dumpVertex_nfg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValidVertex_nfg(graphPtr, vertexId))

    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    if (NFG_IS_PLUS(nfg, vertexId)) {
        if (vertexId == NFG_TERMINAL_VERTEX(nfg)) {
            fputs(" t", output);
        } else {
            uint32_t const v                = NFG_VERTEX_MINUS(nfg, vertexId);
            uint32_t const originalVertexId = nfg->originalVertexIds[v];
            fprintf(output, " %"PRIu32"++", originalVertexId);
        }
    } else if (vertexId == NFG_START_VERTEX(nfg)) {
        fputs(" s", output);
    } else {
        uint32_t const originalVertexId = nfg->originalVertexIds[vertexId];
        fprintf(output, " %"PRIu32"+", originalVertexId);
    }
}

void free_nfg(void* const graphPtr) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))

    NetworkFlowGraph* const nfg = (NetworkFlowGraph*)graphPtr;

    free(nfg->originalVertexIds);
    free(nfg->vertexIds);

    for (uint32_t i = 0; i < nfg->size; i++) {
        free(nfg->flowMtx[i]);
        free(nfg->adjMtx[i]);
    }

    free(nfg->flowMtx);
    free(nfg->adjMtx);

    *nfg = NOT_AN_NFG;
}

uint32_t highestVertexId_nfg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;
    return nfg->size - 1;
}

void incrementFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount) {
    DEBUG_ASSERT(isValid_nfg(nfg))
    DEBUG_ASSERT(isValidEdge_nfg(nfg, from, to))
    DEBUG_ASSERT(amount > 0)
    DEBUG_ASSERT(amount < 0xFFFFFFFF)

    setFlow_nfg(nfg, from, to, nfg->flowMtx[from][to] + amount);
}

bool isValid_nfg(void const* const graphPtr) {
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    return  nfg != NULL                         &&
            isValid_sg(nfg->acyclicGraph)       &&
            nfg->countVertices > 0              &&
            nfg->size >= nfg->countVertices     &&
            nfg->largestOriginalId < 0xFFFFFFFF &&
            nfg->originalVertexIds != NULL      &&
            nfg->vertexIds != NULL              &&
            nfg->flowMtx != NULL;
}

bool isValid_nitr_nfg(NeighborIterator const* const itr) {
    return itr != NULL && isValid_nfg(itr->graphPtr) && isValidVertex_nfg(itr->graphPtr, itr->vertexId);
}

bool isValid_vitr_nfg(VertexIterator const* const itr) {
    return itr != NULL && isValid_nfg(itr->graphPtr);
}

bool isValid_svitr_nfg(StartVertexIterator const* const itr) {
    return itr != NULL && isValid_nfg(itr->graphPtr);
}

bool isValidEdge_nfg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    return  isValidVertex_nfg(graphPtr, sourceVertexId) &&
            isValidVertex_nfg(graphPtr, targetVertexId) &&
            nfg->adjMtx[sourceVertexId][targetVertexId];
}

bool isValidVertex_nfg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;
    return vertexId < nfg->size;
}

void minimizeTotalFlow_nfg(SimpleGraph const* const flowGraph) {
    DEBUG_ASSERT(isValid_sg(flowGraph))

    NetworkFlowGraph* const nfg = flowGraph->graphPtr;

    VertexPathArray stack[2] = { NOT_A_VPATH_ARRAY, NOT_A_VPATH_ARRAY };
    VertexPathArray* stack_A = stack;
    VertexPathArray* stack_B = stack_A + 1;

    constructEmpty_vpa(stack_A, nfg->size);
    constructEmpty_vpa(stack_B, nfg->size);

    uint32_t const s = NFG_START_VERTEX(nfg);
    uint32_t const t = NFG_TERMINAL_VERTEX(nfg);

    bool hasExcessFlow = 1;
    while (hasExcessFlow) {
        hasExcessFlow = 0;

        VertexPath* path = pushEmpty_vpa(stack_A, flowGraph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(path, s, 1))

        while (stack_A->size > 0) {
            if (stack_B > stack_A) {
                stack_A++;
                stack_B--;
            } else {
                stack_A--;
                stack_B++;
            }

            while (stack_B->size > 0) {
                path = pop_vpa(stack_B);
                DEBUG_ASSERT(isValid_vpath(path))
                DEBUG_ASSERT(path->len > 0)

                uint32_t const v0 = path->array[path->len - 1];
                if (v0 == t) {
                    hasExcessFlow = 1;

                    uint32_t minFlow = 0xFFFFFFFF;
                    for (uint32_t i = path->len - 1; i > 0; i--)
                        if (nfg->flowMtx[path->array[i - 1]][path->array[i]] < minFlow)
                            minFlow = nfg->flowMtx[path->array[i - 1]][path->array[i]];

                    for (uint32_t i = path->len - 1; i > 0; i--)
                        decrementFlow_nfg(nfg, path->array[i - 1], path->array[i], minFlow);

                    flush_vpa(stack_A);
                    flush_vpa(stack_B);
                } else {
                    for (uint32_t v1 = 1; v1 < nfg->size; v1++) {
                        if (!nfg->adjMtx[v0][v1] || nfg->flowMtx[v0][v1] == 0) continue;
                        VertexPath* const clone = pushClone_vpa(stack_A, path);
                        if (!extend_vpath(clone, v1, 1))
                            pop_vpa(stack_A);
                    }
                }
            }
        }
    }

    free_vpa(stack_A);
    free_vpa(stack_B);

    for (uint32_t v0 = 1; v0 < nfg->countVertices; v0++) {
        uint32_t const v0p      = NFG_VERTEX_PLUS(nfg, v0);

        nfg->adjMtx[v0][s]      = 0;
        nfg->flowMtx[v0][s]     = 0;

        nfg->adjMtx[v0][t]      = nfg->adjMtx[v0p][t];
        nfg->flowMtx[v0][t]     = nfg->flowMtx[v0p][t];
        nfg->adjMtx[v0p][t]     = 0;
        nfg->flowMtx[v0p][t]    = 0;
        nfg->adjMtx[t][v0p]     = 0;
        nfg->flowMtx[t][v0p]    = 0;

        for (uint32_t v1 = 1; v1 < nfg->countVertices; v1++) {
            if (!nfg->adjMtx[v0p][v1]) continue;

            nfg->adjMtx[v0][v1]     = 1;
            nfg->flowMtx[v0][v1]    = nfg->flowMtx[v0p][v1];

            nfg->adjMtx[v0p][v1]    = 0;
            nfg->flowMtx[v0p][v1]   = 0;
            nfg->adjMtx[v1][v0p]    = 0;
            nfg->flowMtx[v1][v0p]   = 0;
        }

        nfg->adjMtx[v0][v0p]    = 0;
        nfg->flowMtx[v0][v0p]   = 0;

        nfg->adjMtx[v0p][v0]    = 0;
        nfg->flowMtx[v0p][v0]   = 0;
    }
}

uint32_t nextVertexId_nitr_nfg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_nfg(itr))

    while (!isValidEdge_nfg(itr->graphPtr, itr->vertexId, itr->nextNeighborId)) {
        if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextNeighborId--;
    }

    return itr->nextNeighborId--;
}

uint32_t nextVertexId_svitr_nfg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_nfg(itr))
    uint32_t const s_id = itr->nextVertexId;
    itr->nextVertexId   = 0xFFFFFFFF;
    return s_id;
}

uint32_t nextVertexId_vitr_nfg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_nfg(itr))
    if (itr->nextVertexId == 0xFFFFFFFF)
        return 0xFFFFFFFF;
    else
        return itr->nextVertexId--;
}

void setFirstNextId_nitr_nfg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_nfg(itr))
    itr->nextNeighborId = highestVertexId_nfg(itr->graphPtr);
}

void setFirstNextId_svitr_nfg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_nfg(itr))
    itr->nextVertexId = NFG_START_VERTEX(itr->graphPtr);
}

void setFirstNextId_vitr_nfg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_nfg(itr))
    itr->nextVertexId = highestVertexId_nfg(itr->graphPtr);
}

void setFlow_nfg(NetworkFlowGraph* const nfg, uint32_t const from, uint32_t const to, uint32_t const amount) {
    DEBUG_ASSERT(isValid_nfg(nfg))
    DEBUG_ASSERT(isValidEdge_nfg(nfg, from, to))

    nfg->flowMtx[from][to] = amount;
    nfg->flowMtx[to][from] = nfg->countVertices - 1 - amount;
}
