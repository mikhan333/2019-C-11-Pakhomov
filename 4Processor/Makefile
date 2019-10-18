#TARGET = Processor

#LIB = ../3Stack/lib
SRCS = src/asm.cpp #$(LIB)/Stack.cpp
OBJS = $(SRCS:.cpp=.o)
#DEBUG_FILES = debug/*

CC=g++
CFLAGS = -c -Wall
LDFLAGS = -lm

.DEFAULT_GOAL = start

.cpp.o:
	$(CC) $(CFLAGS)  -c $< -o $@
.PHONY: all clean

start: all
	./build/$(TARGET)

# all: $(TARGET)
# $(TARGET): $(OBJS)
# 	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
# 	mv src/asm.o build/asm.o

asm:
	$(CC) $(CFLAGS)  -c $< -o $@
	$(CC) -o asm asm.o $(LDFLAGS)

clean: 
	rm -rf build/* $(DEBUG_FILES)
