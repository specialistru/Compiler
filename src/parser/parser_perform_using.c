#include "parser_perform.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг параметров USING и CHANGING внутри FORM
ast_node_t* parse_perform_parameters(parser_t* parser) {
    ast_node_t* param_root = ast_node_create(AST_PARAMETERS, parser->current);

    while (parser_match(parser, TOKEN_KEYWORD, "USING") || parser_match(parser, TOKEN_KEYWORD, "CHANGING")) {
        token_t keyword_token = parser_previous(parser);
        ast_node_type_t param_type = (strcmp(keyword_token.lexeme, "USING") == 0)
                                     ? AST_EXPR_USING
                                     : AST_EXPR_CHANGING;

        ast_node_t* param_section = ast_node_create(param_type, keyword_token);

        // Парсим список параметров: идентификаторы через пробел
        while (parser_check(parser, TOKEN_IDENTIFIER)) {
            token_t ident_token = parser_advance(parser);
            ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, ident_token);
            ast_node_add_child(param_section, ident_node);
        }

        ast_node_add_child(param_root, param_section);
    }

    return param_root;
}
