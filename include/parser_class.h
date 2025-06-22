#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H

#include "ast.h"
#include "parser_context.h"

// Основной парсер класса
ast_node_t* parse_class(parser_context_t* ctx);

// Определение класса
ast_node_t* parse_class_simple(parser_context_t* ctx);

// Объявление метода внутри класса
ast_node_t* parse_class_method(parser_context_t* ctx);

// Завершение класса
ast_node_t* parse_class_endclass(parser_context_t* ctx);

// Определение интерфейса
ast_node_t* parse_class_interface(parser_context_t* ctx);

// Завершение интерфейса
ast_node_t* parse_class_endinterface(parser_context_t* ctx);

// Объявление атрибутов класса
ast_node_t* parse_class_attributes(parser_context_t* ctx);

// Установка видимости (PUBLIC/PROTECTED/PRIVATE)
ast_node_t* parse_class_visibility(parser_context_t* ctx);

// Обработка синтаксических ошибок
void parse_class_error(const char* message, parser_context_t* ctx);

#endif // PARSER_CLASS_H
