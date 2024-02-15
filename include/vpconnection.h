#ifndef VPCONNECTION_H
    #define VPCONNECTION_H
    #include "vpath.h"

    typedef struct VertexPathConnectionBody {
        uint32_t    connectionType;
        uint32_t    overlapStartPosition;
        VertexPath  connectingPath[1];
    } VertexPathConnection;
