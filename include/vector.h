#ifndef VECTOR_H
    #define VECTOR_H
    #include <stdint.h>

    typedef struct VectorBody {
        uint32_t    start;
        uint32_t    end;
    } Vector;

    typedef struct VectorArrayBody {
        uint32_t    cap;
        uint32_t    size;
        Vector*     array;
    } VectorArray;
#endif
