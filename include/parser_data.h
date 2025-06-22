#ifndef PARSER_DATA_H
#define PARSER_DATA_H

#include "ast.h"
#include "parser_context.h"

//
// Основные функции парсинга конструкций DATA и родственных в ABAP
//

// Парсинг объявления данных: DATA, CONSTANTS, TYPES, FIELD-SYMBOLS, PARAMETERS и др.
ast_node_t* parse_data_declaration(parser_context_t* ctx);

//
// Присвоение значения переменной (VALUE assignment)
ast_node_t* parse_value_assignment(parser_context_t* ctx);

//
// Инициализация переменной (INITIAL VALUE ...)
ast_node_t* parse_initialization(parser_context_t* ctx);

//
// Разбор сложных типов (TABLE OF, STRUCTURE, UNION и др.)
ast_node_t* parse_complex_type(parser_context_t* ctx);

//
// Обработка констант и их значений
ast_node_t* parse_constants_value(parser_context_t* ctx);

//
// Парсинг параметров (PARAMETERS)
ast_node_t* parse_parameters_declaration(parser_context_t* ctx);

//
// Парсинг указателей (FIELD-SYMBOLS)
ast_node_t* parse_field_symbols_declaration(parser_context_t* ctx);

//
// Парсинг конструкции SELECT-OPTIONS
ast_node_t* parse_select_options_declaration(parser_context_t* ctx);

//
// Парсинг RANGES
ast_node_t* parse_ranges_declaration(parser_context_t* ctx);

#endif // PARSER_DATA_H
