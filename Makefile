CC = gcc
CFLAGS = -Wall -Wextra -O2

INCLUDES = -Iinclude

SRC = src/constants.c src/parameters.c src/error_handling.c src/perform.c src/lexer.c src/parser.c src/ast.c src/semantic.c src/ir.c src/ir_generator.c src/optimizer.c src/interpreter.c

OBJ = $(SRC:.c=.o)

TESTS = tests/test_parameters tests/test_perform tests/test_full
EXAMPLES = examples/simple_abap_example

all: $(TESTS) $(EXAMPLES)

tests/test_parameters: tests/test_parameters.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

tests/test_perform: tests/test_perform.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

tests/test_full: tests/test_full.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

examples/simple_abap_example: examples/simple_abap_example.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(OBJ) $(TESTS) $(EXAMPLES)

.PHONY: all clean
