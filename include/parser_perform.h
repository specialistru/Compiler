#ifndef PARSER_PERFORM_H
#define PARSER_PERFORM_H

#include "ast.h"
#include "parser_context.h"

// Главная функция парсинга конструкции PERFORM (весь блок)
ast_node_t* parse_perform(parser_context_t* ctx);

// Парсинг вложенной конструкции PERFORM (PERFORM внутри PERFORM)
ast_node_t* parse_perform_nested(parser_context_t* ctx);

// Парсинг логических операторов в PERFORM (AND, OR и т.д.)
ast_node_t* parse_perform_logical_ops(parser_context_t* ctx);

// Обработка синтаксических ошибок в конструкции PERFORM
void parse_perform_syntax_error(parser_context_t* ctx);

// Парсинг сложных конструкций PERFORM с несколькими выражениями
ast_node_t* parse_perform_complex(parser_context_t* ctx);

// Парсинг логических операторов AND/OR в PERFORM
ast_node_t* parse_perform_and_or(parser_context_t* ctx);

// Обработка и отчёт об ошибках PERFORM
void parse_perform_errors(parser_context_t* ctx);

// Парсинг конструкции ELSEIF внутри PERFORM (если есть)
ast_node_t* parse_perform_elseif(parser_context_t* ctx);

// Парсинг конструкции ELSE внутри PERFORM (если есть)
ast_node_t* parse_perform_else(parser_context_t* ctx);

// Парсинг логического оператора NOT внутри PERFORM
ast_node_t* parse_perform_not(parser_context_t* ctx);

// Парсинг условий в скобках ( ) в конструкции PERFORM
ast_node_t* parse_perform_bracketed(parser_context_t* ctx);

// Парсинг глубоко вложенных конструкций PERFORM (PERFORM внутри PERFORM)
ast_node_t* parse_perform_deep_nested(parser_context_t* ctx);

// Парсинг сложного тела PERFORM с несколькими инструкциями
ast_node_t* parse_perform_complex_body(parser_context_t* ctx);

#endif // PARSER_PERFORM_H
