#include "parser_data_type.h"

// Обрабатывает конструкцию "TYPE typename"
ast_node_t* parse_type_clause(parser_context_t* ctx) {
    if (parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        token_t type_tok = expect_identifier(ctx);
        ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
        return type_node;
    }
    return NULL;
}
