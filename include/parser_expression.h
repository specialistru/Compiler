#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

#include "parser_common.h"

// Основная функция разбора выражений
ast_node_t* parse_expression(parser_context_t* ctx);

// Прототипы функций для конкретных конструкций выражений
ast_node_t* parse_expression_arithmetic(parser_context_t* ctx);
ast_node_t* parse_expression_logical(parser_context_t* ctx);
ast_node_t* parse_expression_function_call(parser_context_t* ctx);
ast_node_t* parse_expression_literal(parser_context_t* ctx);
ast_node_t* parse_expression_identifier(parser_context_t* ctx);
ast_node_t* parse_expression_bracketed(parser_context_t* ctx);
// ... добавить остальные по мере необходимости

#endif // PARSER_EXPRESSION_H
