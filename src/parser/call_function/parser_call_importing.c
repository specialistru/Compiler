#include "parser_call.h"
#include <stdio.h>

// Разбор секции IMPORTING параметров в CALL FUNCTION
ast_node_t* parse_call_importing(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "IMPORTING")) {
        return NULL;
    }

    ast_node_t* importing_node = ast_node_create(AST_CALL_IMPORTING, ctx->previous);

    while (ctx->current.type == TOKEN_IDENTIFIER) {
        token_t param_name = ctx->current;
        parser_advance(ctx);

        if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
            parse_call_error("Ожидался знак '=' после имени параметра IMPORTING", ctx);
            ast_node_destroy(importing_node);
            return NULL;
        }

        if (ctx->current.type != TOKEN_IDENTIFIER && ctx->current.type != TOKEN_STRING && ctx->current.type != TOKEN_NUMBER) {
            parse_call_error("Ожидалось значение параметра IMPORTING", ctx);
            ast_node_destroy(importing_node);
            return NULL;
        }
        token_t param_value = ctx->current;
        parser_advance(ctx);

        ast_node_t* param_node = ast_node_create(AST_CALL_PARAM, param_name);
        ast_node_t* value_node = ast_node_create(AST_EXPR_LITERAL, param_value);
        ast_node_add_child(param_node, value_node);

        ast_node_add_child(importing_node, param_node);

        if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
            break;
        }
    }

    return importing_node;
}
