#include "parser_call.h"

// Парсинг возвращаемых значений (IMPORTING)
ast_node_t* parse_call_return_values(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "IMPORTING")) {
        return NULL; // Возвращаемые значения необязательны
    }

    ast_node_t* import_node = ast_node_create(AST_CALL_IMPORTING, ctx->previous);

    while (!parser_check(ctx, TOKEN_SYMBOL, ".") && !parser_check_keyword(ctx, "EXCEPTIONS") && !parser_check_eof(ctx)) {
        token_t param_name = expect_identifier(ctx);
        ast_node_t* param_node = ast_node_create(AST_CALL_PARAM, param_name);

        if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
            parse_call_error("Expected '=' in IMPORTING parameter", ctx);
            return NULL;
        }

        ast_node_t* expr = parse_expression(ctx);
        if (!expr) {
            parse_call_error("Expected expression after '=' in IMPORTING", ctx);
            return NULL;
        }
        ast_node_add_child(param_node, expr);

        ast_node_add_child(import_node, param_node);

        if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
            break;
        }
    }

    return import_node;
}
