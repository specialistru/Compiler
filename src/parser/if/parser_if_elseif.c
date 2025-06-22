#include "parser_if_elseif.h"
#include "parser_if_condition.h"
#include "parser_if_body.h"
#include "lexer.h"
#include "ast.h"

// парсинг ELSEIF
ast_node_t* parse_if_elseif(token_stream_t *tokens) {
    if (tokens->current_token.type != TOKEN_ELSEIF) return NULL;
    ast_node_t *elseif_node = ast_node_create(AST_ELSEIF, tokens->current_token);
    token_advance(tokens);

    ast_node_t *condition = parse_if_condition(tokens);
    if (!condition) return NULL;
    ast_node_add_child(elseif_node, condition);

    ast_node_t *body = parse_if_body(tokens);
    if (!body) return NULL;
    ast_node_add_child(elseif_node, body);

    return elseif_node;
}
