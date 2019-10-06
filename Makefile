
TARGET = hello
SRCS = main.c hello.c
OBJS = $(SRCS:.c=.o)

# .PHONY: all clean install uninstall

# all: $(TARGET)
# $(TARGET): $(OBJS)
#     $(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean: 
	rm -rf SortLongText/$(OBJS)
	# $(MAKE) -C SquareEquation
	# rm -rf $(TARGET) $(OBJS)
