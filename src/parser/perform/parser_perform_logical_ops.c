#include "parser_perform_logical_ops.h"
#include "parser_utils.h"

// Парсинг логических операций внутри PERFORM (например, в условных выражениях)
// Поддерживаются AND, OR
ast_node_t* parse_perform_logical_ops(parser_context_t* ctx, ast_node_t* left) {
    while (parser_check_keyword(ctx, "AND") || parser_check_keyword(ctx, "OR")) {
        token_t op_token = ctx->current;
        parser_advance(ctx);

        ast_node_t* right = parse_perform_condition(ctx);
        if (!right) {
            parse_error("Ожидалось выражение справа от логического оператора", ctx);
        }

        ast_node_t* op_node = ast_node_create(AST_LOGICAL_OP, op_token);
        ast_node_add_child(op_node, left);
        ast_node_add_child(op_node, right);

        left = op_node;
    }
    return left;
}
