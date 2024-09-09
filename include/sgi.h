#ifndef SGI_H
    #define SGI_H
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>

    #define NOT_A_NITR  ((NeighborIterator){ NULL, 0, 0 })
    #define NOT_A_SVITR ((StartVertexIterator){ NULL, 0 })
    #define NOT_A_VITR  ((VertexIterator){ NULL, 0 })

    #define NOT_AN_SG   ((SimpleGraph){ NULL,   \
        NULL, NULL, NULL, NULL, NULL, NULL,     \
        NULL, NULL, NULL, NULL, NULL, NULL,     \
        NULL, NULL, NULL, NULL, NULL, NULL      \
    })

    typedef struct NeighborIteratorBody {
        void const* graphPtr;
        uint32_t    vertexId;
        uint32_t    nextNeighborId;
    } NeighborIterator;

    typedef struct VertexIteratorBody {
        void const* graphPtr;
        uint32_t    nextVertexId;
    } VertexIterator, StartVertexIterator;

    typedef struct SimpleGraphInterface {
        void*       graphPtr;
        uint32_t    (*countEdges)           (void const* const graphPtr);
        uint32_t    (*countVertices)        (void const* const graphPtr);
        void        (*dump)                 (void const* const graphPtr, FILE* const output);
        void        (*dumpVertex)           (
            void const* const graphPtr,
            FILE* const output,
            uint32_t const vertexId
        );
        void        (*free)                 (void* const graphPtr);
        uint32_t    (*highestVertexId)      (void const* const graphPtr);
        bool        (*isValid)              (void const* const graphPtr);
        bool        (*isValid_nitr)         (NeighborIterator const itr[static const 1]);
        bool        (*isValid_svitr)        (StartVertexIterator const itr[static const 1]);
        bool        (*isValid_vitr)         (VertexIterator const itr[static const 1]);
        bool        (*isValidEdge)          (
            void const* const graphPtr,
            uint32_t const sourceVertexId,
            uint32_t const targetVertexId
        );
        bool        (*isValidVertex)        (void const* const graphPtr, uint32_t const vertexId);
        uint32_t    (*nextVertexId_nitr)    (NeighborIterator itr[static const 1]);
        uint32_t    (*nextVertexId_svitr)   (StartVertexIterator itr[static const 1]);
        uint32_t    (*nextVertexId_vitr)    (VertexIterator itr[static const 1]);
        void        (*setFirstNextId_nitr)  (NeighborIterator itr[static const 1]);
        void        (*setFirstNextId_svitr) (StartVertexIterator itr[static const 1]);
        void        (*setFirstNextId_vitr)  (VertexIterator itr[static const 1]);
    } SimpleGraph;

    void construct_nitr_sg(
        NeighborIterator itr[static const 1],
        SimpleGraph const graph[static const 1],
        uint32_t const sourceVertexId
    );

    void construct_svitr_sg(StartVertexIterator itr[static const 1], SimpleGraph const graph[static const 1]);

    void construct_vitr_sg(VertexIterator itr[static const 1], SimpleGraph const graph[static const 1]);

    void free_sg(SimpleGraph graph[static const 1]);

    bool isValid_sg(SimpleGraph const graph[static const 1]);
#endif
