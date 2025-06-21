#include "parser_perform_not.h"
#include "parser_utils.h"

// Парсинг логического оператора NOT в условии PERFORM
ast_node_t* parse_perform_not(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "NOT")) {
        return NULL;
    }

    token_t not_token = ctx->previous;

    ast_node_t* operand = parse_perform_condition(ctx);
    if (!operand) {
        parse_error("Ожидалось выражение после NOT", ctx);
    }

    ast_node_t* not_node = ast_node_create(AST_LOGICAL_NOT, not_token);
    ast_node_add_child(not_node, operand);

    return not_node;
}
