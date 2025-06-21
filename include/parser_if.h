#ifndef PARSER_IF_H
#define PARSER_IF_H

#include "ast.h"
#include "lexer.h"

// Главная функция для парсинга конструкции IF (весь блок: IF ... ELSEIF ... ELSE ... ENDIF)
ast_node_t* parse_if(token_stream_t *tokens);

// Парсинг условия IF (поддержка скобок, NOT, простых условий)
ast_node_t* parse_if_condition(token_stream_t *tokens);

// Парсинг логических операций AND/OR в условиях
ast_node_t* parse_if_logical_ops(token_stream_t *tokens, ast_node_t *left);

// Парсинг вложенного IF (вложенный блок IF внутри тела)
ast_node_t* parse_if_nested(token_stream_t *tokens);

// Парсинг ветки ELSEIF
ast_node_t* parse_if_elseif(token_stream_t *tokens);

// Парсинг ветки ELSE
ast_node_t* parse_if_else(token_stream_t *tokens);

// Проверка и парсинг ENDIF
int parse_if_end(token_stream_t *tokens);

// Парсинг тела IF/ELSE с произвольными инструкциями
ast_node_t* parse_if_body(token_stream_t *tokens);

// Обработка и отчёт об ошибках синтаксиса конструкции IF
void parse_if_error(const char *message, token_stream_t *tokens);

#endif // PARSER_IF_H
