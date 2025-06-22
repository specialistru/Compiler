/*
#include "parser_expression.h"
#include <stdio.h>

// Парсинг простого термина выражения: литерал, идентификатор, (выражение)
ast_node_t* parse_expression_term(parser_context_t* ctx) {
    token_t token = ctx->current;

    // Числовой литерал
    if (token.type == TOKEN_NUMBER) {
        parser_next_token(ctx);  // consume число
        return ast_node_create(AST_EXPR_LITERAL_NUMBER, token);
    }

    // Строковый литерал
    if (token.type == TOKEN_STRING) {
        parser_next_token(ctx);  // consume строку
        return ast_node_create(AST_EXPR_LITERAL_STRING, token);
    }

    // Идентификатор
    if (token.type == TOKEN_IDENTIFIER) {
        parser_next_token(ctx);  // consume идентификатор
        return ast_node_create(AST_EXPR_IDENTIFIER, token);
    }

    // Скобочное выражение: ( expr )
    if (token.type == TOKEN_SYMBOL && strcmp(token.lexeme, "(") == 0) {
        parser_next_token(ctx); // consume '('

        ast_node_t* inner_expr = parse_expression(ctx);
        if (!inner_expr) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение внутри скобок\n");
            return NULL;
        }

        if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ')'\n");
            ast_node_free(inner_expr);
            return NULL;
        }

        return inner_expr; // возвращаем вложенное выражение
    }

    // Ошибка: неожиданный токен
    fprintf(stderr, "[PARSER ERROR] Ожидалось выражение, но найдено: %s\n", token.lexeme);
    return NULL;
}


#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Парсинг элементарного термина выражения
ast_node_t* parse_expression_term(parser_context_t* ctx) {
    token_t token = ctx->current;

    switch (token.type) {
        case TOKEN_IDENTIFIER:
            parser_next_token(ctx);
            return ast_node_create(AST_EXPR_IDENTIFIER, token);

        case TOKEN_NUMBER:
            parser_next_token(ctx);
            return ast_node_create(AST_EXPR_NUMBER, token);

        case TOKEN_STRING:
            parser_next_token(ctx);
            return ast_node_create(AST_EXPR_STRING, token);

        case TOKEN_SYMBOL:
            if (strcmp(token.lexeme, "(") == 0) {
                parser_next_token(ctx);  // Пропустить '('
                ast_node_t* expr = parse_expression(ctx);
                if (!parser_expect(ctx, TOKEN_SYMBOL, ")")) {
                    fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ')'\n");
                    return NULL;
                }
                return expr;
            }
            break;

        default:
            break;
    }

    fprintf(stderr, "[PARSER ERROR] Ожидалось выражение, но найдено: '%s'\n", token.lexeme);
    return NULL;
}
*/

#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция парсинга терминов — базовых элементов выражения:
// идентификаторы, константы, скобочные выражения
ast_node_t* parse_expression_term(parser_context_t* ctx) {
    ast_node_t* node = NULL;

    switch (ctx->current.type) {
        case TOKEN_IDENTIFIER:
            // Создаем узел идентификатора
            node = ast_node_create(AST_EXPR_IDENTIFIER, ctx->current);
            parser_next_token(ctx); // Сдвигаемся к следующему токену
            break;

        case TOKEN_NUMBER:
        case TOKEN_STRING:
            // Константа (число или строка)
            node = ast_node_create(AST_EXPR_CONSTANT, ctx->current);
            parser_next_token(ctx);
            break;

        case TOKEN_SYMBOL:
            if (strcmp(ctx->current.lexeme, "(") == 0) {
                // Скобочное выражение
                parser_next_token(ctx); // съедаем '('

                node = parse_expression_operation(ctx); // рекурсивно парсим внутреннее выражение

                if (!node) {
                    fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после '('\n");
                    return NULL;
                }

                if (strcmp(ctx->current.lexeme, ")") != 0) {
                    fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ')'\n");
                    ast_node_destroy(node);
                    return NULL;
                }
                parser_next_token(ctx); // съедаем ')'
            }
            else {
                fprintf(stderr, "[PARSER ERROR] Ожидался термин, найден символ '%s'\n", ctx->current.lexeme);
                return NULL;
            }
            break;

        default:
            fprintf(stderr, "[PARSER ERROR] Ожидался термин, найден токен типа %d\n", ctx->current.type);
            return NULL;
    }

    return node;
}
