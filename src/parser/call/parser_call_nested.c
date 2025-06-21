#include "parser_call.h"

// Поддержка вложенных вызовов функций
ast_node_t* parse_call_nested(parser_context_t* ctx) {
    ast_node_t* root_node = ast_node_create(AST_CALL_NESTED, ctx->current);

    // Парсим первый вызов
    ast_node_t* first_call = parse_call_simple(ctx);
    if (!first_call) {
        parse_call_error("Expected function call", ctx);
        return NULL;
    }
    ast_node_add_child(root_node, first_call);

    // Пока есть вложенные вызовы, парсим их
    while (parser_match_keyword(ctx, "CALL")) {
        ast_node_t* nested_call = parse_call_simple(ctx);
        if (!nested_call) {
            parse_call_error("Invalid nested function call", ctx);
            return NULL;
        }
        ast_node_add_child(root_node, nested_call);
    }

    return root_node;
}
