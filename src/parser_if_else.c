#include "parser_if_else.h"
#include "parser_if_body.h"
#include "lexer.h"
#include "ast.h"

ast_node_t* parse_if_else(token_stream_t *tokens) {
    if (tokens->current_token.type != TOKEN_ELSE) return NULL;
    ast_node_t *else_node = ast_node_create(AST_ELSE, tokens->current_token);
    token_advance(tokens);

    ast_node_t *body = parse_if_body(tokens);
    if (!body) return NULL;
    ast_node_add_child(else_node, body);

    return else_node;
}
