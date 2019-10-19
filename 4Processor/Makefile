
SRCS_ASM := src/asm.cpp src/disasm.cpp
OBJS_ASM := ${SRCS_ASM:.cpp=.o} 
PROGS_ASM := ${SRCS_ASM:.cpp=}

SRCS_CPU :=	src/cpu.cpp ../3Stack/lib/Stack.cpp
OBJS_CPU := ${SRCS_CPU:.cpp=.o}
PROGS_CPU := src/cpu

BUILD := build/*

CC := g++
CFLAGS := -Wall
LDFLAGS := -lm

.DEFAULT_GOAL := start
.PHONY: all clean

start: all asm cpu
all: ${PROGS_ASM} ${PROGS_CPU}

cpu: ${PROGS_CPU}
	./${PROGS_CPU}
${PROGS_CPU}: ${OBJS_CPU}
	${CC} ${OBJS_CPU} -o ${PROGS_CPU} ${LDFLAGS}

asm: ${PROGS_ASM}
	./src/asm
disasm: ${PROGS_ASM}
	./src/disasm
# all: ${PROGS_ASM}
${PROGS_ASM} : % : %.o
	${CC} $< -o $@ ${LDFLAGS}

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${PROGS_ASM} ${PROGS_CPU} ${OBJS_ASM} ${OBJS_CPU} ${BUILD}
