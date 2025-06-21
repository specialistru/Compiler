#include "parser_perform_else.h"
#include "parser_utils.h"

// Парсинг ELSE ветки в PERFORM
ast_node_t* parse_perform_else(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "ELSE")) {
        return NULL;
    }

    ast_node_t* else_node = ast_node_create(AST_PERFORM_ELSE, ctx->previous);

    ast_node_t* body = parse_perform_body(ctx);
    ast_node_add_child(else_node, body);

    return else_node;
}

