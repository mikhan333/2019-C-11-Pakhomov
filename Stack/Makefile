TARGET = test_stack.o
SRCS = main.cpp src/Stack.cpp
OBJS = $(SRCS:.cpp=.o)

CC=g++
CFLAGS = -c -Wall
LDFLAGS = -lm

.DEFAULT_GOAL = start

.cpp.o:
	$(CC) $(CFLAGS)  -c $< -o $@
.PHONY: all clean

start: all
	./$(TARGET)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean: 
	rm -rf $(TARGET) $(OBJS)
	rm debug.log
