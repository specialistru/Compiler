#include "parser_if_logical_ops.h"
#include "lexer.h"
#include "ast.h"

// Парсинг логических операций AND/OR в условиях
ast_node_t* parse_if_logical_ops(token_stream_t *tokens, ast_node_t *left) {
    while (tokens->current_token.type == TOKEN_AND || tokens->current_token.type == TOKEN_OR) {
        token_type_t op_type = tokens->current_token.type;
        token_advance(tokens);

        ast_node_t *right = parse_if_condition(tokens);
        if (!right) return NULL;

        ast_node_t *bin_op = ast_node_create(AST_EXPR_BINARY_OP, tokens->current_token);
        bin_op->token.type = op_type;
        ast_node_add_child(bin_op, left);
        ast_node_add_child(bin_op, right);

        left = bin_op;
    }
    return left;
}
