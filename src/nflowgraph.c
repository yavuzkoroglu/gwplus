/**
 * @file nflowgraph.c
 * @brief Implements the functions defined in nflowgraph.h.
 * @author Anonymized for ICSE2025
 */
#include "nflowgraph.h"
#include "padkit/debug.h"

void construct_nfg(NetworkFlowGraph* const nfg, SimpleGraph const* const acyclicGraph) {
    DEBUG_ERROR_IF(nfg == NULL)
    DEBUG_ASSERT(isValid_sg(acyclicGraph))

    nfg->acyclicGraph = acyclicGraph;
    nfg->countVertices = acyclicGraph->countVertices(acyclicGraph->graphPtr);
    DEBUG_ASSERT(nfg->countVertices > 0)

    nfg->size = nfg->countVertices << 1;
    DEBUG_ASSERT(nfg->size > nfg->countVertices)

    nfg->originalVertexIds = malloc((size_t)nfg->countVertices * sizeof(uint32_t));
    DEBUG_ERROR_IF(nfg->originalVertexIds)

    nfg->transitionMtx = malloc((size_t)nfg->size * sizeof(NetworkFlowTransition*));
    DEBUG_ERROR_IF(nfg->transitionMtx == NULL)

    for (uint32_t i = 0; i < nfg->size; i++) {
        nfg->transitionMtx[i] = calloc(nfg->size, sizeof(NetworkFlowTransition));
        DEBUG_ERROR_IF(nfg->transitionMtx[i] == NULL)
    }

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, acyclicGraph);
    uint32_t const s_original_id = acyclicGraph->nextVertexId_svitr(svitr);
    DEBUG_ASSERT(acyclicGraph->isValidVertex(acyclicGraph->graphPtr, s_original_id))

    uint32_t const s            = NFG_START_VERTEX(nfg);
    uint32_t const t            = NFG_TERMINAL_VERTEX(nfg);
    nfg->originalVertexIds[s]   = s_original_id;

    uint32_t v                  = 1;
    uint32_t largestOriginalId  = s_original_id;
    VertexIterator vitr[1];
    construct_vitr_sg(vitr, acyclicGraph);
    for (
        uint32_t v_original_id;
        acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v_original_id = acyclicGraph->nextVertexId_vitr(vitr)));
    ) {
        nfg->originalVertexIds[v++] = v_original_id;

        if (largestOriginalId < v_original_id)
            largestOriginalId = v_original_id;
    }

    nfg->vertexIds = malloc((size_t)(largestOriginalId + 1) * sizeof(uint32_t));
    DEBUG_ERROR_IF(nfg->vertexIds == NULL)
    memset(nfg->vertexIds, 0xFF, (size_t)(largestOriginalId + 1) * sizeof(uint32_t));
    for (uint32_t v = 0; v < nfg->countVertices; v++)
        nfg->vertexIds[nfg->originalVertexIds[v]] = v;

    NeighborIterator nitr[1];
    construct_nitr_sg(nitr, acyclicGraph, s_original_id);
    for (
        uint32_t v_original_id;
        acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v_original_id = acyclicGraph->nextVertexId_nitr(nitr)));
    ) {
        uint32_t const v                            = nfg->vertexIds[v_original_id];
        nfg->transitionMtx[s][v].capacity           = nfg->countVertices - 1;
        nfg->transitionMtx[v][s].capacity           = nfg->countVertices - 1;
        nfg->transitionMtx[v][s].residualCapacity   = (int32_t)(nfg->countVertices - 1);
    }

    for (uint32_t v0 = 1; v0 < nfg->countVertices; v0++) {
        uint32_t const v0_original_id   = nfg->originalVertexIds[v0];
        uint32_t const v0p              = NFG_VERTEX_PLUS(nfg, v0);

        nfg->transitionMtx[v0][v0p].capacity            = nfg->countVertices - 1;
        nfg->transitionMtx[v0p][v0].capacity            = nfg->countVertices - 1;
        nfg->transitionMtx[v0p][v0].residualCapacity    = (int32_t)(nfg->countVertices - 1);

        construct_nitr_sg(nitr, acyclicGraph, v0_original_id);
        for (
            uint32_t v1_original_id;
            acyclicGraph->isValidVertex(acyclicGraph->graphPtr, (v1_original_id = acyclicGraph->nextVertexId_nitr(nitr)));
        ) {
            uint32_t const v1                               = nfg->vertexIds[v1_original_id];
            nfg->transitionMtx[v0p][v1].capacity            = nfg->countVertices - 1;
            nfg->transitionMtx[v1][v0p].capacity            = nfg->countVertices - 1;
            nfg->transitionMtx[v1][v0p].residualCapacity    = (int32_t)(nfg->countVertices - 1);
        }
    }

    SimpleGraph flowGraph[1];
    construct_sgi_nfg(flowGraph, nfg);

    VertexPathArray allShortestPaths[1];
    constructAllShortestPaths_vpa(allShortestPaths, flowGraph);

    for (uint32_t v = 1; v < nfg->countVertices; v++) {
        uint32_t const vp = NFG_VERTEX_PLUS(nfg, vp);
        nfg->transitionMtx[v][vp].lowerBound        = 1;
        nfg->transitionMtx[v][vp].residualCapacity  = -1;
    }

    for (uint32_t v = 1; v < nfg->countVertices; v++) {
        VertexPath const* const s_v_path = allShortestPaths->array + v;
        DEBUG_ASSERT(isValid_vpath(s_v_path))
        DEBUG_ASSERT(s_v_path->len > 0)

        for (uint32_t i = 0; i < s_v_path->len - 1; i++) {
            uint32_t const v    = s_v_path->array[i];
            uint32_t const vp   = s_v_path->array[i + 1];

            if (nfg->transitionMtx[v][vp].residualCapacity >= 0) continue;

            i = 0;
            while (i < s_v_path->len - 1) {
                uint32_t const v0 = s_v_path->array[i];
                uint32_t const v1 = s_v_path->array[i + 1];

                nfg->transitionMtx[v0][v1].flow++;
                nfg->transitionMtx[v0][v1].residualCapacity++;
                /* nfg->transitionMtx[v1][v0].residualCapacity--; */
                i++;
            }

            uint32_t const v_last = s_v_path->array[i];
            nfg->transitionMtx[v_last][t].flow++;
            nfg->transitionMtx[v_last][t].residualCapacity++;
            /* nfg->transitionMtx[t][v_last].residualCapacity--; */

            break;
        }
    }

    free_vpa(allShortestPaths);
}

void construct_sgi_nfg(SimpleGraph* const graph, NetworkFlowGraph const* const nfg) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_nfg(nfg))

    *graph = (SimpleGraph){
        nfg,
        countEdges_nfg,
        countVertices_nfg,
        dump_nfg,
        dumpVertex_nfg,
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

void constructFlowStack_nfg(VertexPathArray* const stack, NetworkFlowGraph const* const nfg) {
    DEBUG_ERROR_IF(stack == NULL)
    DEBUG_ASSERT(isValid_nfg(nfg))

    constructEmpty_vpa(stack, VPATH_ARRAY_DEFAULT_INITIAL_CAP);

    uint32_t const s = NFG_START_VERTEX(nfg);
    uint32_t const t = NFG_TERMINAL_VERTEX(nfg);

    SimpleGraph graph[1];
    construct_sgi_nfg(graph, nfg);

    while (1) {
        VertexPath* const flow = pushEmpty_vpa(stack, graph);
        DEBUG_ASSERT(isValid_vpath(flow))

        if (!computeShortest_vpath(flow, graph, s, t))
            break;

        DEBUG_ASSERT(flow->len > 0)

        nfg->transitionMtx[s][flow->array[0]].flow--;
        nfg->transitionMtx[s][flow->array[0]].residualCapacity--;
        for (uint32_t i = 0; i < flow->len - 1; i++) {
            nfg->transitionMtx[flow->array[i]][flow->array[i + 1]].flow--;
            nfg->transitionMtx[flow->array[i]][flow->array[i + 1]].residualCapacity--;
        }
    }

    pop_vpa(stack);
}

void constructPaths_nfg(VertexPathArray* const paths, NetworkFlowGraph const* const nfg) {
    DEBUG_ERROR_IF(paths == NULL)
    DEBUG_ASSERT(isValid_nfg(nfg))

    VertexPathArray stack[1];
    constructFlowStack_nfg(stack, nfg);

    constructEmpty_vpa(paths, stack->size);

    while (stack->size > 0) {
        VertexPath const* const flow = pop_vpa(stack);
        DEBUG_ASSERT(isValid_vpath(flow))

        VertexPath* const path = pushEmpty_vpa(stack, nfg->acyclicGraph);
        DEBUG_ASSERT(isValid_vpath(path))

        for (uint32_t i = 0; i < flow->len; i++) {
            uint32_t const originalVertexId = nfg->originalVertexIds[flow->array[i]];
            DEBUG_ASSERT(nfg->acyclicGraph->isValidVertex(nfg->acyclicGraph->graphPtr, originalVertexId))
            DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(path, originalVertexId, 1))
        }
    }

    free_vpa(stack);
}

uint32_t countEdges_nfg(void const* const graphPtr) {
    static uint32_t count                       = 0xFFFFFFFF;
    static NetworkFlowGraph const* cached_ptr   = NULL;

    DEBUG_ASSERT(isValid_nfg(graphPtr))

    if (graphPtr == cached_ptr)
        return cached_count;

    cached_ptr  = (NetworkFlowGraph const*)graphPtr;
    count       = 0;

    uint32_t const s = NFG_START_VERTEX(nfg);
    uint32_t const t = NFG_TERMINAL_VERTEX(nfg);

    count += isValidBackward_nft(nfg->transitionMtx[t] + s);
    count += isValidForward_nft(nfg->transitionMtx[s] + t);

    for (uint32_t v0 = 1; v0 < nfg->countVertices - 1; v0++) {
        uint32_t const v0p = NFG_VERTEX_PLUS(nfg, v0);

        count += isValidBackward_nft(nfg->transitionMtx[v0] + s);
        count += isValidBackward_nft(nfg->transitionMtx[v0p] + v0);
        count += isValidBackward_nft(nfg->transitionMtx[t] + v0p);
        count += isValidForward_nft(nfg->transitionMtx[s] + v0);
        count += isValidForward_nft(nfg->transitionMtx[v0] + v0p);
        count += isValidForward_nft(nfg->transitionMtx[v0p] + t);

        for (uint32_t v1 = v0 + 1; v1 < nfg->countVertices; v1++) {
            count += isValidBackward_nft(nfg->transitionMtx[v0] + v1p);
            count += isValidBackward_nft(nfg->transitionMtx[v1] + v0p);
            count += isValidForward_nft(nfg->transitionMtx[v0p] + v1);
            count += isValidForward_nft(nfg->transitionMtx[v1p] + v0);
        }
    }

    return count;
}

uint32_t countVertices_nfg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;
    return nfg->size;
}

void dump_nfg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_nfg(graphPtr))
    DEBUG_ERROR_IF(output == NULL)

    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    uint32_t const s = NFG_START_VERTEX(nfg);
    uint32_t const t = NFG_TERMINAL_VERTEX(nfg);

    for (uint32_t v = 1; v < nfg->countVertices; v++) {
        if (!isValidForward_nft(nfg->transitionMtx[s] + v)) continue;

        dumpVertex_nfg(graphPtr, output, s);
        fputs(" ->", output);
        dumpVertex_nfg(graphPtr, output, v);
        fputs("\n", output);
    }

    if (isValidForward_nft(nfg->transitionMtx[s] + t)) {
        dumpVertex_nfg(graphPtr, output, s);
        fputs(" ->", output);
        dumpVertex_nfg(graphPtr, output, t);
        fputs("\n", output);
    }

    for (uint32_t v0 = 1; v0 < nfg->countVertices; v0++) {
        uint32_t const v0p = NFG_VERTEX_PLUS(nfg, v0);

        if (!isValidForward_nft(nfg->transitionMtx[v0] + v0p)) continue;

        dumpVertex_nfg(graphPtr, output, v0);
        fputs(" ->", output);
        dumpVertex_nfg(graphPtr, output, v0p);
        fputs("\n", output);

        for (uint32_t v1 = 1; v1 < nfg->countVertices; v1++) {
            if (!isValidForward_nft(nfg->transitionMtx[v0p] + v1)) continue;

            dumpVertex_nfg(graphPtr, output, v0p);
            fputs(" ->", output);
            dumpVertex_nfg(graphPtr, output, v1);
            fputs("\n", output);
        }

        if (!isValidForward_nft(nfg->transitionMtx[v0p] + t)) continue;

        dumpVertex_nfg(graphPtr, output, v0p);
        fputs(" ->", output);
        dumpVertex_nfg(graphPtr, output, t);
        fputs("\n", output);
    }
}

void dumpVertex(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
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

void free_nfg(NetworkFlowGraph* const nfg) {
    DEBUG_ASSERT(isValid_nfg(nfg))

    free(nfg->originalVertexIds);
    free(nfg->vertexIds);

    for (uint32_t i = 0; i < nfg->size; i++)
        free(nfg->transitionMtx[i]);

    free(nfg->transitionMtx);

    *nfg = {NOT_AN_NFG};
}

bool isValid_nfg(void const* const graphPtr) {
    NetworkFlowGraph const* const nfg = (NetworkFlowGraph const*)graphPtr;

    return  nfg != NULL                             &&
            isValid_sg(nfg->acyclicGraph)           &&
            nfg->countVertices > 0                  &&
            nfg->size > nfg->countVertices          &&
            nfg->size == nfg->countVertices << 1    &&
            nfg->originalVertexIds != NULL          &&
            nfg->vertexIds != NULL                  &&
            nfg->transitionMtx != NULL;
}

bool isValid_nft(NetworkFlowTransition const* const transition) {
    return  transition != NULL                          &&
            transition->capacity > 0                    &&
            transition->lowerBound <= transition->flow  &&
            transition->flow <= transition->capacity;
}

bool isValid_nitr_nfg(NeighborIterator const* const itr) {
    
}

bool isValidBackward_nft(NetworkFlowTransition const* const transition) {
    return  isValid_nft(transition) &&
            transition->residualCapacity == (int32_t)(transition->capacity - transition->flow);
}

bool isValidForward_nft(NetworkFlowTransition const* const transition) {
    return  isValid_nft(transition) &&
            transition->residualCapacity == (int32_t)(transition->flow - transition->lowerBound);
}

void minimizeTotalFlow_nfg(NetworkFlowGraph* const nfg) {
    
}
