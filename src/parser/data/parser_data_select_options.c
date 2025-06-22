// parser_data_select_options.c
#include "parser_data_select_options.h"
#include <stdio.h>

static token_t expect_identifier(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t token = ctx->current;
    parser_advance(ctx);
    return token;
}

ast_node_t* parse_data_select_options(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "SELECT-OPTIONS")) {
        return NULL;
    }

    ast_node_t* node = ast_node_create(AST_SELECT_OPTIONS, ctx->previous);

    token_t ident_tok = expect_identifier(ctx);
    ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, ident_tok);
    ast_node_add_child(node, ident_node);

    // Ожидаем точку
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась точка '.' в конце объявления SELECT-OPTIONS\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
