// parser_if_elseif.c
#include "parser_if_elseif.h"
#include "ast.h"
#include "parser_if_condition.h"
#include "parser_if_body.h"
#include "parser.h"

bool parse_if_elseif(parser_t* parser, ast_node_t* parent_node) {
    // Создаем узел ELSEIF
    token_t token = parser_previous_token(parser);
    ast_node_t* elseif_node = ast_node_create(AST_ELSEIF, token);

    // Парсим условие ELSEIF
    if (!parse_if_condition(parser, elseif_node)) return false;

    // Парсим тело ELSEIF
    if (!parse_if_body(parser, elseif_node)) return false;

    ast_node_add_child(parent_node, elseif_node);
    return true;
}
