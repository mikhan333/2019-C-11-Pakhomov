# StackTests or Processor
TARGET = StackTests

SRCS = src/$(TARGET).cpp lib/Stack.cpp
OBJS = $(SRCS:.cpp=.o)
DEBUG_FILES = *.log debug/*.log

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
	rm -rf $(TARGET) $(OBJS) $(DEBUG_FILES)
