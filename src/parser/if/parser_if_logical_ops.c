#include "parser_if.h"

// Вспомогательная функция для парсинга логических выражений (AND/OR)
ast_node_t* parse_logical_expression(parser_t* parser) {
    ast_node_t* left = parse_simple_condition(parser);
    if (!left) return NULL;

    while (true) {
        token_t* token = parser_peek_token(parser);
        if (token->type == TOKEN_AND || token->type == TOKEN_OR) {
            token_t op_token = parser_next_token(parser);
            ast_node_t* right = parse_simple_condition(parser);
            if (!right) {
                ast_node_free(left);
                return NULL;
            }
            ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
            ast_node_add_child(bin_op, left);
            ast_node_add_child(bin_op, right);
            left = bin_op;
        } else {
            break;
        }
    }
    return left;
}
