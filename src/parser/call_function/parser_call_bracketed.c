#include "parser_call.h"

// CALL FUNCTION('FUNC') — вызов с именем в скобках
ast_node_t* parse_call_bracketed(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "CALL") || !parser_match_keyword(ctx, "FUNCTION"))
        return NULL;

    if (!parser_match_symbol(ctx, "(")) {
        parse_call_error("Ожидалась '(' после FUNCTION", ctx);
        return NULL;
    }

    if (ctx->current.type != TOKEN_STRING) {
        parse_call_error("Ожидалась строка с именем функции", ctx);
        return NULL;
    }

    token_t func_name = ctx->current;
    parser_advance(ctx);

    if (!parser_match_symbol(ctx, ")")) {
        parse_call_error("Ожидалась ')'", ctx);
        return NULL;
    }

    ast_node_t* root = ast_node_create(AST_CALL_BRACKETED, func_name);

    ast_node_t* params = parse_call_parameters(ctx);
    if (params) ast_node_add_child(root, params);

    ast_node_t* exceptions = parse_call_exceptions(ctx);
    if (exceptions) ast_node_add_child(root, exceptions);

    if (!parser_match_symbol(ctx, ".")) {
        parse_call_error("Ожидалась '.' после CALL FUNCTION(...)", ctx);
        return NULL;
    }

    return root;
}
