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
     * @def GW_GUESS_ID_STR_LEN
     *   In GraphWalker models, index strings are generally uuids.
     */
    #define GW_GUESS_ID_STR_LEN 37

    /**
     * @def GW_GUESS_NAME_LEN
     *   GraphWalker entities tend to have short names.
     */
    #define GW_GUESS_NAME_LEN   27

    /**
     * @def GWVERTEX_NOT_SHARED
     *   This shared_id value means that a GWVertex is not shared.
     */
    #define GWVERTEX_NOT_SHARED 0xFFFFFFFF

    /**
     * @def IS_GWVERTEX_SHARED
     *   Evaluates to nonzero if a GWVertex is shared.
     */
    #define IS_GWVERTEX_SHARED(v) (v->shared_id != 0xFFFFFFFF)

    /**
     * @def GWVERTEX_DEFAULT_X
     *   The default x coordinate for a GWVertex.
     */
    #define GWVERTEX_DEFAULT_X  0.0

    /**
     * @def GWVERTEX_DEFAULT_Y
     *    The default y coordinate for a GWVertex.
     */
    #define GWVERTEX_DEFAULT_Y  0.0

    /**
     * @def NOT_A_GWVERTEX
     *   A special GWVertex denoting a NOT-GWVertex. This GWVertex cannot pass the isValid_gwvertex() test.
     */
    #define NOT_A_GWVERTEX ((GWVertex){ 0xFFFFFFFF, 0xFFFFFFFF, 0.0, 0.0, 0, 0, NULL })

    /**
     * @struct GWVertex
     * @brief A GWVertex represents a vertex in a GraphWalker model.
     *
     * @var GWVertex::original_v_id
     *    The original vertex index.
     * @var GWVertex::shared_id
     *    The GWVertex index shared across a GWModelArray.
     * @var GWVertex::x
     *    The x position of the GWVertex in the GraphWalker environment.
     * @var GWVertex::y
     *    The y position of the GWVertex in the GraphWalker environment.
     * @var GWVertex::size_edges
     *    The total number of outgoing edges from the GWVertex.
     * @var GWVertex::size_edges
     *    The maximum number of outgoing edges the GWVertex can hold.
     * @var GWVertex::edges
     *    A pointer to the first element in an array of GWEdge indices.
     */
    typedef struct GWVertexBody {
        uint32_t    original_v_id;
        uint32_t    shared_id;
        double      x;
        double      y;
        uint32_t    size_edges;
        uint32_t    cap_edges;
        uint32_t*   edges;
    } GWVertex;

    /**
     * @brief Checks if two GWVertex objects represent the same vertex.
     * @param v1 A pointer to the first GWVertex.
     * @param v2 A pointer to the second GWVertex.
     */
    bool areEqual_gwvertex(GWVertex const* const v1, GWVertex const* const v2);

    /**
     * @brief Constructs a GWVertex with default parameters.
     * @param vertex A pointer to the GWVertex.
     * @param original_v_id The original vertex index.
     * @param initial_cap_edges Initial edge capacity.
     */
    void construct_gwvertex(GWVertex* const vertex, uint32_t const original_v_id, uint32_t const initial_cap_edges);

    /**
     * @brief Frees a GWVertex.
     * @param vertex A pointer to the GWVertex.
     */
    void free_gwvertex(GWVertex* const vertex);

    /**
     * @brief Checks if a GWVertex is valid.
     * @param vertex A pointer to the GWVertex.
     */
    bool isValid_gwvertex(GWVertex const* const vertex);

    /**
     * @def NOT_A_GWSHARED
     *   A special GWShared denoting a NOT-GWShared. This GWShared cannot pass the isValid_gwshared() test.
     */
    #define NOT_A_GWSHARED ((GWShared){ 0, 0, NULL })

    /**
     * @struct GWShared
     * @brief A GWShared represents a shared vertex in a GraphWalker model.
     *
     * @var GWShared::size_vertices
     *   The total number of vertices connected through this GWShared vertex.
     * @var GWShared::cap_vertices
     *   The maximum number of vertices the GWShared can hold.
     * @var GWShared::vertices
     *   A pointer to the first element in a sorted array of GWVertex indices.
     */
    typedef struct GWSharedBody {
        uint32_t    size_vertices;
        uint32_t    cap_vertices;
        uint32_t*   vertices;
    } GWShared;

    /**
     * @brief Shares a GWVertex through a GWShared.
     * @param shared_vertex A pointer to the GWShared.
     * @param v_id The vertex index.
     */
    void addVertex_gwshared(GWShared* const shared_vertex, uint32_t const v_id);

    /**
     * @brief Constructs an empty GWShared.
     * @param shared_vertex A pointer to the GWShared.
     * @param initial_cap The initial capacity of the GWShared.
     */
    void constructEmpty_gwshared(GWShared* const shared_vertex, uint32_t const initial_cap);

    /**
     * @brief Frees a GWShared.
     * @param shared_vertex A pointer to the GWShared.
     */
    void free_gwshared(GWShared* const shared_vertex);

    /**
     * @brief Checks if a GWShared is valid.
     * @param shared_vertex A pointer to the GWShared.
     */
    bool isValid_gwshared(GWShared const* const shared_vertex);

    /**
     * @def NOT_A_GWEDGE
     *   A special GWEdge denoting a NOT-GWEdge. This GWEdge cannot pass the isValid_gwedge() test.
     */
    #define NOT_A_GWEDGE (GWEdge){ 0xFFFFFFFF, 0xFFFFFFFF }

    /**
     * @struct GWEdge
     * @brief A directed connection between a source vertex and a target vertex.
     *
     * @var GWEdge::chunks
     *   These Chunks hold string information about a GWEdge.
     * @var GWEdge::source
     *   The vertex index of the source.
     * @var GWEdge::target
     *   The vertex index of the target.
     */
    #define GWEDGE_CHUNK_ACTIONS        0
    #define GWEDGE_CHUNK_REQUIREMENTS   1
    #define GWEDGE_CHUNK_LAST           GWEDGE_CHUNK_REQUIREMENTS
    typedef struct GWEdgeBody {
        Chunk chunks[GWEDGE_CHUNK_LAST];
        uint32_t source;
        uint32_t target;
    } GWEdge;

    void constructInvalid_gwedge(GWEdge* const edge);

    void free_gwedge(GWEdge* const edge);

    /**
     * @brief Checks if a GWEdge is valid.
     * @param edge A pointer to the GWEdge.
     */
    bool isValid_gwedge(GWEdge const* const edge);

    /**
     * @def NOT_A_GWMODEL
     *   A special GWModel denoting a NOT-GWModel. This GWModel cannot pass the isValid_gwmodel() test.
     */
    #define NOT_A_GWMODEL   ((GWModel){ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, NULL })

    /**
     * @struct GWModel
     * @brief A GraphWalker model.
     *
     * @var GWModel::first_v_id
     *   The Chunk index of the first vertex of the GWModel.
     * @var GWModel::first_e_id
     *   The Chunk index of the first edge of the GWModel.
     * @var GWModel::size_vertices
     *   The total number of vertices in the GWModel.
     * @var GWModel::size_edges
     *   The total number of edges in the GWModel.
     */
    typedef struct GWModelBody {
        uint32_t first_v_id;
        uint32_t first_e_id;
        uint32_t size_vertices;
        uint32_t size_edges;
    } GWModel;

    /**
     * @brief Checks if a GWModel is valid.
     * @param gwm A pointer to the GWModel.
     */
    bool isValid_gwm(GWModel const* const gwm);

    #define NOT_A_GWMODEL_ARRAY ((GWModelArray){                                            \
        { NOT_A_CHUNK, NOT_A_CHUNK, NOT_A_CHUNK, NOT_A_CHUNK, NOT_A_CHUNK, NOT_A_CHUNK },   \
        { NOT_A_CHUNK_TABLE },                                                              \
        0xFFFFFFFF,                                                                         \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                       \
        NULL, NULL, NULL, NULL                                                              \
    })

    #define GWMA_START_ELEMENT_VERTEX   0
    #define GWMA_START_ELEMENT_EDGE     1

    /**
     * @struct GWModelArray
     * @brief An array of GWModel objects. GraphWalker model files usually contain multiple models.
     *
     * @var GWModelArray::chunks
     *   These Chunk objects hold string information regarding the GWModelArray.
     * @var GWModelArray::tables
     *   These ChunkTable objects facilitate locating shared states in O(1).
     * @var GWModelArray::s_id
     *   The vertex index of the starting vertex.
     * @var GWModelArray::size_edges
     *   The total number of GWEdge objects residing in the GWModelArray.
     * @var GWModelArray::size_models
     *   The total number of GWModel objects residing in the GWModelArray.
     * @var GWModelArray::size_shared_vertices
     *   The total number of GWShared objects residing in the GWModelArray.
     * @var GWModelArray::size_vertices
     *   The total number of GWVertex objects residing in the GWModelArray.
     * @var GWModelArray::cap_edges
     *   The maximum number of GWEdge objects the GWModelArray can hold.
     * @var GWModelArray::cap_models
     *   The maximum number of GWModel objects the GWModelArray can hold.
     * @var GWModelArray::cap_shared_vertices
     *   The maximum number of GWShared objects the GWModelArray can hold.
     * @var GWModelArray::cap_vertices
     *   The maximum number of GWVertex objects the GWModelArray can hold.
     * @var GWModelArray::edges
     *   A pointer to the first GWEdge in the GWModelArray.
     * @var GWModelArray::models
     *   A pointer to the first GWModel in the GWModelArray.
     * @var GWModelArray::shared_vertices
     *   A pointer to the first GWShared in the GWModelArray.
     * @var GWModelArray::vertices
     *   A pointer to the first GWVertex in the GWModelArray.
     */
    #define GWMA_CHUNK_MODEL_IDS        0
    #define GWMA_CHUNK_MODEL_NAMES      1
    #define GWMA_CHUNK_MODEL_ACTIONS    2
    #define GWMA_CHUNK_VERTEX_IDS       3
    #define GWMA_CHUNK_VERTEX_NAMES     4
    #define GWMA_CHUNK_EDGE_IDS         5
    #define GWMA_CHUNK_EDGE_NAMES       6
    #define GWMA_CHUNK_EDGE_GUARD       7
    #define GWMA_CHUNK_SHARED_STATES    8
    #define GWMA_CHUNK_LAST             GWMA_CHUNK_SHARED_STATES
    #define GWMA_TBL_VERTEX_IDS         0
    #define GWMA_TBL_SHARED_STATES      1
    #define GWMA_TBL_LAST               GWMA_TBL_SHARED_STATES
    typedef struct GWModelArrayBody {
        Chunk       chunks[GWMA_CHUNK_LAST + 1];
        ChunkTable  tables[GWMA_TBL_LAST + 1];
        uint32_t    s_id;
        uint32_t    s_type;
        uint32_t    guess_edge_count_per_vertex;
        uint32_t    guess_vertex_count_per_shared;
        uint32_t    size_edges;
        uint32_t    size_models;
        uint32_t    size_shared_vertices;
        uint32_t    size_vertices;
        uint32_t    cap_edges;
        uint32_t    cap_models;
        uint32_t    cap_shared_vertices;
        uint32_t    cap_vertices;
        GWEdge*     edges;
        GWModel*    models;
        GWShared*   shared_vertices;
        GWVertex*   vertices;
    } GWModelArray;

    /**
     * @brief Adds a new GWEdge to a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param gwm A pointer to the GWModel.
     */
    void addEdge_gwma(GWModelArray* const gwma, GWModel* const gwm);

    /**
     * @brief Adds a new GWModel to a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    void addModel_gwma(GWModelArray* const gwma);

    /**
     * @brief Registers the last GWEdge to its source vertex's array of GWEdge indices.
     * @param gwma A pointer to the GWModelArray.
     */
    void addTransition_gwma(GWModelArray* const gwma);

    /**
     * @brief Adds a new GWVertex to the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    void addVertex_gwma(GWModelArray* const gwma);

    /**
     * @def GWMA_DEFAULT_CAP_EDGES
     *   This default capacity should work nicely in most situations.
     */
    #define GWMA_DEFAULT_CAP_EDGES              8192

    /**
     * @def GWMA_DEFAULT_CAP_MODELS
     *   This default capacity should work nicely in most situations.
     */
    #define GWMA_DEFAULT_CAP_MODELS             8

    /**
     * @def GWMA_DEFAULT_CAP_SHARED_VERTICES
     *   This default capacity should work nicely in most situations.
     */
    #define GWMA_DEFAULT_CAP_SHARED_VERTICES    16

    /**
     * @def GWMA_DEFAULT_CAP_VERTICES
     *   This default capacity should work nicely in most situations.
     */
    #define GWMA_DEFAULT_CAP_VERTICES           1024

    /**
     * @def GWMA_DEFAULT_PARAMETERS
     *   These default parameters should work nicely in most situations.
     */
    #define GWMA_DEFAULT_PARAMETERS         \
        GWMA_DEFAULT_CAP_EDGES,             \
        GWMA_DEFAULT_CAP_MODELS,            \
        GWMA_DEFAULT_CAP_SHARED_VERTICES,   \
        GWMA_DEFAULT_CAP_VERTICES,          \
        GW_GUESS_ID_STR_LEN,                \
        GW_GUESS_NAME_LEN

    /**
     * @brief Constructs an empty GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param initial_cap_edges The initial edge capacity.
     * @param initial_cap_models The initial model capacity.
     * @param initial_cap_shared_vertices The initial shared vertex capacity.
     * @param initial_cap_vertices The initial vertex capacity.
     * @param guess_id_str_len An estimation of index string length.
     * @param guess_name_len An estimation of name length.
     */
    void constructEmpty_gwma(
        GWModelArray* const gwma,
        uint32_t const initial_cap_edges, uint32_t const initial_cap_models,
        uint32_t const initial_cap_shared_vertices, uint32_t const initial_cap_vertices,
        size_t const guess_id_str_len, size_t const guess_name_len
    );

    /**
     * @brief Counts the total number of unique edges in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    uint32_t countUniqueEdges_gwma(GWModelArray const* const gwma);

    /**
     * @brief Counts the total number of unique vertices in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    uint32_t countUniqueVertices_gwma(GWModelArray const* const gwma);

    /**
     * @brief Fill a GWModelArray using a JSON file stream.
     * @param gwma A pointer to the GWModelArray.
     * @param jsonFile A file stream to read a GraphWalker JSON file.
     */
    void fillUsingJSON_gwma(GWModelArray* const gwma, FILE* const jsonFile);

    /**
     * @brief Finds the vertex index of a GWVertex given its index string.
     * @param gwma A pointer to the GWModelArray.
     * @param v_id_str A pointer to the first character of the vertex index string.
     * @param v_id_str_len The total number of characters in the vertex index string.
     */
    uint32_t findVertexId_gwma(GWModelArray const* const gwma, char const* const v_id_str, size_t const v_id_str_len);

    /**
     * @brief Finds the first registered incoming GWEdge towards a GWVertex.
     * @param gwma A pointer to the GWModelArray.
     * @param v_id The vertex id.
     */
    uint32_t firstEdgeTowards_gwma(GWModelArray const* const gwma, uint32_t const v_id);

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

    /**
     * @brief Gets a pointer to the last GWEdge in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    GWEdge* lastEdge_gwma(GWModelArray* const gwma);

    /**
     * @brief Gets a pointer to the last GWModel in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    GWModel* lastModel_gwma(GWModelArray* const gwma);

    /**
     * @brief Gets a pointer to the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     */
    GWVertex* lastVertex_gwma(GWModelArray* const gwma);

    /**
     * @brief Sets the index string of the last GWEdge in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param id_str A pointer to the first character of the index string.
     * @param id_str_len The total number of characters in the index string.
     */
    void setEdgeIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len);

    /**
     * @brief Sets the name of the last GWEdge in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param name A pointer to the first character of the name string.
     * @param name_len The total number of characters in the name.
     */
    void setEdgeName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len);

    /**
     * @brief Sets the source of the last GWEdge in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param v_id_str A pointer to the first character of the vertex index string.
     * @param v_id_str_len The total number of characters in the vertex index string.
     */
    void setEdgeSource_gwma(GWModelArray* const gwma, char const* const v_id_str, size_t const v_id_str_len);

    /**
     * @brief Sets the target of the last GWEdge in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param v_id_str A pointer to the first character of the vertex index string.
     * @param v_id_str_len The total number of characters in the vertex index string.
     */
    void setEdgeTarget_gwma(GWModelArray* const gwma, char const* const v_id_str, size_t const v_id_str_len);

    /**
     * @brief Sets the index string of the last GWModel in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param id_str A pointer to the first character of the index string.
     * @param id_str_len The total number of characters in the index string.
     */
    void setModelIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len);

    /**
     * @brief Sets the name of the last GWModel in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param name A pointer to the first character of the name string.
     * @param name_len The total number of characters in the name.
     */
    void setModelName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len);

    /**
     * @brief Sets the starting GWVertex or GWEdge of a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param s_id_str A pointer to the first character of the starting element's index string.
     * @param s_id_len The total number of characters in the starting element's index string.
     */
    void setStartingElement_gwma(GWModelArray* const gwma, char const* const s_id_str, size_t const s_id_len);

    /**
     * @brief Sets the index string of the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param id_str A pointer to the first character of the index string.
     * @param id_str_len The total number of characters in the index string.
     */
    void setVertexIdStr_gwma(GWModelArray* const gwma, char const* const id_str, size_t const id_str_len);

    /**
     * @brief Sets the name of the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param name A pointer to the first character of the name string.
     * @param name_len The total number of characters in the name.
     */
    void setVertexName_gwma(GWModelArray* const gwma, char const* const name, size_t const name_len);

    /**
     * @brief Sets the x coordinate of the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param x The x coordinate.
     */
    void setVertexX_gwma(GWModelArray* const gwma, double const x);

    /**
     * @brief Sets the y coordinate of the last GWVertex in a GWModelArray.
     * @param gwma A pointer to the GWModelArray.
     * @param y The y coordinate.
     */
    void setVertexY_gwma(GWModelArray* const gwma, double const y);

    /**
     * @brief Shares the last GWVertex of a GWModelArray under a shared name.
     * @param gwma A pointer to the GWModelArray.
     * @param shared_name A pointer to the first character of the shared_name string.
     * @param shared_name_len The total number of characters in the shared_name.
     */
    void shareVertex_gwma(GWModelArray* const gwma, char const* const shared_name, size_t const shared_name_len);

    /**
     * @brief Writes a GWModelArray into a JSON file.
     * @param gwma A pointer to the GWModelArray.
     * @param jsonFile A pointer to the JSON file.
     * @param ePath A pointer to the first GWEdge index in an array of GWEdge indices denoting a predefined path.
     * @param len The total number of edges in the predefined path.
     */
    void writeJSON_gwma(GWModelArray const* const gwma, FILE* const jsonFile, uint32_t const* const ePath, uint32_t const len);

    /**
     * @def NOT_A_CVITR
     *   A special ConstVertexIterator denoting a NOT-ConstVertexIterator that fails the isValid_cvitr() test.
     */
    #define NOT_A_CVITR ((ConstVertexIterator){ NULL, 0xFFFFFFFF, 0xFFFFFFFF } )

    /**
     * @def CVITR_STATE_NON_SHARED
     *   In this state, the ConstVertexIterator iterates only non-shared vertices.
     */
    #define CVITR_STATE_NON_SHARED  0

    /**
     * @def CVITR_STATE_SHARED
     *   In this state, the ConstVertexIterator iterates only shared vertices.
     */
    #define CVITR_STATE_SHARED      1

    /**
     * @def CVITR_STATE_STARTING
     *   In this state, the ConstVertexIterator iterates only the starting vertex.
     */
    #define CVITR_STATE_STARTING    2

    /**
     * @def CVITR_STATE_FINISHED
     *   In this state, the ConstVertexIterator stops iterating.
     */
    #define CVITR_STATE_FINISHED    3

    /**
     * @def CVITR_STATE_LAST
     *   The last state of a ConstVertexIterator
     */
    #define CVITR_STATE_LAST        CVITR_STATE_FINISHED

    /**
     * @struct ConstVertexIterator
     * @brief Iterates through the unique vertices of a GWModelArray.
     *
     * @var ConstVertexIterator::gwma
     *   A pointer to the GWModelArray vertices belong to.
     * @var ConstVertexIterator::nextVertexId
     *   The index of the next GWVertex.
     * @var ConstVertexIterator::state
     *   The state of the ConstVertexIterator.
     */
    typedef struct ConstVertexIteratorBody {
        GWModelArray const* gwma;
        uint32_t nextVertexId;
        uint32_t state;
    } ConstVertexIterator;

    /**
     * @brief Constructs a ConstVertexIterator under a GWModelArray.
     * @param itr A pointer to the ConstVertexIterator.
     * @param gwma A pointer to the GWModelArray.
     */
    void construct_cvitr(ConstVertexIterator* const itr, GWModelArray const* const gwma);

    /**
     * @brief Checks if a ConstVertexIterator is valid.
     * @param itr A pointer to the ConstVertexIterator.
     */
    bool isValid_cvitr(ConstVertexIterator const* const itr);

    /**
     * @brief Gets the next GWVertex index from a ConstVertexIterator.
     * @param itr A pointer to the ConstVertexIterator.
     */
    uint32_t nextVertex_cvitr(ConstVertexIterator* const itr);

    /**
     * @def NOT_A_CEITR
     *   A special ConstEdgeIterator denoting a NOT-ConstEdgeIterator that fails the isValid_ceitr() test.
     */
    #define NOT_A_CEITR ((ConstEdgeIterator){ NULL, 0xFFFFFFFF } )

    /**
     * @struct ConstEdgeIterator
     * @brief Iterates through the edges of a GWModelArray.
     *
     * @var ConstTransitionIterator::gwma
     *   A pointer to the GWModelArray vertices belong to.
     * @var ConstTransitionIterator::nextEdgeId
     *   The index of the next GWEdge.
     */
    typedef struct ConstEdgeIteratorBody {
        GWModelArray const* gwma;
        uint32_t nextEdgeId;
    } ConstEdgeIterator;

    /**
     * @brief Constructs a ConstEdgeIterator under a GWModelArray.
     * @param itr A pointer to the ConstEdgeIterator.
     * @param gwma A pointer to the GWModelArray.
     */
    void construct_ceitr(ConstEdgeIterator* const itr, GWModelArray const* const gwma);

    /**
     * @brief Checks if a ConstEdgeIterator is valid.
     * @param itr A pointer to the ConstEdgeIterator.
     */
    bool isValid_ceitr(ConstEdgeIterator const* const itr);

    /**
     * @brief Gets the next GWEdge index from a ConstEdgeIterator.
     * @param itr A pointer to the ConstEdgeIterator.
     */
    uint32_t nextEdge_ceitr(ConstEdgeIterator* const itr);

    /**
     * @def NOT_A_CTITR
     *   A special ConstTransitionIterator denoting a NOT-ConstTransitionIterator that fails the isValid_ctitr() test.
     */
    #define NOT_A_CTITR ((ConstTransitionIterator){ NULL, NULL, NULL, 0xFFFFFFFF, 0xFFFFFFFF } )

    /**
     * @struct ConstTransitionIterator
     * @brief Iterates through the outgoing edges of a GWVertex, including those belong to its shared vertices.
     *
     * @var ConstTransitionIterator::gwma
     *   A pointer to the GWModelArray vertices belong to.
     * @var ConstTransitionIterator::vertex
     *   A pointer to the GWVertex currently iterated.
     * @var ConstTransitionIterator::nextSource
     *   The index of the next shared GWVertex.
     * @var ConstTransitionIterator::nextEdgeId
     *   The index of the next GWEdge.
     */
    typedef struct ConstTransitionIteratorBody {
        GWModelArray const* gwma;
        GWVertex const*     vertex;
        uint32_t            nextSource;
        uint32_t            nextEdgeId;
    } ConstTransitionIterator;

    /**
     * @brief Constructs a ConstTransitionIterator under a GWModelArray and a source GWVertex.
     * @param itr A pointer to the ConstTransitionIterator.
     * @param gwma A pointer to the GWModelArray.
     * @param v_id The GWVertex index.
     */
    void construct_ctitr(ConstTransitionIterator* const itr, GWModelArray const* const gwma, uint32_t const v_id);

    /**
     * @brief Checks if a ConstTransitionIterator is valid.
     * @param itr A pointer to the ConstTransitionIterator.
     */
    bool isValid_ctitr(ConstTransitionIterator const* const itr);

    /**
     * @brief Gets the next GWEdge index from a ConstTransitionIterator.
     * @param itr A pointer to the ConstTransitionIterator.
     */
    uint32_t nextEdge_ctitr(ConstTransitionIterator* const itr);
#endif
