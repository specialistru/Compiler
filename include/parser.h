#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

// Структура парсера
typedef struct {
    lexer_t lexer;
    token_t current;
    token_t previous;
} parser_t;

// Инициализация парсера
void parser_init(parser_t* parser, const char* source);

// Основной парсинг программы
ast_node_t* parse_program(parser_t* parser);

// Освобождение ресурсов
void parser_free(parser_t* parser);

// Диагностика ошибок
void parser_error(parser_t* parser, const char* message);

#endif
