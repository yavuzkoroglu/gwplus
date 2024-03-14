/**
 * @file hpathgraph.c
 * @brief Implements the functions defined in hpathgraph.h
 * @author Anonymized for ICSE2025
 */
#include <inttypes.h>
#include <string.h>
#include "hpathgraph.h"
#include "padkit/debug.h"

void construct_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph) {
    DEBUG_ERROR_IF(hpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(pathGraph))

    hpgraph->pathGraph = pathGraph;

    uint32_t const sz   = pathGraph->countVertices(pathGraph->graphPtr);
    uint32_t const cap  = sz << 1;
    DEBUG_ASSERT(cap > sz)

    constructVerticesAsPaths_vpa(hpgraph->hpaths, pathGraph);
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(hpgraph->edgeMtx, cap, cap))
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(hpgraph->subsumptionMtx, 1, cap))

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, pathGraph);
    for (
        uint32_t pathId;
        pathGraph->isValidVertex(pathGraph->graphPtr, (pathId = pathGraph->nextVertexId_vitr(vitr)));
    ) {
        #ifndef NDEBUG
            VertexPath* const hpath = hpgraph->hpaths->array + pathId;
            DEBUG_ASSERT(isValid_vpath(hpath))
            DEBUG_ASSERT(hpath->len == 1)
        #endif

        NeighborIterator nitr[1];
        construct_nitr_sg(nitr, pathGraph, pathId);
        for (
            uint32_t neighborId;
            pathGraph->isValidVertex(pathGraph->graphPtr, (neighborId = pathGraph->nextVertexId_nitr(nitr)));
        ) connect_gmtx(hpgraph->edgeMtx, pathId, neighborId);
    }
}

void construct_sgi_hpg(SimpleGraph* const graph, HyperPathGraph const* const hpgraph) {
    DEBUG_ERROR_IF(graph == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    *graph = (SimpleGraph){
        hpgraph,
        countEdges_hpg,
        countVertices_hpg,
        dump_hpg,
        dumpVertex_hpg,
        isValid_hpg,
        isValid_nitr_hpg,
        isValid_svitr_hpg,
        isValid_vitr_hpg,
        isValidEdge_hpg,
        isValidVertex_hpg,
        nextVertexId_nitr_hpg,
        nextVertexId_svitr_hpg,
        nextVertexId_vitr_hpg,
        setFirstNextId_nitr_hpg,
        setFirstNextId_svitr_hpg,
        setFirstNextId_vitr_hpg
    };
}

void constructAcyclic_hpg(HyperPathGraph* const hpgraph, SimpleGraph const* const pathGraph) {
    DEBUG_ERROR_IF(hpgraph == NULL)
    DEBUG_ASSERT(isValid_sg(pathGraph))

    construct_hpg(hpgraph, pathGraph);

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    for (
        VertexPath* hpath;
        computeShortestCycle_vpath((hpath = pushEmpty_vpa(hpgraph->hpaths, hyperPathGraph)), hyperPathGraph);
    ) {
        uint32_t const parentId = hpgraph->hpaths->size - 1;

        /*
        puts("");
        dumpVertex_hpg(hpgraph, stdout, parentId);
        printf(":");
        dump_vpath(hpath, stdout);
        */

        for (uint32_t i = 0; i < hpath->len; i++) {
            uint32_t childId = hpath->array[i];
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->subsumptionMtx, 0, childId))

            VertexIterator itr[1];
            construct_vitr_sg(itr, hyperPathGraph);
            for (
                uint32_t pathId;
                isValidVertex_hpg(hpgraph, (pathId = nextVertexId_vitr_hpg(itr)));
            ) {
                if (pathId == parentId || contains_vpath(hpath, pathId)) continue;
                if (isConnected_gmtx(hpgraph->edgeMtx, childId, pathId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, parentId, pathId))
                if (isConnected_gmtx(hpgraph->edgeMtx, pathId, childId))
                    DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(hpgraph->edgeMtx, pathId, parentId))
            }
        }

        /*
        dump_hpg(hpgraph, stdout);
        */
    }
    pop_vpa(hpgraph->hpaths);
}

void constructPathTrace_hpg(VertexPath* const pathTrace, HyperPathGraph* const hpgraph, uint32_t const rootId) {
    DEBUG_ERROR_IF(pathTrace == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))
    DEBUG_ASSERT(rootId < hpgraph->hpaths->size)

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    if (pathTrace->isAllocated) {
        flush_vpath(pathTrace);
        pathTrace->graph = hyperPathGraph;
    } else {
        constructEmpty_vpath(pathTrace, hyperPathGraph);
    }

    extend_vpath(pathTrace, rootId, 0);

    VertexPath secondTrace[1];
    constructEmpty_vpath(secondTrace, hyperPathGraph);

    VertexPath partialTrace[1] = {NOT_A_VPATH};

    VertexPath* current = pathTrace;
    VertexPath* next    = secondTrace;

    GraphMatrix coverMtx[1];
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(coverMtx, 1, hpgraph->hpaths->size))

    while (current->len != next->len) {
        flush_vpath(next);

        /*
        printf("CURRENT =");
        dump_vpath(current, stdout);
        */

        uint32_t prevPathId = current->array[current->len - 1];

        for (uint32_t i = 0; i < current->len; i++) {
            uint32_t const pathId     = current->array[i];
            uint32_t const nextPathId = (i == current->len - 1)
                ? ((current->len == 1) ? pathId : next->array[0])
                : current->array[i + 1];

            if (hpgraph->pathGraph->isValidVertex(hpgraph->pathGraph->graphPtr, pathId)) {
                extend_vpath(next, pathId, 0);
                prevPathId = pathId;
                continue;
            }

            clone_vpath(partialTrace, hpgraph->hpaths->array + pathId);
            DEBUG_ASSERT(partialTrace->len > 0)

            for (uint32_t k = 0; k < partialTrace->len; k++)
                DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(hpgraph->subsumptionMtx, 0, partialTrace->array[k]))

            uint32_t nRotations = partialTrace->len;
            while (nRotations > 0 && prevPathId != pathId && !isValidEdge_hpg(hpgraph, prevPathId, partialTrace->array[0])) {
                nRotations--;
                DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(partialTrace))
            }

            if (nRotations == 0) {
                extend_vpath(next, pathId, 0);
                prevPathId = pathId;
                continue;
            }

            if (nextPathId == pathId || isValidEdge_hpg(hpgraph, partialTrace->array[partialTrace->len - 1], nextPathId)) {
                concat_vpath(next, partialTrace);
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, pathId))
                prevPathId = next->array[next->len - 1];
                continue;
            }

            uint32_t r = 0;
            while (r < partialTrace->len && !isValidEdge_hpg(hpgraph, partialTrace->array[r], nextPathId))
                r++;

            if (r == partialTrace->len) {
                extend_vpath(next, pathId, 0);
                prevPathId = pathId;
                continue;
            }

            if (!isConnected_gmtx(coverMtx, 0, pathId)) {
                concat_vpath(next, partialTrace);
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, pathId))
            }
            for (uint32_t k = 0; k <= r; k++)
                extend_vpath(next, partialTrace->array[k], 0);

            /*
            printf("NEXT =");
            dump_vpath(next, stdout);
            */

            prevPathId = next->array[next->len - 1];
        }

        VertexPath* const tmp   = current;
        current                 = next;
        next                    = tmp;
    }

    free_vpath(secondTrace);
    if (partialTrace->isAllocated)
        free_vpath(partialTrace);
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(coverMtx))

    pathTrace->graph = hpgraph->pathGraph;
}

/*
void constructPathTrace_hpg(VertexPath* const pathTrace, HyperPathGraph* const hpgraph, uint32_t const rootId) {
    DEBUG_ERROR_IF(pathTrace == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))
    DEBUG_ASSERT(rootId < hpgraph->hpaths->size)

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    VertexPath traces[3]        = {NOT_A_VPATH, NOT_A_VPATH, NOT_A_VPATH};
    VertexPath* trace_A         = traces;
    VertexPath* trace_B         = traces + 1;
    VertexPath* partialTrace    = traces + 2;

    constructEmpty_vpath(trace_A, hyperPathGraph);
    constructEmpty_vpath(trace_B, hyperPathGraph);

    extend_vpath(trace_A, rootId, 0);

    GraphMatrix coverMtx[1];
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(coverMtx, 1, hpgraph->hpaths->size))

    while (trace_A->len != trace_B->len) {
        flush_vpath(trace_B);

        printf("trace_A = ");
        dump_vpath(trace_A, stdout);

        uint32_t step = 1;
        for (uint32_t i = 0; i < trace_A->len; i += step) {
            step = 1;

            uint32_t const pathId = trace_A->array[i];

            if (hpgraph->pathGraph->isValidVertex(hpgraph->pathGraph->graphPtr, pathId)) {
                extend_vpath(trace_B, pathId, 0);
                continue;
            }

            clone_vpath(partialTrace, hpgraph->hpaths->array + pathId);
            DEBUG_ASSERT(partialTrace->len > 0)

            for (uint32_t k = 0; k < partialTrace->len; k++)
                DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(hpgraph->subsumptionMtx, 0, partialTrace->array[k]))

            if (trace_A->len == 1) {
                concat_vpath(trace_B, partialTrace);
                break;
            }

            uint32_t const prevPathId = (trace_B->len > 0)
                ? trace_B->array[trace_B->len - 1]
                : trace_A->array[(i + trace_A->len - 1) % trace_A->len];

            uint32_t nextPathId;
            if (i == trace_A->len - 1) {
                nextPathId = trace_B->array[0];
            } else {
                uint32_t j = i + 1;
                nextPathId = trace_A->array[j];
                while (isConnected_gmtx(coverMtx, 0, nextPathId)) {
                    if (j == trace_A->len - 1) {
                        if (isValidEdge_hpg(hpgraph, pathId, trace_B->array[0])) {
                            step++;
                            nextPathId = trace_B->array[0];
                        }
                        break;
                    } else if (isValidEdge_hpg(hpgraph, pathId, trace_A->array[j + 1])) {
                        step++;
                        j++;
                        nextPathId = trace_A->array[j];
                        continue;
                    } else {
                        nextPathId = trace_A->array[j];
                        break;
                    }
                }
            }

            if (isConnected_gmtx(coverMtx, 0, pathId)) {
                if (isValidEdge_hpg(hpgraph, prevPathId, nextPathId))
                    continue;

                uint32_t len    = 0xFFFFFFFF;
                uint32_t start  = 0xFFFFFFFF;
                uint32_t end    = 0xFFFFFFFF;
                for (uint32_t j = 0; j < partialTrace->len; j++) {
                    if (isValidEdge_hpg(hpgraph, prevPathId, partialTrace->array[j])) {
                        uint32_t const limit = j + partialTrace->len;
                        for (uint32_t k = j; k < limit; k++) {
                            if (isValidEdge_hpg(hpgraph, partialTrace->array[k % partialTrace->len], nextPathId)) {
                                uint32_t const candidate_len = k - j + 1;
                                if (candidate_len < len) {
                                    len     = candidate_len;
                                    start   = j;
                                    end     = k;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                DEBUG_ERROR_IF(start == 0xFFFFFFFF)
                DEBUG_ERROR_IF(end == 0xFFFFFFFF)

                for (uint32_t j = start; j <= end; j++)
                    extend_vpath(trace_B, partialTrace->array[j % partialTrace->len], 0);
            } else {
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(coverMtx, 0, pathId))

                uint32_t len    = 0xFFFFFFFF;
                uint32_t start  = 0xFFFFFFFF;
                uint32_t end    = 0xFFFFFFFF;
                for (uint32_t j = 0; j < partialTrace->len; j++) {
                    if (isValidEdge_hpg(hpgraph, prevPathId, partialTrace->array[j])) {
                        uint32_t const limit = j + partialTrace->len + partialTrace->len - 1;
                        for (uint32_t k = j + partialTrace->len - 1; k < limit; k++) {
                            if (isValidEdge_hpg(hpgraph, partialTrace->array[k % partialTrace->len], nextPathId)) {
                                uint32_t const candidate_len = k - j + 1;
                                if (candidate_len < len) {
                                    len     = candidate_len;
                                    start   = j;
                                    end     = k;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                if (start == 0xFFFFFFFF) {
                    printf("Cannot extend %u\n", pathId);
                }
                DEBUG_ERROR_IF(start == 0xFFFFFFFF)
                DEBUG_ERROR_IF(end == 0xFFFFFFFF)

                printf("start, end = %u, %u\n", start, end);

                for (uint32_t j = start; j <= end; j++)
                    extend_vpath(trace_B, partialTrace->array[j % partialTrace->len], 0);
            }

            printf("trace_B = ");
            dump_vpath(trace_B, stdout);
        }

        if (trace_A < trace_B) {
            trace_A++;
            trace_B--;
        } else {
            trace_A--;
            trace_B++;
        }
    }

    clone_vpath(pathTrace, trace_A);
    DEBUG_ASSERT(isValid_vpath(trace_A))
    DEBUG_ASSERT(isValid_vpath(pathTrace))
    pathTrace->graph = hpgraph->pathGraph;
    DEBUG_ASSERT(isValid_vpath(pathTrace))

    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(coverMtx))

    free_vpath(trace_A);
    free_vpath(trace_B);
    if (partialTrace->isAllocated)
        free_vpath(partialTrace);
}
*/

void constructTestPaths_hpg(VertexPathArray* const testPaths, HyperPathGraph* const hpgraph) {
    DEBUG_ERROR_IF(testPaths == NULL)
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)hpgraph->pathGraph->graphPtr;

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hyperPathGraph);
    uint32_t const s_id = nextVertexId_svitr_hpg(svitr);
    DEBUG_ASSERT(isValidVertex_hpg(hpgraph, s_id))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, hyperPathGraph, s_id);
    uint32_t const rootId = nextVertexId_nitr_hpg(itr);

    VertexPath pathTrace[1] = {NOT_A_VPATH};
    constructPathTrace_hpg(pathTrace, hpgraph, rootId);

    uint32_t shortestLen        = 0xFFFFFFFF;
    uint32_t shortestPathId     = 0xFFFFFFFF;

    constructEmpty_vpa(testPaths, pathTrace->len);

    for (uint32_t nRotations = pathTrace->len; nRotations > 0; nRotations--) {
        if (hpgraph->pathGraph->isValidEdge(hpgraph->pathGraph->graphPtr, s_id, pathTrace->array[0])) {
            VertexPath* const testPath = pushEmpty_vpa(testPaths, vpgraph->graph);
            constructTestPath_vpg(testPath, vpgraph, pathTrace);

            if (testPath->len < shortestLen) {
                shortestLen     = testPath->len;
                shortestPathId  = (uint32_t)(testPath - testPaths->array);
            }
        }

        DEBUG_ASSERT_NDEBUG_EXECUTE(rotate_vpath(pathTrace))
    }

    DEBUG_ERROR_IF(shortestPathId >= testPaths->size)

    VertexPath tmp[1];
    VertexPath* const shortestPath = testPaths->array + shortestPathId;
    memcpy(tmp, testPaths->array, sizeof(VertexPath));
    memcpy(testPaths->array, shortestPath, sizeof(VertexPath));
    memcpy(shortestPath, tmp, sizeof(VertexPath));
    testPaths->size = 1;

    if (pathTrace->isAllocated)
        free_vpath(pathTrace);
}

uint32_t countEdges_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    if (hpgraph->hpaths->size == 0)
        return 0;

    uint32_t count = 0;
    for (uint32_t i = 0; i < hpgraph->hpaths->size - 1; i++) {
        if (isConnected_gmtx(hpgraph->subsumptionMtx, 0, i))
            continue;

        for (uint32_t j = i + 1; j < hpgraph->hpaths->size; j++) {
            if (isConnected_gmtx(hpgraph->subsumptionMtx, 0, j))
                continue;

            count += isConnected_gmtx(hpgraph->edgeMtx, i, j);
            count += isConnected_gmtx(hpgraph->edgeMtx, j, i);
        }
    }

    return count;
}

uint32_t countVertices_hpg(void const* const graphPtr) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    uint32_t count = 0;
    for (uint32_t i = 0; i < hpgraph->hpaths->size; i++)
        count += !isConnected_gmtx(hpgraph->subsumptionMtx, 0, i);

    return count;
}

void dump_hpg(void const* const graphPtr, FILE* const output) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    DEBUG_ERROR_IF(output == NULL)

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hyperPathGraph);
    uint32_t const s_id = hyperPathGraph->nextVertexId_svitr(svitr);
    DEBUG_ASSERT(hyperPathGraph->isValidVertex(graphPtr, s_id))

    NeighborIterator itr[1];
    construct_nitr_sg(itr, hyperPathGraph, s_id);
    for (
        uint32_t neighborId;
        hyperPathGraph->isValidVertex(graphPtr, (neighborId = hyperPathGraph->nextVertexId_nitr(itr)));
    ) {
        hyperPathGraph->dumpVertex(graphPtr, output, s_id);
        fputs(" ->", output);
        hyperPathGraph->dumpVertex(graphPtr, output, neighborId);
        fputs(";\n", output);
    }

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, hyperPathGraph);
    for (
        uint32_t vertexId;
        hyperPathGraph->isValidVertex(graphPtr, (vertexId = hyperPathGraph->nextVertexId_vitr(vitr)));
    ) {
        if (vertexId == s_id) continue;
        construct_nitr_sg(itr, hyperPathGraph, vertexId);

        for (
            uint32_t neighborId;
            hyperPathGraph->isValidVertex(graphPtr, (neighborId = hyperPathGraph->nextVertexId_nitr(itr)));
        ) {
            hyperPathGraph->dumpVertex(graphPtr, output, vertexId);
            fputs(" ->", output);
            hyperPathGraph->dumpVertex(graphPtr, output, neighborId);
            fputs(";\n", output);
        }
    }
}

void dumpVertex_hpg(void const* const graphPtr, FILE* const output, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    DEBUG_ASSERT(isValidVertex_hpg(graphPtr, vertexId))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    SimpleGraph hyperPathGraph[1];
    construct_sgi_hpg(hyperPathGraph, hpgraph);

    StartVertexIterator itr[1];
    construct_svitr_sg(itr, hyperPathGraph);
    uint32_t const startVertexId = hyperPathGraph->nextVertexId_svitr(itr);
    if (startVertexId == vertexId)
        fputs(" s", output);
    else if (vertexId < startVertexId)
        fprintf(output, " %"PRIu32, vertexId);
    else
        fprintf(output, " %"PRIu32, vertexId);
}

void free_hpg(HyperPathGraph* const hpgraph) {
    DEBUG_ASSERT(isValid_hpg(hpgraph))

    free_vpa(hpgraph->hpaths);
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(hpgraph->edgeMtx))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(hpgraph->subsumptionMtx))
    *hpgraph = NOT_A_HPATH_GRAPH;
}

bool isValid_hpg(void const* const graphPtr) {
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;
    return  hpgraph != NULL                         &&
            isValid_sg(hpgraph->pathGraph)          &&
            isValid_vpa(hpgraph->hpaths)            &&
            isValid_gmtx(hpgraph->edgeMtx)          &&
            isValid_gmtx(hpgraph->subsumptionMtx);
}

bool isValid_nitr_hpg(NeighborIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr) && isValidVertex_hpg(itr->graphPtr, itr->vertexId);
}

bool isValid_svitr_hpg(StartVertexIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValid_vitr_hpg(VertexIterator const* const itr) {
    return itr != NULL && isValid_hpg(itr->graphPtr);
}

bool isValidEdge_hpg(void const* const graphPtr, uint32_t const sourceVertexId, uint32_t const targetVertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    return  isValidVertex_hpg(graphPtr, sourceVertexId)                         &&
            isValidVertex_hpg(graphPtr, targetVertexId)                         &&
            isConnected_gmtx(hpgraph->edgeMtx, sourceVertexId, targetVertexId);
}

bool isValidVertex_hpg(void const* const graphPtr, uint32_t const vertexId) {
    DEBUG_ASSERT(isValid_hpg(graphPtr))
    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)graphPtr;

    return vertexId < hpgraph->hpaths->size && !isConnected_gmtx(hpgraph->subsumptionMtx, 0, vertexId);
}

uint32_t nextVertexId_nitr_hpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_hpg(itr))

    while (!isValidEdge_hpg(itr->graphPtr, itr->vertexId, itr->nextNeighborId)) {
        if (itr->nextNeighborId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextNeighborId--;
    }

    return itr->nextNeighborId--;
}

uint32_t nextVertexId_svitr_hpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_hpg(itr))

    if (!isValidVertex_hpg(itr->graphPtr, itr->nextVertexId)) return 0xFFFFFFFF;

    uint32_t const s_id = itr->nextVertexId;
    itr->nextVertexId = 0xFFFFFFFF;
    return s_id;
}

uint32_t nextVertexId_vitr_hpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_hpg(itr))

    while (!isValidVertex_hpg(itr->graphPtr, itr->nextVertexId)) {
        if (itr->nextVertexId == 0xFFFFFFFF) return 0xFFFFFFFF;
        itr->nextVertexId--;
    }

    return itr->nextVertexId--;
}

void setFirstNextId_nitr_hpg(NeighborIterator* const itr) {
    DEBUG_ASSERT(isValid_nitr_hpg(itr))

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;
    itr->nextNeighborId                 = hpgraph->hpaths->size - 1;
}

void setFirstNextId_svitr_hpg(StartVertexIterator* const itr) {
    DEBUG_ASSERT(isValid_svitr_hpg(itr))

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;

    StartVertexIterator svitr[1];
    construct_svitr_sg(svitr, hpgraph->pathGraph);
    itr->nextVertexId = hpgraph->pathGraph->nextVertexId_svitr(svitr);
}

void setFirstNextId_vitr_hpg(VertexIterator* const itr) {
    DEBUG_ASSERT(isValid_vitr_hpg(itr))

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)itr->graphPtr;
    itr->nextVertexId                   = hpgraph->hpaths->size - 1;
}

