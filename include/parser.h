#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
    // контекст парсера
    token_t current_token;
} parser_t;

void parser_init(parser_t* parser, const char* source);
ast_node_t* parser_parse_program(parser_t* parser);

#endif // PARSER_H
