#include "parser_call.h"
#include <stdio.h>

// Разбор секции EXCEPTIONS в CALL FUNCTION
ast_node_t* parse_call_exceptions(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "EXCEPTIONS")) {
        return NULL;
    }

    ast_node_t* exceptions_node = ast_node_create(AST_CALL_EXCEPTIONS, ctx->previous);

    while (ctx->current.type == TOKEN_IDENTIFIER) {
        token_t exc_name = ctx->current;
        parser_advance(ctx);

        if (ctx->current.type == TOKEN_NUMBER) {
            token_t exc_code = ctx->current;
            parser_advance(ctx);

            // Создаем узел исключения с кодом
            ast_node_t* exc_node = ast_node_create(AST_CALL_EXCEPTION, exc_name);
            ast_node_t* code_node = ast_node_create(AST_EXPR_LITERAL, exc_code);
            ast_node_add_child(exc_node, code_node);

            ast_node_add_child(exceptions_node, exc_node);
        } else {
            // Исключение без кода
            ast_node_t* exc_node = ast_node_create(AST_CALL_EXCEPTION, exc_name);
            ast_node_add_child(exceptions_node, exc_node);
        }

        if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
            break;
        }
    }

    return exceptions_node;
}
