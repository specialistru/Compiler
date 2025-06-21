// parser_if_else.c
#include "parser_if_else.h"
#include "ast.h"
#include "parser_if_body.h"
#include "parser.h"

bool parse_if_else(parser_t* parser, ast_node_t* parent_node) {
    token_t token = parser_previous_token(parser);
    ast_node_t* else_node = ast_node_create(AST_ELSE, token);

    if (!parse_if_body(parser, else_node)) return false;

    ast_node_add_child(parent_node, else_node);
    return true;
}
