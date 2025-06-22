#ifndef PARSER_METHOD_H
#define PARSER_METHOD_H

#include "parser.h"
#include "ast.h"

// Главная функция парсинга метода
ast_node_t* parse_method(parser_t* parser);

// Парсинг объявления метода
ast_node_t* parse_method_declaration(parser_t* parser);

// Парсинг определения метода с телом
ast_node_t* parse_method_definition(parser_t* parser);

// Парсинг параметров метода
ast_node_t* parse_method_parameters(parser_t* parser);

// Парсинг видимости метода (PUBLIC, PRIVATE, PROTECTED)
ast_node_t* parse_method_visibility(parser_t* parser);

// Обработка ошибок в парсинге методов
void parse_method_error(parser_t* parser, const char* message);

#endif // PARSER_METHOD_H
