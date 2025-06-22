// parser_class_statement.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Функция парсинга одного оператора (statement).
// В зависимости от текущего токена вызывает соответствующие подфункции парсинга.
// Возвращает ast_node_t* — узел AST или NULL при ошибке.

ast_node_t* parse_statement(parser_context_t* ctx) {
    if (!ctx) return NULL;

    // Проверяем текущий токен и решаем, что парсить

    switch (ctx->current.type) {
        case TOKEN_KEYWORD:
            if (strcmp(ctx->current.lexeme, "IF") == 0) {
                // Парсим конструкцию IF
                return parse_if(ctx);
            } else if (strcmp(ctx->current.lexeme, "WHILE") == 0) {
                // Парсим цикл WHILE
                return parse_while(ctx);
            } else if (strcmp(ctx->current.lexeme, "RETURN") == 0) {
                // Парсим оператор возврата
                return parse_return(ctx);
            } else if (strcmp(ctx->current.lexeme, "METHOD") == 0) {
                // Парсим определение метода (если актуально)
                return parse_method_definition(ctx);
            }
            // Добавить другие ключевые слова по необходимости
            break;

        case TOKEN_IDENTIFIER:
            // Может быть вызов функции, присвоение и т.п.
            // Например, парсим выражение или вызов функции
            return parse_expression(ctx);

        case TOKEN_SYMBOL:
            if (strcmp(ctx->current.lexeme, "{") == 0) {
                // Начало блока кода
                return parse_block(ctx);
            }
            break;

        default:
            break;
    }

    fprintf(stderr, "[PARSER ERROR] Неизвестный или неподдерживаемый оператор: %s\n", ctx->current.lexeme);
    return NULL;
}
