
TARGET = hello
SRCS = main.c
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean: 
	rm -rf SortLongText/$(OBJS)
	$(MAKE) -C Stack $@
	# rm -rf $(TARGET) $(OBJS)
