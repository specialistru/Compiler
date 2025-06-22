#include "parser_perform_elseif.h"
#include "parser_utils.h"

// Парсинг конструкции ELSEIF внутри PERFORM (если есть расширения, например в условных выражениях)
ast_node_t* parse_perform_elseif(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "ELSEIF")) {
        return NULL;
    }

    ast_node_t* elseif_node = ast_node_create(AST_PERFORM_ELSEIF, ctx->previous);

    ast_node_t* condition = parse_perform_condition(ctx);
    if (!condition) {
        parse_error("Ожидалось условие после ELSEIF", ctx);
    }
    ast_node_add_child(elseif_node, condition);

    if (!parser_match_keyword(ctx, "THEN")) {
        parse_error("Ожидался THEN после условия ELSEIF", ctx);
    }

    ast_node_t* body = parse_perform_body(ctx);
    ast_node_add_child(elseif_node, body);

    return elseif_node;
}
