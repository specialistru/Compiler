CC=gcc
CFLAGS=-Wall -Iinclude

SRCS=src/main.c src/lexer.c src/parser.c src/semantic.c src/codegen.c src/optimizer.c
OBJS=$(SRCS:.c=.o)
TARGET=abap_compiler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

