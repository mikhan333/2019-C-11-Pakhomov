TARGET = hello
PREFIX = /usr/local/bin
SRCS = main.c hello.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean install uninstall

all: $(TARGET)
$(TARGET): $(OBJS)
            $(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
 
.c.o:
            $(CC) $(CFLAGS)  -c $< -o $@

clean:
            rm -rf $(TARGET) $(OBJS)
install:
            install $(TARGET) $(PREFIX)
uninstall:
            rm -rf $(PREFIX)/$(TARGET)