// parser_if_body.c
#include "parser_if_body.h"
#include "ast.h"
#include "parser.h"

// Парсинг тела блока IF, ELSEIF, ELSE (список инструкций)
bool parse_if_body(parser_t* parser, ast_node_t* parent_node) {
    while (!parser_check_keyword(parser, "ELSEIF") &&
           !parser_check_keyword(parser, "ELSE") &&
           !parser_check_keyword(parser, "ENDIF") &&
           !parser_is_at_end(parser)) {
        ast_node_t* stmt = parse_statement(parser);
        if (!stmt) return false;
        ast_node_add_child(parent_node, stmt);
    }
    return true;
}
