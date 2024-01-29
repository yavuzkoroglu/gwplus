include padkit/compile.mk

INCLUDES=-Iinclude -Ipadkit/include
OBJECTS=obj/algorithm.o obj/gwmodel.o obj/gwplus.o obj/hyperpath.o obj/path.o

.PHONY: all clean documentation objects

all: bin/gwplus

bin: ; mkdir bin

bin/gwplus:                             \
    bin                                 \
    padkit/compile.mk                   \
    padkit/lib/libpadkit.a              \
    ${OBJECTS}                          \
    ; ${COMPILE} padkit/lib/libpadkit.a ${OBJECTS} -o bin/gwplus

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov html latex

documentation: ; doxygen

obj: ; mkdir obj

obj/algorithm.o: obj                    \
    include/hyperpath.h                 \
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

obj/hyperpath.o: obj                    \
    include/coverage.h                  \
    include/hyperpath.h                 \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/hyperpath.c                     \
    ; ${COMPILE} ${INCLUDES} src/hyperpath.c -c -o obj/hyperpath.o

obj/path.o: obj                         \
    include/path.h                      \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/path.c                          \
    ; ${COMPILE} ${INCLUDES} src/path.c -c -o obj/path.o

objects: ${OBJECTS}

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: padkit; make -C padkit lib/libpadkit.a
