// parser_expression_function_call.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для парсинга списка аргументов функции
static ast_node_t* parse_argument_list(parser_context_t* ctx) {
    ast_node_t* args_list = ast_node_create(AST_ARG_LIST, ctx->current_token);

    if (parser_check(ctx, TOKEN_PAREN_CLOSE)) {
        // Пустой список аргументов
        parser_advance(ctx);  // пропускаем )
        return args_list;
    }

    while (1) {
        ast_node_t* expr = parse_expression(ctx);
        if (!expr) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение в списке аргументов\n");
            exit(EXIT_FAILURE);
        }
        ast_node_add_child(args_list, expr);

        if (parser_check(ctx, TOKEN_PAREN_CLOSE)) {
            parser_advance(ctx);  // пропускаем )
            break;
        }

        if (!parser_match(ctx, TOKEN_COMMA, ",")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась запятая или закрывающая скобка в списке аргументов\n");
            exit(EXIT_FAILURE);
        }
    }

    return args_list;
}

// Основная функция для парсинга вызова функции
ast_node_t* parse_expression_function_call(parser_context_t* ctx) {
    // Ожидаем идентификатор функции
    if (!parser_check(ctx, TOKEN_IDENTIFIER)) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор функции\n");
        return NULL;
    }
    token_t func_name = ctx->current_token;
    parser_advance(ctx);  // переходим к следующему токену

    // Ожидаем открывающую скобку '('
    if (!parser_match(ctx, TOKEN_PAREN_OPEN, "(")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась открывающая скобка '(' после имени функции\n");
        return NULL;
    }

    // Создаем AST-узел вызова функции
    ast_node_t* func_call_node = ast_node_create(AST_FUNCTION_CALL, func_name);

    // Парсим аргументы
    ast_node_t* args = parse_argument_list(ctx);
    ast_node_add_child(func_call_node, args);

    return func_call_node;
}
