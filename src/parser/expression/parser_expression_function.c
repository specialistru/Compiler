#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Разбор вызова функции с параметрами:
// Пример: func_name(arg1, arg2, ...)
ast_node_t* parse_expression_function(parser_context_t* ctx) {
    // Проверяем, что текущий токен — идентификатор (имя функции)
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя функции, но найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    token_t func_name_token = ctx->current;
    parser_next_token(ctx); // съедаем имя функции

    // Ожидаем '('
    if (ctx->current.type != TOKEN_SYMBOL || strcmp(ctx->current.lexeme, "(") != 0) {
        fprintf(stderr, "[PARSER ERROR] Ожидался символ '(' после имени функции '%s'\n", func_name_token.lexeme);
        return NULL;
    }
    parser_next_token(ctx); // съедаем '('

    // Создаем узел функции
    ast_node_t* func_node = ast_node_create(AST_EXPR_FUNCTION_CALL, func_name_token);

    // Парсим список аргументов (возможно пустой)
    if (ctx->current.type != TOKEN_SYMBOL || strcmp(ctx->current.lexeme, ")") != 0) {
        while (1) {
            ast_node_t* arg_node = parse_expression_operation(ctx);
            if (!arg_node) {
                fprintf(stderr, "[PARSER ERROR] Ошибка парсинга аргумента функции '%s'\n", func_name_token.lexeme);
                ast_node_destroy(func_node);
                return NULL;
            }

            ast_node_add_child(func_node, arg_node);

            if (ctx->current.type == TOKEN_SYMBOL && strcmp(ctx->current.lexeme, ",") == 0) {
                parser_next_token(ctx); // съедаем запятую и парсим следующий аргумент
            } else {
                break;
            }
        }
    }

    // Ожидаем ')'
    if (ctx->current.type != TOKEN_SYMBOL || strcmp(ctx->current.lexeme, ")") != 0) {
        fprintf(stderr, "[PARSER ERROR] Ожидался символ ')' после аргументов функции '%s'\n", func_name_token.lexeme);
        ast_node_destroy(func_node);
        return NULL;
    }
    parser_next_token(ctx); // съедаем ')'

    return func_node;
}
