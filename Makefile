include padkit/compile.mk

INCLUDES=-Iinclude -Ipadkit/include
OBJECTS=obj/gwmodel.o obj/gwplus.o obj/hpathgraph.o obj/sgi.o obj/vpath.o obj/vpatharray.o obj/vpathgraph.o

all: bin/gwplus

.PHONY: all clean cleanobjects documentation objects

bin: ; mkdir bin

bin/gwplus:                             \
    bin                                 \
    padkit/compile.mk                   \
    padkit/lib/libpadkit.a              \
    ${OBJECTS}                          \
    ; ${COMPILE} ${OBJECTS} padkit/lib/libpadkit.a -o bin/gwplus

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov html latex

cleanobjects: ; rm -rf obj

documentation: ; doxygen

obj: ; mkdir obj

obj/gwmodel.o: obj                      \
    include/gwmodel.h                   \
    include/sgi.h                       \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/chunktable.h  \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/jsonparser.h  \
    padkit/include/padkit/reallocate.h  \
    src/gwmodel.c                       \
    ; ${COMPILE} ${INCLUDES} src/gwmodel.c -c -o obj/gwmodel.o

obj/gwplus.o: obj                       \
    include/coverage.h                  \
    include/gwmodel.h                   \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    include/hpathgraph.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/streq.h       \
    padkit/include/padkit/timestamp.h   \
    src/gwplus.c                        \
    ; ${COMPILE} ${INCLUDES} src/gwplus.c -c -o obj/gwplus.o

obj/hpathgraph.o: obj                   \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    include/hpathgraph.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/graphmatrix.h \
    src/hpathgraph.c                    \
    ; ${COMPILE} ${INCLUDES} src/hpathgraph.c -c -o obj/hpathgraph.o

obj/nflowgraph.o: obj                   \
    include/nflowgraph.h                \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    src/nflowgraph.c                    \
    ; ${COMPILE} ${INCLUDES} src/nflowgraph.c -c -o obj/nflowgraph.o

obj/sgi.o: obj                          \
    include/sgi.h                       \
    padkit/include/padkit/debug.h       \
    src/sgi.c                           \
    ; ${COMPILE} ${INCLUDES} src/sgi.c -c -o obj/sgi.o

obj/vpath.o: obj                        \
    include/sgi.h                       \
    include/vpath.h                     \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    padkit/include/padkit/streq.h       \
    src/vpath.c                         \
    ; ${COMPILE} ${INCLUDES} src/vpath.c -c -o obj/vpath.o

obj/vpatharray.o: obj                   \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/vpatharray.c                    \
    ; ${COMPILE} ${INCLUDES} src/vpatharray.c -c -o obj/vpatharray.o

obj/vpathgraph.o: obj                   \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    padkit/include/padkit/debug.h       \
    src/vpathgraph.c                    \
    ; ${COMPILE} ${INCLUDES} src/vpathgraph.c -c -o obj/vpathgraph.o

objects: ${OBJECTS}

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: padkit; make -C padkit lib/libpadkit.a
