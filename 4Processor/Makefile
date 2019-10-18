
SRCS := src/asm.cpp #\
	#src/disasm.cpp
OBJS := ${SRCS:.cpp=.o}
PROGS := ${SRCS:.cpp=}

CC := g++
CFLAGS := -Wall
LDFLAGS := -lm

.DEFAULT_GOAL := start
.PHONY: all clean

# start: all
# 	./build/$(TARGET)

asm: src/asm
	./src/asm

all: ${PROGS}

${PROGS} : % : %.o
	${CC} $< -o $@ ${LDFLAGS}

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${PROGS} ${OBJS}
