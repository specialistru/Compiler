/*
#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция: ожидание конкретного токена
static void expect_token(parser_context_t* ctx, token_type_t expected_type) {
    if (ctx->current.type != expected_type) {
        fprintf(stderr, "[PARSER ERROR] Ожидался токен типа %d, найден %d (%s)\n",
                expected_type, ctx->current.type, ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
}

// Разбор первичного выражения: идентификатор, число, строка, или скобки
ast_node_t* parse_expression_primary(parser_context_t* ctx) {
    token_t token = ctx->current;
    ast_node_t* node = NULL;

    switch (token.type) {
        case TOKEN_IDENTIFIER:
            node = ast_node_create(AST_EXPR_IDENTIFIER, token);
            parser_next_token(ctx);
            break;

        case TOKEN_NUMBER:
            node = ast_node_create(AST_EXPR_NUMBER, token);
            parser_next_token(ctx);
            break;

        case TOKEN_STRING:
            node = ast_node_create(AST_EXPR_STRING, token);
            parser_next_token(ctx);
            break;

        case TOKEN_SYMBOL:
            if (strcmp(token.lexeme, "(") == 0) {
                parser_next_token(ctx); // consume '('
                node = parse_expression(ctx);
                if (!node) {
                    fprintf(stderr, "[PARSER ERROR] Ошибка в выражении внутри скобок\n");
                    return NULL;
                }
                if (ctx->current.type != TOKEN_SYMBOL || strcmp(ctx->current.lexeme, ")") != 0) {
                    fprintf(stderr, "[PARSER ERROR] Ожидалась ')'\n");
                    return NULL;
                }
                parser_next_token(ctx); // consume ')'
            } else {
                fprintf(stderr, "[PARSER ERROR] Неожиданный символ: %s\n", token.lexeme);
                return NULL;
            }
            break;

        default:
            fprintf(stderr, "[PARSER ERROR] Неожиданный токен: %s\n", token.lexeme);
            return NULL;
    }

    return node;
}
*/

#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Разбор первичных выражений: идентификаторы, числа, строки, скобки
ast_node_t* parse_expression_primary(parser_context_t* ctx) {
    token_t token = ctx->current;

    // Скобочное выражение: ( expr )
    if (token.type == TOKEN_SYMBOL && strcmp(token.lexeme, "(") == 0) {
        parser_next_token(ctx);  // consume '('
        ast_node_t* inner_expr = parse_expression(ctx);  // рекурсивный вызов
        if (!inner_expr) {
            fprintf(stderr, "[PARSER ERROR] Пустое выражение внутри скобок\n");
            return NULL;
        }

        if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ')'\n");
            return NULL;
        }

        return inner_expr;  // не создаём отдельный узел для скобок
    }

    // Числовой литерал
    if (token.type == TOKEN_NUMBER) {
        parser_next_token(ctx);
        return ast_node_create(AST_EXPR_LITERAL_NUMBER, token);
    }

    // Строковый литерал
    if (token.type == TOKEN_STRING) {
        parser_next_token(ctx);
        return ast_node_create(AST_EXPR_LITERAL_STRING, token);
    }

    // Идентификатор
    if (token.type == TOKEN_IDENTIFIER) {
        parser_next_token(ctx);
        return ast_node_create(AST_EXPR_IDENTIFIER, token);
    }

    // Ошибка: неизвестный тип выражения
    fprintf(stderr, "[PARSER ERROR] Ожидалось первичное выражение, найдено: '%s'\n", token.lexeme);
    return NULL;
}
