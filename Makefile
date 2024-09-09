include padkit/compile.mk

INC_DIR=-Iinclude -Ipadkit/include
OBJECTS=obj/eflowgraph.o    \
        obj/gwmodel.o       \
        obj/gwplus.o        \
        obj/hpathgraph.o    \
        obj/nflowgraph.o    \
        obj/sgi.o           \
        obj/vpath.o         \
        obj/vpatharray.o    \
        obj/vpathgraph.o

SILENCE=-Wno-padded

all: bin/gwplus bin/rq2

.FORCE:

.PHONY: .FORCE all clean

bin: ; mkdir bin

bin/gwplus: .FORCE                      \
    bin                                 \
    ${OBJECTS}                          \
    padkit/lib/libpadkit.a              \
    ; ${COMPILE} ${OBJECTS} padkit/lib/libpadkit.a -o bin/gwplus

bin/rq2: .FORCE src/rq2.c; ${COMPILE} src/rq2.c -o bin/rq2

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov html latex

obj: ; mkdir obj

obj/eflowgraph.o: .FORCE                \
    obj                                 \
    include/eflowgraph.h                \
    include/hpathgraph.h                \
    include/nflowgraph.h                \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/graphmatrix.h	\
    padkit/include/padkit/reallocate.h  \
    src/eflowgraph.c                    \
    ; ${COMPILE} ${INC_DIR} src/eflowgraph.c -c -o obj/eflowgraph.o

obj/gwmodel.o: .FORCE                   \
    obj                                 \
    include/gwmodel.h                   \
    include/sgi.h                       \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/chunktable.h  \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/jsonparser.h  \
    padkit/include/padkit/reallocate.h  \
    src/gwmodel.c                       \
    ; ${COMPILE} ${INC_DIR} src/gwmodel.c -c -o obj/gwmodel.o

obj/gwplus.o: .FORCE                    \
    obj                                 \
    include/coverage.h                  \
    include/gwmodel.h                   \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    include/hpathgraph.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/graphmatrix.h \
    padkit/include/padkit/repeat.h      \
    padkit/include/padkit/streq.h       \
    padkit/include/padkit/timestamp.h   \
    src/gwplus.c                        \
    ; ${COMPILE} ${INC_DIR} src/gwplus.c -c -o obj/gwplus.o

obj/hpathgraph.o: .FORCE                \
    obj                                 \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    include/hpathgraph.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/graphmatrix.h \
    src/hpathgraph.c                    \
    ; ${COMPILE} ${INC_DIR} src/hpathgraph.c -c -o obj/hpathgraph.o

obj/nflowgraph.o: .FORCE                \
    obj                                 \
    include/nflowgraph.h                \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    src/nflowgraph.c                    \
    ; ${COMPILE} ${INC_DIR} src/nflowgraph.c -c -o obj/nflowgraph.o

obj/sgi.o: .FORCE                       \
    obj                                 \
    include/sgi.h                       \
    src/sgi.c                           \
    ; ${COMPILE} ${SILENCE} ${INC_DIR} src/sgi.c -c -o obj/sgi.o

obj/vpath.o: .FORCE                     \
    obj                                 \
    include/sgi.h                       \
    include/vpath.h                     \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    padkit/include/padkit/streq.h       \
    src/vpath.c                         \
    ; ${COMPILE} ${INC_DIR} src/vpath.c -c -o obj/vpath.o

obj/vpatharray.o: .FORCE                \
    obj                                 \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/vpatharray.c                    \
    ; ${COMPILE} ${INC_DIR} src/vpatharray.c -c -o obj/vpatharray.o

obj/vpathgraph.o: .FORCE                \
    obj                                 \
    include/sgi.h                       \
    include/vpath.h                     \
    include/vpatharray.h                \
    include/vpathgraph.h                \
    padkit/include/padkit/debug.h       \
    src/vpathgraph.c                    \
    ; ${COMPILE} ${INC_DIR} src/vpathgraph.c -c -o obj/vpathgraph.o

padkit/include/padkit.h: .FORCE; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: .FORCE; make -C padkit lib/libpadkit.a
