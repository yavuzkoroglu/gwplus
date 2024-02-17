#ifndef NFLOWGRAPH_H
    #define NFLOWGRAPH_H
    #include "sgi.h"

    typedef struct NetworkFlowEdgeBody {
        uint32_t capacity;
        uint32_t flow;
        uint32_t lowerBound;
        uint32_t residualCapacity;
    } NetworkFlowTransition;

    typedef struct NetworkFlowGraphBody {
        SimpleGraph const*      acyclicGraph;
        NetworkFlowTransition** forwardTransitionMtx;
        NetworkFlowTransition** backwardTransitionMtx;
    } NetworkFlowGraph;
#endif
