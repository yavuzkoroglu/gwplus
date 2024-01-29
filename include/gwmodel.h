/**
 * @file gwmodel.h
 * @brief Defines GWEdge, GWModel, GWModelArray and related functions.
 *
 * A GWModel is a graph corresponding to a GraphWalker model. A GraphWalker
 * model usually has vertices with variable length string indices and names.
 * These vertices are connected via directed edges also with string indices
 * and names.
 *
 * @author Yavuz Koroglu
 */
#ifndef GWMODEL_H
    #define GWMODEL_H
    #include "padkit/chunktable.h"

    /**
     * @def NOT_A_GWEDGE
     *   A special GWEdge denoting a NOT-GWEdge. This GWEdge cannot pass the isValid_gwedge() test.
     */
    #define NOT_A_GWEDGE (GWEdge){ 0xFFFFFFFF, 0xFFFFFFFF }

    /**
     * @struct GWEdge
     * @brief A directed connection between a source vertex and a target vertex.
     *
     * @var GWEdge::source
     *   The vertex index of the source.
     * @var GWEdge::target
     *   The vertex index of the target.
     */
    typedef struct GWEdgeBody {
        uint32_t source;
        uint32_t target;
    } GWEdge;

    /**
     * @brief Checks if a GWEdge is valid.
     * @param edge A pointer to the GWEdge.
     */
    bool isValid_gwedge(GWEdge const* const edge);

    /**
     * @def GWM_CHUNK_INFO_MAX_STRINGS
     *   GWModel objects usually have six info strings.
     */
    #define GWM_CHUNK_INFO_MAX_STRINGS  6

    /**
     * @def GWM_INITIAL_STR_LEN
     *   We allocate 64 bytes for every string index, name, or information. It is unusual to have longer strings.
     */
    #define GWM_INITIAL_STR_LEN         64

    /**
     * @def GWM_RECOMMENDED_INITIAL_VERTEX_CAP
     *   Allocate this many vertices at construction. Consider increasing this when regularly working with large graphs.
     */
    #define GWM_RECOMMENDED_INITIAL_VERTEX_CAP  256

    /**
     * @def GWM_RECOMMENDED_INITIAL_EDGE_CAP
     *   Allocate this many edges at construction. Consider increasing this when regularly working with large graphs.
     */
    #define GWM_RECOMMENDED_INITIAL_EDGE_CAP    8192

    /**
     * @def GWM_RECOMMENDED_PARAMETERS
     *   These are the <default-parameters> for constructEmpty_gwm(gwm, <default-parameters>)
     */
    #define GWM_RECOMMENDED_PARAMETERS      \
        GWM_RECOMMENDED_INITIAL_VERTEX_CAP, \
        GWM_RECOMMENDED_INITIAL_EDGE_CAP

    /**
     * @struct GWModel
     * @brief A GraphWalker model.
     *
     * @var GWModel::chunks
     *   Memory chunks for strings related to vertices, edges, or general graph info.
     * @var GWModel::tables
     *   Hash-based look-up tables to quickly find vertex indices from vertex strings.o
     * @var GWModel::transitions
     *   transitions[vertex_id] is an array of vertices reachable from vertex_id in one hop.
     * @var GWModel::size_outEdges
     *   size_outEdges[vertex_id] is the total number of outgoing edges of a vertex_id.
     * @var GWModel::cap_outEdges
     *   size_outEdges[vertex_id] is the capacity of outgoing edges of a vertex_id.
     * @var GWModel::size_vertices
     *   The total number of vertices in the GWModel.
     * @var GWModel::cap_vertices
     *   The maximum number of vertices the GWModel can hold.
     * @var GWModel::edges
     *   An array of all edges in the GWModel.
     * @var GWModel::size_edges
     *   The total number of edges in the GWModel.
     * @var GWModel::cap_edges
     *   The maximum number of edges the GWModel can hold.
     */
    #define GWM_CHUNK_INFO          0
    #define GWM_CHUNK_VERTEX_IDS    1
    #define GWM_CHUNK_VERTEX_NAMES  2
    #define GWM_CHUNK_EDGE_IDS      3
    #define GWM_CHUNK_EDGE_NAMES    4
    #define GWM_CHUNK_LAST          GWM_CHUNK_EDGE_NAMES
    #define GWM_TBL_VERTICES        0
    #define GWM_TBL_LAST            GWM_TBL_VERTICES
    #define GWM_ID_S                0
    #define GWM_ID_T                1
    #define GWM_NAME_S              "s"
    #define GWM_NAME_T              "t"
    #define GWM_NAME_S_LEN          1
    #define GWM_NAME_T_LEN          1
    typedef struct GWModelBody {
        Chunk chunks[GWM_CHUNK_LAST + 1];
        ChunkTable tables[GWM_TBL_LAST + 1];
        uint32_t** transitions;
        uint32_t* size_outEdges;
        uint32_t* cap_outEdges;
        uint32_t size_vertices;
        uint32_t cap_vertices;
        GWEdge* edges;
        uint32_t size_edges;
        uint32_t cap_edges;
    } GWModel;

    /**
     * @brief Adds a new GWEdge with unknown source and target to a GWModel.
     * @param gwm A pointer to the GWModel.
     * @param id_str GraphWalker index string.
     * @param id_str_len Length of the GraphWalker index string.
     * @param name GraphWalker name string.
     * @param name_len Length of the GraphWalker name string.
     */
    void addEdge_gwm(
        GWModel* const gwm,
        char const* const id_str, size_t const id_str_len,
        char const* const name, size_t const name_len
    );

    /**
     * @brief Adds a new transition with known source and target to a GWModel.
     * @param gwm A pointer to the GWModel.
     * @param source The vertex index of the source.
     * @param sink The vertex index of the target.
     */
    void addTransition_gwm(GWModel* const gwm, uint32_t const source, uint32_t const sink);

    /**
     * @brief Adds a new vertex with empty name and string index to a GWModel.
     * @param gwm A pointer to the GWModel.
     * @param id_str GraphWalker index string.
     * @param id_str_len Length of the GraphWalker index string.
     * @param name GraphWalker name string.
     * @param name_len Length of the GraphWalker name string.
     */
    void addVertex_gwm(
        GWModel* const gwm,
        char const* const id_str, size_t const id_str_len,
        char const* const name, size_t const name_len
    );

    /**
     * @brief Constructs an empty GWModel.
     * @param initial_cap_vertices Initial capacity of vertices.
     * @param initial_cap_edges Initial capacity of edges.
     */
    void constructEmpty_gwm(
        GWModel* const gwm,
        uint32_t const initial_cap_vertices,
        uint32_t const initial_cap_edges
    );

    /**
     * @brief Frees a GWModel.
     * @param gwm A pointer to the GWModel.
     */
    void free_gwm(GWModel* const gwm);

    /**
     * @brief Gets the GraphWalker index string of a GWModel.
     * @param gwm A pointer to the GWModel.
     */
    char const* getModelId_gwm(GWModel const* const gwm);

    /**
     * @brief Gets the name string of a GWModel.
     * @param gwm A pointer to the GWModel.
     */
    char const* getModelName_gwm(GWModel const* const gwm);

    /**
     * @brief Checks if a GWModel is valid.
     * @param gwm A pointer to the GWModel.
     */
    bool isValid_gwm(GWModel const* const gwm);

    /**
     * @brief Returns the number of vertices in a GWModel.
     * @param gwm A pointer to the GWModel.
     */
    uint32_t vertexCount_gwm(GWModel const* const gwm);

    /**
     * @def GWM_ARRAY_RECOMMENDED_INITIAL_CAP
     *   This initial cap should work nicely in most situations.
     */
    #define GWM_ARRAY_RECOMMENDED_INITIAL_CAP   8

    /**
     * @struct GWModelArray
     * @brief An array of GWModel objects. GraphWalker model files usually contain multiple models.
     *
     * @var GWModelArray::cap
     *   The maximum number of GWModel objects the GWModelArray can hold.
     * @var GWModelArray::size
     *   The total number of GWModel onjects residing in the GWModelArray.
     * @var GWModelArray::array
     *   A pointer to the first GWModel in the GWModelArray.
     */
    typedef struct GWModelArrayBody {
        size_t cap;
        size_t size;
        GWModel* array;
    } GWModelArray;

    /**
     * @brief Constructs a GWModelArray from a JSON file stream.
     * @param gwma A pointer to the GWModelArray.
     * @param initial_cap Initial capacity of the GWModelArray.
     * @param jsonFile A file stream to read a GraphWalker JSON file.
     */
    void constructFromJSON_gwma(GWModelArray* const gwma, size_t const initial_cap, FILE* const jsonFile);

    /**
     * @brief Frees a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    void free_gwma(GWModelArray* const gwma);

    /**
     * @brief Checks if a GWModelArray is valid.
     * @param gwma A pointer to the GWModelArray.
     */
    bool isValid_gwma(GWModelArray const* const gwma);
#endif
