#include "parser_call.h"

// Динамический вызов функции по имени в переменной
ast_node_t* parse_call_dynamic(parser_context_t* ctx) {
    // Ожидаем CALL FUNCTION var_name
    if (!parser_match_keyword(ctx, "CALL") || !parser_match_keyword(ctx, "FUNCTION")) {
        return NULL;
    }

    // Следующий токен — идентификатор или строка с именем функции
    if (ctx->current.type != TOKEN_IDENTIFIER && ctx->current.type != TOKEN_STRING) {
        parse_call_error("Expected function name or variable for dynamic call", ctx);
        return NULL;
    }

    token_t func_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* node = ast_node_create(AST_CALL_DYNAMIC, func_name);

    // Опционально парсим параметры, исключения и т.д.
    ast_node_t* params = parse_call_parameters(ctx);
    if (params) ast_node_add_child(node, params);

    ast_node_t* exceptions = parse_call_exceptions(ctx);
    if (exceptions) ast_node_add_child(node, exceptions);

    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parse_call_error("Expected '.' after CALL FUNCTION dynamic call", ctx);
        return NULL;
    }

    return node;
}
