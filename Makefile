include padkit/compile.mk

INCLUDES=-Iinclude -Ipadkit/include
OBJECTS=obj/algorithm.o obj/gwmodel.o obj/gwplus.o obj/path.o obj/testrequirements.o
TOYOBJS=obj/tgi.o obj/toygraph.o obj/vpath.o obj/vpatharray.o

all: bin/gwplus bin/toygraph

.PHONY: all clean cleanobjects documentation objects

bin: ; mkdir bin

bin/gwplus:                             \
    bin                                 \
    padkit/compile.mk                   \
    padkit/lib/libpadkit.a              \
    ${OBJECTS}                          \
    ; ${COMPILE} padkit/lib/libpadkit.a ${OBJECTS} -o bin/gwplus

bin/toygraph:                           \
    bin                                 \
    padkit/compile.mk                   \
    padkit/lib/libpadkit.a              \
    ${TOYOBJS}                          \
    ; ${COMPILE} padkit/lib/libpadkit.a ${TOYOBJS} -o bin/toygraph

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov html latex

cleanobjects: ; rm -rf obj

documentation: ; doxygen

obj: ; mkdir obj

obj/algorithm.o: obj                    \
    include/testrequirements.h          \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/algorithm.c                     \
    ; ${COMPILE} ${INCLUDES} src/algorithm.c -c -o obj/algorithm.o

obj/gwmodel.o: obj                      \
    include/gwmodel.h                   \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/chunktable.h  \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/jsonparser.h  \
    padkit/include/padkit/reallocate.h  \
    padkit/include/padkit/repeat.h      \
    src/gwmodel.c                       \
    ; ${COMPILE} ${INCLUDES} src/gwmodel.c -c -o obj/gwmodel.o

obj/gwplus.o: obj                       \
    include/algorithm.h                 \
    include/coverage.h                  \
    include/hyperpath.h                 \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/streq.h       \
    src/gwplus.c                        \
    ; ${COMPILE} ${INCLUDES} src/gwplus.c -c -o obj/gwplus.o

obj/path.o: obj                         \
    include/path.h                      \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/path.c                          \
    ; ${COMPILE} ${INCLUDES} src/path.c -c -o obj/path.o

obj/testrequirements.o: obj             \
    include/coverage.h                  \
    include/gwmodel.h                   \
    include/hyperpath.h                 \
    include/path.h                      \
    include/testrequirements.h          \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/testrequirements.c              \
    ; ${COMPILE} ${INCLUDES} src/testrequirements.c -c -o obj/testrequirements.o

obj/tgi.o: obj                          \
    include/tgi.h                       \
    padkit/include/padkit/debug.h       \
    src/tgi.c                           \
    ; ${COMPILE} ${INCLUDES} src/tgi.c -c -o obj/tgi.o

obj/toygraph.o: obj                     \
    include/tgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    src/toygraph.c                      \
    ; ${COMPILE} ${INCLUDES} src/toygraph.c -c -o obj/toygraph.o

obj/vpath.o: obj                        \
    include/tgi.h                       \
    include/vpath.h                     \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    padkit/include/padkit/streq.h       \
    src/vpath.c                         \
    ; ${COMPILE} ${INCLUDES} src/vpath.c -c -o obj/vpath.o

obj/vpatharray.o: obj                   \
    include/tgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/vpatharray.c                    \
    ; ${COMPILE} ${INCLUDES} src/vpatharray.c -c -o obj/vpatharray.o

objects: ${OBJECTS}

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: padkit; make -C padkit lib/libpadkit.a
