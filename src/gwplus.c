/**
 * @file gwplus.c
 * @brief Implements the main function for the gwplus executable.
 * @author Anonymized for ICSE2025
 */
#include <inttypes.h>
#include <string.h>
#include "coverage.h"
#include "gwmodel.h"
#include "hpathgraph.h"
#include "padkit/debug.h"
#include "padkit/graphmatrix.h"
#include "padkit/repeat.h"
#include "padkit/streq.h"
#include "padkit/timestamp.h"

static void convertToEdgePaths(
    VertexPathArray* const newRequirements,
    SimpleGraph* const graph, GWModelArray* const gwma,
    VertexPathArray const* const requirements
) {
    DEBUG_ERROR_IF(newRequirements == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ASSERT(isValid_vpa(requirements))
    DEBUG_ERROR_IF(gwma->useLineGraph)

    GWModelArray newGwma[1];
    memcpy(newGwma, gwma, sizeof(GWModelArray));
    newGwma->useLineGraph   = 1;
    newGwma->adjLists       = NULL;
    fillAdjLists_gwma(newGwma);

    SimpleGraph newGraph[1];
    construct_sgi_gwma(newGraph, newGwma);

    constructEmpty_vpa(newRequirements, requirements->cap);
    for (uint32_t requirementId = 0; requirementId < requirements->size; requirementId++) {
        VertexPath const* const requirement = requirements->array + requirementId;
        DEBUG_ASSERT(isValid_vpath(requirement))
        DEBUG_ASSERT(requirement->len > 0)

        VertexPath* const newRequirement = pushEmpty_vpa(newRequirements, newGraph);
        for (uint32_t i = 0; i < requirement->len - 1; i++) {
            uint32_t const v_id     = requirement->array[i];
            uint32_t const vp_id    = requirement->array[i + 1];
            DEBUG_ASSERT(v_id < gwma->size_vertices)
            DEBUG_ASSERT(vp_id < gwma->size_vertices)

            GWVertex const* const v     = gwma->vertices + v_id;
            GWVertex const* const vp    = gwma->vertices + vp_id;
            DEBUG_ASSERT(isValid_gwvertex(v))
            DEBUG_ASSERT(isValid_gwvertex(vp))

            for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
                GWEdge const* const e = gwma->edges + e_id;
                DEBUG_ASSERT(isValid_gwedge(e))

                GWVertex const* const v_a = gwma->vertices + e->source;
                GWVertex const* const v_b = gwma->vertices + e->target;
                DEBUG_ASSERT(isValid_gwvertex(v_a))
                DEBUG_ASSERT(isValid_gwvertex(v_b))

                if (areEqual_gwvertex(v, v_a) && areEqual_gwvertex(vp, v_b)) {
                    DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(newRequirement, e_id, 1))
                    break;
                }
            }
        }
    }

    freeAdjLists_gwma(gwma);
    memcpy(gwma, newGwma, sizeof(GWModelArray));

    for (uint32_t requirementId = 0; requirementId < newRequirements->size; requirementId++) {
        VertexPath* const requirement = newRequirements->array + requirementId;
        DEBUG_ERROR_IF(requirement == NULL)

        requirement->graph = graph;
    }
}

static void convertToEdgePathsAndIncludeRemainingEdges(
    VertexPathArray* const newRequirements,
    SimpleGraph* const graph, GWModelArray* const gwma,
    VertexPathArray const* const requirements
) {
    DEBUG_ERROR_IF(newRequirements == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_gwma(gwma))
    DEBUG_ASSERT(isValid_vpa(requirements))
    DEBUG_ERROR_IF(gwma->useLineGraph)

    GWModelArray newGwma[1];
    memcpy(newGwma, gwma, sizeof(GWModelArray));
    newGwma->useLineGraph   = 1;
    newGwma->adjLists       = NULL;
    fillAdjLists_gwma(newGwma);

    SimpleGraph newGraph[1];
    construct_sgi_gwma(newGraph, newGwma);

    GraphMatrix edgeMtx[1];
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(edgeMtx, 1, gwma->size_edges))

    constructEmpty_vpa(newRequirements, requirements->cap);
    for (uint32_t requirementId = 0; requirementId < requirements->size; requirementId++) {
        VertexPath const* const requirement = requirements->array + requirementId;
        DEBUG_ASSERT(isValid_vpath(requirement))
        DEBUG_ASSERT(requirement->len > 0)

        VertexPath* const newRequirement = pushEmpty_vpa(newRequirements, newGraph);
        for (uint32_t i = 0; i < requirement->len - 1; i++) {
            uint32_t const v_id     = requirement->array[i];
            uint32_t const vp_id    = requirement->array[i + 1];
            DEBUG_ASSERT(v_id < gwma->size_vertices)
            DEBUG_ASSERT(vp_id < gwma->size_vertices)

            GWVertex const* const v     = gwma->vertices + v_id;
            GWVertex const* const vp    = gwma->vertices + vp_id;
            DEBUG_ASSERT(isValid_gwvertex(v))
            DEBUG_ASSERT(isValid_gwvertex(vp))

            for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
                GWEdge const* const e = gwma->edges + e_id;
                DEBUG_ASSERT(isValid_gwedge(e))

                GWVertex const* const v_a = gwma->vertices + e->source;
                GWVertex const* const v_b = gwma->vertices + e->target;
                DEBUG_ASSERT(isValid_gwvertex(v_a))
                DEBUG_ASSERT(isValid_gwvertex(v_b))

                if (areEqual_gwvertex(v, v_a) && areEqual_gwvertex(vp, v_b)) {
                    if (isConnected_gmtx(edgeMtx, 0, e_id)) {
                        for (uint32_t ep_id = e_id + 1; ep_id < gwma->size_edges; ep_id++) {
                            if (isConnected_gmtx(edgeMtx, 0, ep_id)) continue;

                            GWEdge const* const ep = gwma->edges + ep_id;
                            DEBUG_ASSERT(isValid_gwedge(ep))

                            GWVertex const* const v_c = gwma->vertices + ep->source;
                            GWVertex const* const v_d = gwma->vertices + ep->target;
                            DEBUG_ASSERT(isValid_gwvertex(v_c))
                            DEBUG_ASSERT(isValid_gwvertex(v_d))

                            if (areEqual_gwvertex(v, v_c) && areEqual_gwvertex(vp, v_d)) {
                                e_id = ep_id;
                                break;
                            }
                        }
                        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(edgeMtx, 0, e_id))
                    } else {
                        DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(edgeMtx, 0, e_id))
                    }
                    DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(newRequirement, e_id, 1))
                    break;
                }
            }
        }
    }

    for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
        if (isConnected_gmtx(edgeMtx, 0, e_id)) continue;

        VertexPath* const newRequirement = pushEmpty_vpa(newRequirements, newGraph);
        DEBUG_ASSERT_NDEBUG_EXECUTE(extend_vpath(newRequirement, e_id, 1))
    }

    freeAdjLists_gwma(gwma);
    memcpy(gwma, newGwma, sizeof(GWModelArray));
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(edgeMtx))

    for (uint32_t requirementId = 0; requirementId < newRequirements->size; requirementId++) {
        VertexPath* const requirement = newRequirements->array + requirementId;
        DEBUG_ERROR_IF(requirement == NULL)

        requirement->graph = graph;
    }
}

static void generateDotOfPathGraph(FILE* const output, SimpleGraph const* const pathGraph, GWModelArray const* const gwma) {
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValid_vpg(pathGraph->graphPtr))
    DEBUG_ASSERT(isValid_gwma(gwma))

    VertexPathGraph const* const vpgraph = (VertexPathGraph const*)pathGraph->graphPtr;

    Chunk const* const chunk_names = gwma->useLineGraph
        ? gwma->chunks + GWMA_CHUNK_EDGE_NAMES
        : gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;

    fputs(
        "digraph PathGraph {\n"
        "    rankdir=LR;\n"
        "    node [shape=\"rectangle\"];\n"
        "    s [shape=\"circle\"];\n",
        output
    );

    uint32_t const nPaths = pathGraph->countVertices(pathGraph->graphPtr);
    for (uint32_t pathId = 0; pathId < nPaths - 1; pathId++) {
        VertexPath const* const path = vpgraph->vpaths->array + pathId;
        DEBUG_ASSERT(isValid_vpath(path))

        fprintf(output, "    %"PRIu32" [label=\"p%"PRIu32":\\l", pathId, pathId);

        for (uint32_t i = 0; i < path->len; i++) {
            char const* const label = get_chunk(chunk_names, path->array[i]);
            DEBUG_ERROR_IF(label == NULL)

            fprintf(output, "%s\\l", label);
        }

        fputs("\"];\n", output);
    }

    NeighborIterator itr[1];
    construct_nitr_sg(itr, pathGraph, nPaths - 1);
    for (
        uint32_t pathId;
        pathGraph->isValidVertex(vpgraph, (pathId = pathGraph->nextVertexId_nitr(itr)));
    ) fprintf(output, "    s -> %"PRIu32";\n", pathId);

    for (uint32_t p0_id = 0; p0_id < nPaths - 1; p0_id++) {
        construct_nitr_sg(itr, pathGraph, p0_id);
        for (
            uint32_t p1_id;
            pathGraph->isValidVertex(vpgraph, (p1_id = pathGraph->nextVertexId_nitr(itr)));
        ) fprintf(output, "    %"PRIu32" -> %"PRIu32";\n", p0_id, p1_id);
    }

    fputs("}", output);
}

static void generateDotOfSimpleGraph(FILE* const output, SimpleGraph const* const graph) {
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_gwma(graph->graphPtr))

    GWModelArray const* const gwma = (GWModelArray const*)graph->graphPtr;

    Chunk const* const chunk_vertex_names   = gwma->chunks + GWMA_CHUNK_VERTEX_NAMES;
    Chunk const* const chunk_edge_names     = gwma->chunks + GWMA_CHUNK_EDGE_NAMES;

    fputs(
        "digraph SimpleGraph {\n"
        "    node [shape=\"rectangle\"];\n"
        "    reset [shape=\"none\", label=\"\", width=0, height=0];\n",
        output
    );

    VertexIterator vitr[1];
    construct_vitr_sg(vitr, graph);
    for (
        uint32_t v_id;
        graph->isValidVertex(gwma, (v_id = graph->nextVertexId_vitr(vitr)));
    ) {
        char const* const label = get_chunk(gwma->useLineGraph ? chunk_edge_names : chunk_vertex_names, v_id);
        DEBUG_ERROR_IF(label == NULL)

        fprintf(output, "    %"PRIu32" [label=\"%s\"];\n", v_id, label);
    }

    if (!gwma->useLineGraph) {
        if (gwma->s_type == GWMA_START_ELEMENT_TYPE_VERTEX) {
            fprintf(output, "    reset -> %"PRIu32";\n", gwma->s_id);
        } else {
            char const* const label = get_chunk(chunk_edge_names, gwma->s_id);
            DEBUG_ERROR_IF(label == NULL)

            fprintf(output, "    reset -> %"PRIu32" [label=\"%s\"];\n", gwma->s_id, label);
        }
    } else if (gwma->s_type == GWMA_START_ELEMENT_TYPE_EDGE) {
        fprintf(output, "    reset -> %"PRIu32";\n", gwma->s_id);
    } else {
        char const* const label = get_chunk(chunk_vertex_names, gwma->s_id);
        DEBUG_ERROR_IF(label == NULL)

        StartVertexIterator svitr[1];
        construct_svitr_sg(svitr, graph);
        for (
            uint32_t s_id;
            graph->isValidVertex(gwma, (s_id = graph->nextVertexId_svitr(svitr)));
        ) fprintf(output, "    reset -> %"PRIu32" [label=\"%s\"];\n", s_id, label);
    }

    construct_vitr_sg(vitr, graph);
    if (!gwma->useLineGraph) {
        for (
            uint32_t v0_id;
            graph->isValidVertex(gwma, (v0_id = graph->nextVertexId_vitr(vitr)));
        ) {
            GWVertex const* const v0 = gwma->vertices + v0_id;
            DEBUG_ASSERT(isValid_gwvertex(v0))

            NeighborIterator nitr[1];
            construct_nitr_sg(nitr, graph, v0_id);
            for (
                uint32_t v1_id;
                graph->isValidVertex(gwma, (v1_id = graph->nextVertexId_nitr(nitr)));
            ) {
                GWVertex const* const v1 = gwma->vertices + v1_id;
                DEBUG_ASSERT(isValid_gwvertex(v1))

                for (uint32_t e_id = 0; e_id < gwma->size_edges; e_id++) {
                    GWEdge const* const e = gwma->edges + e_id;
                    DEBUG_ASSERT(isValid_gwedge(e))

                    GWVertex const* const v_a = gwma->vertices + e->source;
                    GWVertex const* const v_b = gwma->vertices + e->target;
                    DEBUG_ASSERT(isValid_gwvertex(v_a))
                    DEBUG_ASSERT(isValid_gwvertex(v_b))

                    if (areEqual_gwvertex(v0, v_a) && areEqual_gwvertex(v1, v_b)) {
                        char const* const label = get_chunk(chunk_edge_names, e_id);
                        DEBUG_ERROR_IF(label == NULL)

                        fprintf(output, "    %"PRIu32" -> %"PRIu32" [label=\"%s\"];\n", v0_id, v1_id, label);
                        break;
                    }
                }
            }
        }
    } else {
        for (
            uint32_t v0_id;
            graph->isValidVertex(gwma, (v0_id = graph->nextVertexId_vitr(vitr)));
        ) {
            GWEdge const* const edge = gwma->edges + v0_id;
            DEBUG_ASSERT(isValid_gwedge(edge))

            GWVertex const* const vertex = gwma->vertices + edge->target;
            DEBUG_ASSERT(isValid_gwvertex(vertex))

            char const* const label = get_chunk(chunk_vertex_names, vertex->original_v_id);
            DEBUG_ERROR_IF(label == NULL)

            NeighborIterator nitr[1];
            construct_nitr_sg(nitr, graph, v0_id);
            for (
                uint32_t v1_id;
                graph->isValidVertex(gwma, (v1_id = graph->nextVertexId_nitr(nitr)));
            ) fprintf(output, "    %"PRIu32" -> %"PRIu32" [label=\"%s\"];\n", v0_id, v1_id, label);
        }
    }

    fputs("}", output);
}

static void generateTestRequirements(
    VertexPathArray* const requirements, coverage_t const coverageCriterion,
    SimpleGraph* const graph, GWModelArray* const gwma, Chunk const* const requirementsChunk
) {
    DEBUG_ERROR_IF(requirements == NULL)
    DEBUG_ASSERT(IS_VALID_COVERAGE(coverageCriterion))
    DEBUG_ASSERT(isValid_sg(graph))
    DEBUG_ASSERT(isValid_gwma(gwma))

    switch (coverageCriterion) {
        case CUSTOM_COVERAGE:
            DEBUG_ASSERT(isValid_chunk(requirementsChunk))
            {
                Chunk const* const chunk_ids = gwma->useLineGraph
                    ? gwma->chunks + GWMA_CHUNK_EDGE_IDS
                    : gwma->chunks + GWMA_CHUNK_VERTEX_IDS;

                ChunkTable const* const ctbl_ids = gwma->useLineGraph
                    ? gwma->tables + GWMA_TBL_EDGE_IDS
                    : gwma->tables + GWMA_TBL_VERTEX_IDS;

                uint32_t i = 1;
                DEBUG_ASSERT(i < requirementsChunk->nStrings)

                char const* const countRequirements = get_chunk(requirementsChunk, i);
                DEBUG_ERROR_IF(countRequirements == NULL)

                uint32_t nRequirements;
                DEBUG_ASSERT(strspn(countRequirements, "0123456789") == strlen_chunk(requirementsChunk, i))
                sscanf(countRequirements, "%"PRIu32, &nRequirements);

                constructEmpty_vpa(requirements, nRequirements);
                REPEAT_CNTR (_dcntr1, nRequirements) {
                    i++;
                    DEBUG_ASSERT(i < requirementsChunk->nStrings)

                    char const* const requirementLength = get_chunk(requirementsChunk, i);
                    DEBUG_ERROR_IF(requirementLength == NULL)

                    uint32_t requirementLen;
                    DEBUG_ASSERT(strspn(requirementLength, "0123456789") == strlen_chunk(requirementsChunk, i))
                    sscanf(requirementLength, "%"PRIu32, &requirementLen);

                    DEBUG_ASSERT(requirements->size < requirements->cap)
                    VertexPath* const requirement = requirements->array + requirements->size++;
                    constructEmptyCapped_vpath(requirement, graph, requirementLen);
                    REPEAT_CNTR (_dcntr2, requirementLen) {
                        i++;
                        DEBUG_ASSERT(i < requirementsChunk->nStrings)

                        char const* const element_id = get_chunk(requirementsChunk, i);
                        DEBUG_ERROR_IF(element_id == NULL)

                        uint64_t const element_len = strlen_chunk(requirementsChunk, i);
                        DEBUG_ASSERT(element_len > 0)

                        ChunkTableEntry const* const entry = get_ctbl(ctbl_ids, chunk_ids, element_id, element_len);
                        DEBUG_ERROR_IF(entry == NULL)

                        extend_vpath(requirement, entry->value, 0);
                    }
                }
            }
            eliminateSubPaths_vpa(requirements);
            break;
        case VERTEX_COVERAGE:
        case EDGE_COVERAGE:
            constructVerticesAsPaths_vpa(requirements, graph);
            break;
        case PRIME1_COVERAGE:
            constructAllPrimePaths_vpa(requirements, graph);
            {
                VertexPathArray newRequirements[1];
                convertToEdgePaths(newRequirements, graph, gwma, requirements);
                free_vpa(requirements);
                memcpy(requirements, newRequirements, sizeof(VertexPathArray));
            }
            break;
        case PRIME2_COVERAGE:
            constructAllPrimePaths_vpa(requirements, graph);
            {
                VertexPathArray newRequirements[1];
                convertToEdgePathsAndIncludeRemainingEdges(newRequirements, graph, gwma, requirements);
                free_vpa(requirements);
                memcpy(requirements, newRequirements, sizeof(VertexPathArray));
            }
            break;
        case PRIME3_COVERAGE:
            constructAllPrimePaths_vpa(requirements, graph);
            break;
        case EPAIR_COVERAGE:
        default:
            constructAllUpToKPaths_vpa(requirements, graph, (uint32_t)coverageCriterion);
            eliminateSubPaths_vpa(requirements);
    }
}

static void saveHyperpaths(FILE* const output, SimpleGraph const* const hyperPathGraph) {
    DEBUG_ERROR_IF(output == NULL)
    DEBUG_ASSERT(isValid_sg(hyperPathGraph))
    DEBUG_ASSERT(isValid_hpg(hyperPathGraph->graphPtr))

    HyperPathGraph const* const hpgraph = (HyperPathGraph const*)hyperPathGraph->graphPtr;
    uint32_t const              nPaths  = hpgraph->pathGraph->countVertices(hpgraph->pathGraph->graphPtr);

    for (uint32_t h_id = nPaths; h_id < hpgraph->hpaths->size; h_id++) {
        VertexPath const* const hpath = hpgraph->hpaths->array + h_id;
        DEBUG_ASSERT(hpath->len > 0)

        fprintf(output, "h%"PRIu32":", h_id - nPaths);
        for (uint32_t i = 0; i < hpath->len; i++) {
            uint32_t const hp_id = hpath->array[i];
            if (hp_id < nPaths)
                fprintf(output, " p%"PRIu32"", hp_id);
            else
                fprintf(output, " h%"PRIu32"", hp_id - nPaths);
        }
        fputs("\n", output);
    }
}

static void saveTestRequirements(FILE* const requirementsFile, VertexPathArray const* const requirements, GWModelArray const* const gwma) {
    DEBUG_ERROR_IF(requirementsFile == NULL)
    DEBUG_ASSERT(isValid_vpa(requirements))
    DEBUG_ASSERT(isValid_gwma(gwma))

    Chunk const* const chunk_ids = gwma->useLineGraph
        ? gwma->chunks + GWMA_CHUNK_EDGE_IDS
        : gwma->chunks + GWMA_CHUNK_VERTEX_IDS;

    if (gwma->useLineGraph) {
        fputs("edgepaths\n", requirementsFile);
    } else {
        fputs("vertexpaths\n", requirementsFile);
    }

    fprintf(requirementsFile, "%"PRIu32"\n", requirements->size);
    for (uint32_t requirementId = 0; requirementId < requirements->size; requirementId++) {
        VertexPath const* const requirement = requirements->array + requirementId;
        DEBUG_ASSERT(isValid_vpath(requirement))
        DEBUG_ASSERT(requirement->len > 0)

        fprintf(requirementsFile, "%"PRIu32"\n", requirement->len);
        for (uint32_t i = 0; i < requirement->len; i++) {
            char const* const id_str = get_chunk(chunk_ids, requirement->array[i]);
            DEBUG_ERROR_IF(id_str == NULL)

            fprintf(requirementsFile, "%s\n", id_str);
        }
    }
}

static void showCopyright(void) {
    fputs(
        "\n"
        "Copyright (C) Anonymized for ICSE2025\n"
        "\n",
        stderr
    );
}

static void showErrorCannotOpenFile(char const* const filename) {
    DEBUG_ERROR_IF(filename == NULL)

    fprintf(
        stderr,
        "\n"
        "[ERROR] - Cannot open file '%s'\n"
        "\n",
        filename
    );
}

static void showErrorCoverageCriterionMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Coverage criterion missing (-c or --coverage without a criterion specifier)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorHyperPathsNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Hyperpaths file name is missing (-h or --hyperpaths without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorInputFileMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Input file missing (-i or --input without an input file)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorInvalidInputSyntax(char const* const filename) {
    DEBUG_ERROR_IF(filename == NULL)

    fprintf(
        stderr,
        "\n"
        "[ERROR] - Invalid Syntax @ %s\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        filename
    );
}

static void showErrorMustSpecifyInputFile(void) {
    fputs(
        "\n"
        "[ERROR] - Must specify an input file with -i or --input\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorNoInputFileGiven(void) {
    fputs(
        "\n"
        "[ERROR] - No input file given (no -i or --input option found)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorNotImplementedYet(char const* const functionality) {
    DEBUG_ERROR_IF(functionality == NULL)

    fprintf(
        stderr,
        "\n"
        "[ERROR] - %s is NOT implemented yet\n"
        "\n",
        functionality
    );
}

static void showErrorNotWellformed(void) {
    fputs(
        "\n"
        "[ERROR] - The model is NOT well-formed\n"
        "\n",
        stderr
    );
}

static void showErrorPathGraphNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Path graph file name is missing (-p or --pathgraph without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorRequirementsNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Requirements file name is missing (-r or --requirements without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorSimpleGraphNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Simple graph file name is missing (-s or --simplegraph without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorTestFilesMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Tests file(s) missing (-m or --measure without test file(s))\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorTestOutputFileNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Test output file name is missing (-t or --tests without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showErrorUnifiedModelNameMissing(void) {
    fputs(
        "\n"
        "[ERROR] - Unified model name is missing (-u or --unify without an output file name)\n"
        "\n"
        "gwplus --help for more instructions\n"
        "\n",
        stderr
    );
}

static void showIgnoringArgument(char const* const arg) {
    DEBUG_ERROR_IF(arg == NULL)
    fprintf(stderr, "[WARNING] - Ignoring argument => %s\n", arg);
}

static void showUsage(void) {
    fputs(
        "\n"
        "GWPlus: Fast Optimal Test Generator for GraphWalker\n"
        "\n"
        "Usage: gwplus <options>\n"
        "\n"
        "GENERAL OPTIONS:\n"
        "  -c,--coverage COVERAGE       Set the coverage criterion\n"
        "  -C,--copyright               Output the copyright message and exit\n"
        "  -H,--help                    Output this help message and exit\n"
        "  -h,--hyperpaths TXT-FILE     Output the hyperpaths to a TXT file\n"
        "  -i,--input JSON-FILE         (Mandatory) An input GraphWalker model in JSON format\n"
        "  -m,--measure CUSTOM-TEST(s)  Output coverage of custom test(s)\n"
        "  -p,--pathgraph DOT-FILE      Output the path graph to a DOT file\n"
        "  -r,--requirements TXT-FILE   Output the test requirements to a TXT file\n"
        "  -s,--simplegraph DOT-FILE    Output the simple graph to a DOT file\n"
        "  -t,--tests JSON-FILE         Output a unified GraphWalker model with predefinedEdgeIds\n"
        "  -u,--unify JSON-FILE         Output a unified GraphWalker model with no tests\n"
        "  -v,--verbose                 Timestamped status information to stdout\n"
        "  -V,--version                 Output version number and exit\n"
        "\n"
        "COVERAGE OPTIONS:\n"
        "  vertex                       All vertices of a GraphWalker model\n"
        "  edge                         (Default) All edges of a GraphWalker model\n"
        "  edgepair                     All edge-pairs of a GraphWalker model\n"
        "  NUMBER                       All edge paths up to a length (0=vertex, 1=edge, etc.)\n"
        "  prime1                       All prime vertex paths of a GraphWalker model\n"
        "  prime2                       All prime vertex paths and edges of a GraphWalker model\n"
        "  prime3                       All prime edge paths of a GraphWalker model\n"
        "  TXT-FILE                     Custom test requirements from a TXT file\n"
        "\n"
        "CUSTOM-TEST OPTIONS:\n"
        "  -b,--builtin                 Uses the predefinedEdgeIds of the input model\n"
        "  TXT-FILE(s)                  Reads custom test(s) from TXT file(s)\n"
        "\n"
        "EXAMPLE USES:\n"
        "  bin/gwplus -i exps/001/m.json -c prime3 -s sg.dot -p pg.dot -h hp.txt -t test.json -v\n"
        "  bin/gwplus -i exps/003/m.json -c 0 -t testpath.json -v\n"
        "  bin/gwplus -i exps/003/m.json -c edge -m exps/003/t1.txt exps/003/t2.txt\n"
        "  bin/gwplus -i exps/002/m.json -u unified.json -v\n"
        "\n",
        stderr
    );
}

static void showVersion(void) {
    fputs(
        "\n"
        "GWPlus v1.0 for ICSE2025\n"
        "\n",
        stderr
    );
}

#define VERBOSE_MSG(...) if (verbose) { printf("[%s] - ", get_timestamp()); printf(__VA_ARGS__); puts(""); }
int main(int argc, char* argv[]) {
    if (argc < 2) {
        showUsage();
        return EXIT_SUCCESS;
    }

    for (int i = argc - 1; i > 0; i--) {
        if (str_eq(argv[i], "-V") || str_eq(argv[i], "--version")) {
            showVersion();
            return EXIT_SUCCESS;
        }
    }

    for (int i = argc - 1; i > 0; i--) {
        if (str_eq(argv[i], "-C") || str_eq(argv[i], "--copyright")) {
            showCopyright();
            return EXIT_SUCCESS;
        }
    }

    for (int i = argc - 1; i > 0; i--) {
        if (str_eq(argv[i], "-H") || str_eq(argv[i], "--help")) {
            showUsage();
            return EXIT_SUCCESS;
        }
    }

    bool* const isArgProcessed = calloc((size_t)argc, sizeof(bool));
    DEBUG_ERROR_IF(isArgProcessed == NULL)

    bool verbose = 0;
    for (int i = argc - 1; i > 0; i--) {
        if (str_eq(argv[i], "-v") || str_eq(argv[i], "--verbose")) {
            verbose = 1;
            VERBOSE_MSG("Verbose enabled.")
            isArgProcessed[i] = 1;
            break;
        }
    }

    char const* inputFileName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-i") || str_eq(argv[i], "--input")) {
            if (i == argc - 1) {
                showErrorInputFileMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            inputFileName = argv[i + 1];
            if (inputFileName[0] == '-') {
                showErrorInputFileMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Input Model File = %s", inputFileName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }
    if (inputFileName == NULL) {
        showErrorNoInputFileGiven();
        free(isArgProcessed);
        return EXIT_FAILURE;
    }

    coverage_t  coverageCriterion   = EDGE_COVERAGE;
    char const* coverageString      = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-c") || str_eq(argv[i], "--coverage")) {
            if (i == argc - 1) {
                showErrorCoverageCriterionMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            coverageString = argv[i + 1];
            if (coverageString[0] == '-') {
                showErrorCoverageCriterionMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            } else if (str_eq(coverageString, "vertex") || str_eq(coverageString, "0")) {
                coverageCriterion = VERTEX_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Vertex Coverage")
            } else if (str_eq(coverageString, "edge") || str_eq(coverageString, "1")) {
                coverageCriterion = EDGE_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Edge Coverage")
            } else if (str_eq(coverageString, "edgepair") || str_eq(coverageString, "2")) {
                coverageCriterion = EPAIR_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Edge Pair Coverage")
            } else if (str_eq(coverageString, "prime1")) {
                coverageCriterion = PRIME1_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Prime Vertex Path Coverage")
            } else if (str_eq(coverageString, "prime2")) {
                coverageCriterion = PRIME2_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Prime Vertex Path + Edge Coverage")
            } else if (str_eq(coverageString, "prime3")) {
                coverageCriterion = PRIME3_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = Prime Edge Path Coverage")
            } else if (strspn(coverageString, "0123456789") == strlen(coverageString)) {
                sscanf(coverageString, "%d", &coverageCriterion);
                VERBOSE_MSG("Coverage Criterion = Paths of Length Up to %d", coverageCriterion)
            } else {
                coverageCriterion = CUSTOM_COVERAGE;
                VERBOSE_MSG("Coverage Criterion = From %s", coverageString)
            }
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    int firstTestFileId = -1;
    int lastTestFileId  = -1;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-m") || str_eq(argv[i], "--measure")) {
            VERBOSE_MSG("Will NOT generate tests, only measure coverage.")
            isArgProcessed[i] = 1;

            if (i == argc - 1) {
                showErrorTestFilesMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            firstTestFileId = i + 1;
            lastTestFileId  = firstTestFileId;
            while (
                lastTestFileId < argc && (
                    str_eq(argv[lastTestFileId], "-b")          ||
                    str_eq(argv[lastTestFileId], "--builtin")   ||
                    argv[lastTestFileId][0] != '-'
                )
            ) {
                if (argv[lastTestFileId][0] != '-') {
                    VERBOSE_MSG("Test File #%d = %s", lastTestFileId - firstTestFileId + 1, argv[lastTestFileId])
                } else {
                    VERBOSE_MSG("Test File #%d = builtin", lastTestFileId - firstTestFileId + 1)
                }
                isArgProcessed[lastTestFileId] = 1;
                lastTestFileId++;
            }

            if (lastTestFileId - firstTestFileId <= 0) {
                showErrorTestFilesMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }

            break;
        }
    }

    char const* unifiedModelName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-u") || str_eq(argv[i], "--unify")) {
            if (i == argc - 1) {
                showErrorUnifiedModelNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            unifiedModelName = argv[i + 1];
            if (unifiedModelName[0] == '-') {
                showErrorUnifiedModelNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Unified Model Name = %s", unifiedModelName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    char const* simpleGraphName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-s") || str_eq(argv[i], "--simplegraph")) {
            if (i == argc - 1) {
                showErrorSimpleGraphNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            simpleGraphName = argv[i + 1];
            if (simpleGraphName[0] == '-') {
                showErrorSimpleGraphNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Simple Graph Name = %s", simpleGraphName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    char const* requirementsName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-r") || str_eq(argv[i], "--requirements")) {
            if (i == argc - 1) {
                showErrorRequirementsNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            requirementsName = argv[i + 1];
            if (requirementsName[0] == '-') {
                showErrorRequirementsNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Requirements File = %s", requirementsName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    char const* pathGraphName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-p") || str_eq(argv[i], "--pathgraph")) {
            if (i == argc - 1) {
                showErrorPathGraphNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            pathGraphName = argv[i + 1];
            if (pathGraphName[0] == '-') {
                showErrorPathGraphNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Path Graph File = %s", pathGraphName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    char const* hyperPathsName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-h") || str_eq(argv[i], "--hyperpaths")) {
            if (i == argc - 1) {
                showErrorHyperPathsNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            hyperPathsName = argv[i + 1];
            if (hyperPathsName[0] == '-') {
                showErrorHyperPathsNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Hyperpaths File = %s", hyperPathsName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    char const* testOutputFileName = NULL;
    for (int i = argc - 1; i > 0; i--) {
        if (isArgProcessed[i]) continue;

        if (str_eq(argv[i], "-t") || str_eq(argv[i], "--tests")) {
            if (i == argc - 1) {
                showErrorTestOutputFileNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            testOutputFileName = argv[i + 1];
            if (testOutputFileName[0] == '-') {
                showErrorTestOutputFileNameMissing();
                free(isArgProcessed);
                return EXIT_FAILURE;
            }
            VERBOSE_MSG("Output Model File with Predefined Edges = %s", testOutputFileName)
            isArgProcessed[i]       = 1;
            isArgProcessed[i + 1]   = 1;
            break;
        }
    }

    for (int i = 1; i < argc; i++) {
        if (!isArgProcessed[i]) {
            showIgnoringArgument(argv[i]);
        }
    }
    free(isArgProcessed);

    bool    useLineGraph;
    Chunk   requirementsChunk[1] = {NOT_A_CHUNK};
    switch (coverageCriterion) {
        case CUSTOM_COVERAGE:
            {
                FILE* const customRequirements = fopen(coverageString, "r");
                if (customRequirements == NULL) {
                    showErrorCannotOpenFile(coverageString);
                    return EXIT_FAILURE;
                }

                DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(requirementsChunk, CHUNK_RECOMMENDED_PARAMETERS))
                DEBUG_ERROR_IF(fromStream_chunk(requirementsChunk, customRequirements, "\n") == 0xFFFFFFFF)
                NDEBUG_EXECUTE(fromStream_chunk(requirementsChunk, customRequirements, "\n"))

                char const* const line = get_chunk(requirementsChunk, 0);
                DEBUG_ERROR_IF(line == NULL)

                if (str_eq(line, "vertexpaths")) {
                    useLineGraph = 0;
                } else if (str_eq(line, "edgepaths")) {
                    useLineGraph = 1;
                } else {
                    showErrorInvalidInputSyntax(coverageString);
                    DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))
                    DEBUG_ASSERT(fclose(customRequirements) == 0)
                    NDEBUG_EXECUTE(fclose(customRequirements))
                    return EXIT_FAILURE;
                }

                DEBUG_ASSERT(fclose(customRequirements) == 0)
                NDEBUG_EXECUTE(fclose(customRequirements))
            }
            break;
        case VERTEX_COVERAGE:
        case PRIME1_COVERAGE:
        case PRIME2_COVERAGE:
            useLineGraph = 0;
            break;
        default:
            useLineGraph = 1;
    }

    if (inputFileName == NULL) {
        showErrorMustSpecifyInputFile();

        if (isValid_chunk(requirementsChunk))
            DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))

        return EXIT_FAILURE;
    }

    VERBOSE_MSG("Creating Empty GraphWalker Model...")
    GWModelArray gwma[1];
    constructEmpty_gwma(gwma, useLineGraph, GWMA_DEFAULT_PARAMETERS);

    FILE* const inputJsonFile = fopen(inputFileName, "r");
    if (inputJsonFile == NULL) {
        showErrorCannotOpenFile(inputFileName);

        if (isValid_chunk(requirementsChunk))
            DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))

        free_gwma(gwma);

        return EXIT_FAILURE;
    }

    VERBOSE_MSG("Filling the GraphWalker Model using '%s'", inputFileName)
    fillUsingJSON_gwma(gwma, inputJsonFile);

    VERBOSE_MSG("Filling adjacency lists to optimize path generation...")
    fillAdjLists_gwma(gwma);

    DEBUG_ASSERT(fclose(inputJsonFile) == 0)
    NDEBUG_EXECUTE(fclose(inputJsonFile))

    SimpleGraph graph[1];
    construct_sgi_gwma(graph, gwma);

    if (gwma->s_type == GWMA_START_ELEMENT_TYPE_EDGE) {
        VERBOSE_MSG("Starting Element is an EDGE")
    } else {
        VERBOSE_MSG("Starting Element is a VERTEX")
    }

    VERBOSE_MSG("# Vertices = %"PRIu32, gwma->size_vertices)
    VERBOSE_MSG("# Edges = %"PRIu32, gwma->size_edges)

    if (unifiedModelName != NULL) {
        VERBOSE_MSG("Saving the unified model to '%s'...", unifiedModelName)

        FILE* const unifiedModel = fopen(unifiedModelName, "w");
        if (unifiedModel == NULL) {
            showErrorCannotOpenFile(unifiedModelName);

            if (isValid_chunk(requirementsChunk))
                DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))

            free_gwma(gwma);

            return EXIT_FAILURE;
        }

        graph->dump(gwma, unifiedModel);

        DEBUG_ASSERT(fclose(unifiedModel) == 0)
        NDEBUG_EXECUTE(fclose(unifiedModel))
    }

    if (simpleGraphName != NULL) {
        VERBOSE_MSG("Saving the simple graph to '%s'...", simpleGraphName)

        FILE* const simpleGraph = fopen(simpleGraphName, "w");
        if (simpleGraph == NULL) {
            showErrorCannotOpenFile(simpleGraphName);

            if (isValid_chunk(requirementsChunk))
                DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))

            free_gwma(gwma);

            return EXIT_FAILURE;
        }

        generateDotOfSimpleGraph(simpleGraph, graph);

        DEBUG_ASSERT(fclose(simpleGraph) == 0)
        NDEBUG_EXECUTE(fclose(simpleGraph))
    }

    VertexPathArray requirements[1];

    VERBOSE_MSG("Generating/Loading Test Requirements...")
    generateTestRequirements(requirements, coverageCriterion, graph, gwma, requirementsChunk);

    if (requirementsName != NULL) {
        VERBOSE_MSG("Saving test requirements to '%s'", requirementsName)

        FILE* const requirementsFile = fopen(requirementsName, "w");
        if (requirementsFile == NULL) {
            showErrorCannotOpenFile(requirementsName);

            if (isValid_chunk(requirementsChunk))
                DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(requirementsChunk))

            free_gwma(gwma);

            return EXIT_FAILURE;
        }

        saveTestRequirements(requirementsFile, requirements, gwma);

        DEBUG_ASSERT(fclose(requirementsFile) == 0)
        NDEBUG_EXECUTE(fclose(requirementsFile))
    }

    if (isValid_chunk(requirementsChunk))
        free_chunk(requirementsChunk);

    VertexPathGraph vpgraph[1]      = {NOT_A_VPATH_GRAPH};
    SimpleGraph     pathGraph[1]    = {NOT_A_SG};
    if (hyperPathsName != NULL || pathGraphName != NULL || testOutputFileName != NULL) {
        VERBOSE_MSG("Generating Path Graph...")

        int optimizationLevel;
        switch (coverageCriterion) {
            case VERTEX_COVERAGE:
            case EDGE_COVERAGE:
                optimizationLevel = 2;
                break;
            case CUSTOM_COVERAGE:
            case PRIME1_COVERAGE:
            case PRIME2_COVERAGE:
            case PRIME3_COVERAGE:
                optimizationLevel = 0;
                break;
            case EPAIR_COVERAGE:
            default:
                optimizationLevel = 1;
        }
        VERBOSE_MSG("Optimization Level = %d", optimizationLevel)

        construct_vpg(vpgraph, graph, requirements, optimizationLevel);
        construct_sgi_vpg(pathGraph, vpgraph);

        if (pathGraphName != NULL) {
            VERBOSE_MSG("Saving path graph to '%s'", pathGraphName)

            FILE* const pathGraphFile = fopen(pathGraphName, "w");
            if (pathGraphFile == NULL) {
                showErrorCannotOpenFile(pathGraphName);

                free_vpg(vpgraph);
                free_vpa(requirements);
                free_gwma(gwma);

                return EXIT_FAILURE;
            }

            generateDotOfPathGraph(pathGraphFile, pathGraph, gwma);

            DEBUG_ASSERT(fclose(pathGraphFile) == 0)
            NDEBUG_EXECUTE(fclose(pathGraphFile))
        }
    }

    HyperPathGraph  hpgraph[1]          = {NOT_A_HPATH_GRAPH};
    SimpleGraph     hyperPathGraph[1]   = {NOT_A_SG};
    if (hyperPathsName != NULL || testOutputFileName != NULL) {
        VERBOSE_MSG("Generating Hyperpaths...")

        constructAcyclic_hpg(hpgraph, pathGraph);
        construct_sgi_hpg(hyperPathGraph, hpgraph);

        if (hyperPathsName != NULL) {
            VERBOSE_MSG("Saving hyperpaths to '%s'", hyperPathsName)

            FILE* const hyperPathsFile = fopen(hyperPathsName, "w");
            if (hyperPathsFile == NULL) {
                showErrorCannotOpenFile(hyperPathsName);

                free_hpg(hpgraph);
                free_vpg(vpgraph);
                free_vpa(requirements);
                free_gwma(gwma);

                return EXIT_FAILURE;
            }

            saveHyperpaths(hyperPathsFile, hyperPathGraph);

            DEBUG_ASSERT(fclose(hyperPathsFile) == 0)
            NDEBUG_EXECUTE(fclose(hyperPathsFile))
        }
    }

    if (testOutputFileName != NULL) {
        VERBOSE_MSG("Generating Test(s)...")

        uint32_t const nHyperpaths = hyperPathGraph->countVertices(hpgraph);
        VERBOSE_MSG("# Hyperpaths = %"PRIu32, nHyperpaths)

        if (nHyperpaths == 2) {
            VertexPathArray testPaths[1];
            constructTestPaths_hpg(testPaths, hpgraph);

            DEBUG_ASSERT(testPaths->size > 0)

            VertexPath const* const testPath = testPaths->array;
            DEBUG_ASSERT(isValid_vpath(testPath))

            VERBOSE_MSG("Test Length = %"PRIu32, testPath->len)

            setPredefinedPath_gwma(gwma, testPath->array, testPath->len);

            VERBOSE_MSG("Saving the test to '%s'...", testOutputFileName)

            FILE* const testFile = fopen(testOutputFileName, "w");
            if (testFile == NULL) {
                showErrorCannotOpenFile(testOutputFileName);

                free_vpa(testPaths);
                free_hpg(hpgraph);
                free_vpg(vpgraph);
                free_vpa(requirements);
                free_gwma(gwma);

                return EXIT_FAILURE;
            }

            graph->dump(gwma, testFile);

            DEBUG_ASSERT(fclose(testFile) == 0)
            NDEBUG_EXECUTE(fclose(testFile))
        } else {
            showErrorNotWellformed();
        }
    }

    if (isValid_hpg(hpgraph))
        free_hpg(hpgraph);

    if (isValid_vpg(vpgraph))
        free_vpg(vpgraph);

    if (lastTestFileId > firstTestFileId) {
        VERBOSE_MSG("Measuring Coverage...")

        showErrorNotImplementedYet("Coverage Measurement");
    }

    VERBOSE_MSG("Finished.")

    DEBUG_ASSERT(isValid_vpa(requirements))
    free_vpa(requirements);

    DEBUG_ASSERT(isValid_gwma(gwma))
    free_gwma(gwma);

    return EXIT_SUCCESS;
}
#undef VERBOSE_MSG
