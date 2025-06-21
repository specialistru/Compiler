#include "parser_perform.h"
#include <stdio.h>

// Парсинг сложных конструкций PERFORM, например:
// PERFORM subroutine WITH param1 param2 RETURNING var.

ast_node_t* parse_perform_complex(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "PERFORM")) {
        return NULL;
    }

    token_t subroutine_token = expect_identifier(ctx);
    ast_node_t* node = ast_node_create(AST_PERFORM_COMPLEX, subroutine_token);

    // Проверяем параметры WITH
    if (parser_match(ctx, TOKEN_KEYWORD, "WITH")) {
        ast_node_t* with_node = ast_node_create(AST_PERFORM_WITH, ctx->previous);
        while (ctx->current.type == TOKEN_IDENTIFIER) {
            token_t param = ctx->current;
            parser_advance(ctx);
            ast_node_t* param_node = ast_node_create(AST_EXPR_IDENTIFIER, param);
            ast_node_add_child(with_node, param_node);
        }
        ast_node_add_child(node, with_node);
    }

    // Проверяем RETURNING
    if (parser_match(ctx, TOKEN_KEYWORD, "RETURNING")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор после RETURNING\n");
            exit(EXIT_FAILURE);
        }
        token_t ret_var = ctx->current;
        parser_advance(ctx);
        ast_node_t* ret_node = ast_node_create(AST_PERFORM_RETURNING, ret_var);
        ast_node_add_child(node, ret_node);
    }

    // Ожидаем точку в конце
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце PERFORM\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
