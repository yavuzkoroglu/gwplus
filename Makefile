include padkit/compile.mk

INCLUDES=-Iinclude -Ipadkit/include
OBJECTS=obj/gwmodel.o obj/gwplus.o

all: bin/gwplus

.PHONY: all clean objects

bin: ; mkdir bin

bin/gwplus:                             \
    bin                                 \
    padkit/compile.mk                   \
    padkit/lib/libpadkit.a              \
    ${OBJECTS}                          \
    ; ${COMPILE} padkit/lib/libpadkit.a ${OBJECTS} -o bin/gwplus

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov

obj: ; mkdir obj

obj/gwmodel.o: obj                      \
    include/gwmodel.h                   \
    padkit/include/padkit/chunk.h       \
    padkit/include/padkit/chunktable.h  \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/jsonparser.h  \
    padkit/include/padkit/reallocate.h  \
    src/gwmodel.c                       \
    ; ${COMPILE} ${INCLUDES} src/gwmodel.c -c -o obj/gwmodel.o

obj/gwplus.o: obj                       \
    include/gwmodel.h                   \
    include/path.h                      \
    padkit/include/padkit/debug.h       \
    src/gwplus.c                        \
    ; ${COMPILE} ${INCLUDES} src/gwplus.c -c -o obj/gwplus.o

obj/path.o: obj                         \
    include/gwmodel.h                   \
    include/path.h                      \
    padkit/include/padkit/debug.h       \
    padkit/include/padkit/reallocate.h  \
    src/path.c                          \
    ; ${COMPILE} ${INCLUDES} src/path.c -c -o obj/path.o

objects: ${OBJECTS}

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: padkit; make -C padkit lib/libpadkit.a
