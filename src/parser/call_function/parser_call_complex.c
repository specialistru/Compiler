#include "parser_call.h"

// Парсинг сложных вызовов с параметрами, исключениями, возвратами
ast_node_t* parse_call_complex(parser_context_t* ctx) {
    ast_node_t* node = ast_node_create(AST_CALL_COMPLEX, ctx->current);

    if (!parser_match_keyword(ctx, "CALL") || !parser_match_keyword(ctx, "FUNCTION")) {
        parse_call_error("Expected 'CALL FUNCTION' keyword", ctx);
        return NULL;
    }

    // Ожидаем имя функции
    token_t func_name = expect_identifier(ctx);
    ast_node_t* func_node = ast_node_create(AST_CALL_FUNC_NAME, func_name);
    ast_node_add_child(node, func_node);

    // Параметры
    ast_node_t* params = parse_call_parameters(ctx);
    if (params) ast_node_add_child(node, params);

    // Возвращаемые значения
    ast_node_t* imports = parse_call_return_values(ctx);
    if (imports) ast_node_add_child(node, imports);

    // Исключения
    ast_node_t* exceptions = parse_call_exceptions(ctx);
    if (exceptions) ast_node_add_child(node, exceptions);

    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parse_call_error("Expected '.' at end of CALL FUNCTION statement", ctx);
        return NULL;
    }

    return node;
}
