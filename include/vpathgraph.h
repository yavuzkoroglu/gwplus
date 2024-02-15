#ifndef VPATHGRAPH_H
    #define VPATHGRAPH_H
    #include "vpatharray.h"

    typedef struct VertexPathGraphBody {
        VertexPathArray const*  vpaths;
        VertexPath**            splices;
    } VertexPathGraph;

    void construct_vpg(VertexPathGraph* const vpgraph, VertexPathArray const* const vpaths);

    void dump_vpg(VertexPathGraph* const vpgraph, FILE* const output);

    void free_vpg(VertexPathGraph* const vpgraph);

    bool isValid_vpg(VertexPathGraph const* const vpgraph);
#endif
