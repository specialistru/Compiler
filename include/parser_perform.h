#ifndef PARSER_PERFORM_H
#define PARSER_PERFORM_H

#include "ast.h"
#include "parser.h"

// Главная функция для разбора конструкции PERFORM
ast_node_t* parse_perform(parser_t* parser);

// Простая форма PERFORM form_name.
ast_node_t* parse_perform_simple(parser_t* parser);

// PERFORM form_name USING ... CHANGING ...
ast_node_t* parse_perform_with_params(parser_t* parser);

// Обработка вложенных PERFORM (если они поддерживаются)
ast_node_t* parse_perform_nested(parser_t* parser);

// Проверка синтаксических ошибок
void parse_perform_error(const char* message, parser_t* parser);

#endif // PARSER_PERFORM_H
