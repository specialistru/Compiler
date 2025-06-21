#ifndef PARSER_IF_H
#define PARSER_IF_H

#include "parser_context.h"
#include "ast.h"
#include "lexer.h"

// Парсинг конструкции IF ... ELSEIF ... ELSE ... ENDIF
ast_node_t* parse_if_statement(parser_context_t* ctx);

#endif // PARSER_IF_H
