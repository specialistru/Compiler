// parser_data_parameters.c
#include "parser_data_parameters.h"
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

ast_node_t* parse_data_parameters(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "PARAMETERS")) {
        return NULL;
    }

    ast_node_t* node = ast_node_create(AST_PARAMETERS, ctx->previous);

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
        fprintf(stderr, "[PARSER ERROR] Ожидалась точка '.' в конце объявления PARAMETERS\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
