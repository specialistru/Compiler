#ifndef PARSER_DATA_H
#define PARSER_DATA_H

#include "parser_context.h"
#include "ast.h"
#include "lexer.h"

// Парсинг инструкции DATA / CONSTANTS / TYPES / FIELD-SYMBOLS / PARAMETERS
ast_node_t* parse_data_declaration(parser_context_t* ctx);

#endif // PARSER_DATA_H
