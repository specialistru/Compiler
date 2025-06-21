#ifndef PARSER_IF_H
#define PARSER_IF_H

#include "ast.h"
#include "lexer.h"

// Главная функция для парсинга конструкции IF
ast_node_t* parse_if(token_stream_t *tokens);

#endif // PARSER_IF_H
