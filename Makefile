CC = gcc
CFLAGS = -Wall -Wextra -O2

INCLUDES = -Iinclude

SRC = src/constants.c src/parameters.c src/error_handling.c src/perform.c
OBJ = $(SRC:.c=.o)

TESTS = tests/test_parameters tests/test_perform
EXAMPLES = examples/order_processing

all: $(TESTS) $(EXAMPLES)

tests/test_parameters: tests/test_parameters.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	
tests/test_perform: tests/test_perform.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

examples/order_processing: examples/order_processing.c $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(OBJ) $(TESTS) $(EXAMPLES)

.PHONY: all clean
