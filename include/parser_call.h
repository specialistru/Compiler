#ifndef PARSER_CALL_H
#define PARSER_CALL_H

#include "ast.h"
#include "parser_context.h"

// Главная функция парсинга CALL FUNCTION
ast_node_t* parse_call(parser_context_t* ctx);

// Простая конструкция: CALL FUNCTION 'func_name'.
ast_node_t* parse_call_simple(parser_context_t* ctx);

// Парсинг EXPORTING параметров
ast_node_t* parse_call_exporting(parser_context_t* ctx);

// Парсинг IMPORTING параметров
ast_node_t* parse_call_importing(parser_context_t* ctx);

// Парсинг EXCEPTIONS блока
ast_node_t* parse_call_exceptions(parser_context_t* ctx);

// Парсинг TABLES блока
ast_node_t* parse_call_tables(parser_context_t* ctx);

// Обработка ошибок парсинга CALL
void parse_call_error(const char* message, parser_context_t* ctx);

#endif // PARSER_CALL_H
