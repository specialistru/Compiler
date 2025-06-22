#ifndef PARSER_IF_H
#define PARSER_IF_H

#include "ast.h"
#include "lexer.h"
#include "parser.h"

//
// === Главная точка входа ===
//

// Парсинг конструкции IF ... [ELSEIF] ... [ELSE] ... ENDIF.
ast_node_t* parse_if(parser_t* parser);

//
// === Поддержка вложенных и сложных условий ===
//

// Парсинг конструкции: IF NOT ...
ast_node_t* parse_if_not(parser_t* parser);

// Парсинг логических операций: AND, OR
ast_node_t* parse_if_and_or(parser_t* parser, ast_node_t* left_expr);

// Парсинг условий с вложенными скобками: IF (a = 1 OR (b = 2 AND c = 3))
ast_node_t* parse_if_bracketed(parser_t* parser);

// Парсинг вложенного IF внутри тела
ast_node_t* parse_if_nested(parser_t* parser);

//
// === Парсинг ветвей конструкции ===
//

// Парсинг выражения внутри IF, IF NOT и т.п.
ast_node_t* parse_if_condition(parser_t* parser);

// Парсинг тела инструкции IF / ELSE / ELSEIF
ast_node_t* parse_if_body(parser_t* parser);

// Парсинг ветки ELSEIF
ast_node_t* parse_if_elseif(parser_t* parser);

// Парсинг ветки ELSE
ast_node_t* parse_if_else(parser_t* parser);

// Проверка закрытия ENDIF
int parse_if_end(parser_t* parser);

//
// === Обработка ошибок ===
//

// Генерация сообщения об ошибке синтаксиса конструкции IF
void parse_if_error(const char* message, parser_t* parser);

#endif // PARSER_IF_H
