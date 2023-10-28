include padkit/compile.mk

all: bin/ppwalker

.PHONY: all clean

bin: ; mkdir bin

bin/ppwalker:               \
    bin                     \
    padkit/compile.mk       \
    padkit/lib/libpadkit.a  \
    padkit/include/padkit.h \
    src/ppwalker.c          \
    ; ${COMPILE} -Ipadkit/include padkit/lib/libpadkit.a src/ppwalker.c -o bin/ppwalker

clean: ; rm -rf bin padkit

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: padkit; make -C padkit lib/libpadkit.a
