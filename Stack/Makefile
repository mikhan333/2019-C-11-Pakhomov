TARGET = test_stack.o
SRCS = main.c src/Stack.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -lm

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

.PHONY: all clean

start: all
	./$(TARGET)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clean: 
	rm -rf $(TARGET) $(OBJS)
