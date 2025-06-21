#include "parser_call.h"

// Парсинг вызовов в скобках: CALL FUNCTION('FUNC_NAME')
ast_node_t* parse_call_bracketed(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "CALL") || !parser_match_keyword(ctx, "FUNCTION")) {
        return NULL;
    }
    if (!parser_match(ctx, TOKEN_SYMBOL, "(")) {
        return NULL;
    }

    // Ожидаем строку с именем функции
    if (ctx->current.type != TOKEN_STRING) {
        parse_call_error("Expected function name string inside brackets", ctx);
        return NULL;
    }

    token_t func_name = ctx->current;
    parser_advance(ctx);

    if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
        parse_call_error("Expected ')' after function name", ctx);
        return NULL;
    }

    ast_node_t* node = ast_node_create(AST_CALL_BRACKETED, func_name);

    // Парсим параметры и исключения
    ast_node_t* params = parse_call_parameters(ctx);
    if (params) ast_node_add_child(node, params);

    ast_node_t* exceptions = parse_call_exceptions(ctx);
    if (exceptions) ast_node_add_child(node, exceptions);

    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parse_call_error("Expected '.' after CALL FUNCTION(...)", ctx);
        return NULL;
    }

    return node;
}
