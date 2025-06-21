#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    int success;
    int pos;
} ParseResult;

ParseResult parse_class(Token* tokens);

#endif

