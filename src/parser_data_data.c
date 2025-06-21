// parser_data_data.c
#include "parser_data_data.h"
#include <stdio.h>

// Вспомогательная функция: ожидает идентификатор переменной
static token_t expect_identifier(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t token = ctx->current;
    parser_advance(ctx);
    return token;
}

// Парсинг конструкции DATA <variable_name> [TYPE <type>] .
ast_node_t* parse_data_data(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "DATA")) {
        return NULL; // Не наша конструкция
    }

    ast_node_t* node = ast_node_create(AST_DATA, ctx->previous);

    token_t ident_tok = expect_identifier(ctx);
    ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, ident_tok);
    ast_node_add_child(node, ident_node);

    // Опциональный TYPE <typename>
    if (parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        token_t type_tok = expect_identifier(ctx);
        ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
        ast_node_add_child(node, type_node);
    }

    // Ожидаем точку в конце
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась точка '.' в конце объявления DATA\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
