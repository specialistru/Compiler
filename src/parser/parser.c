#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast.h"
#include "error_handling.h"

// Очень упрощённый пример парсера: только список идентификаторов как программа
static parser_t* global_parser;

static void parser_advance() {
    global_parser->current_token = lexer_next_token();
}

void parser_init(parser_t* parser, const char* source) {
    global_parser = parser;
    lexer_init(source);
    parser_advance();
}

static ast_node_t* parse_identifier() {
    if (global_parser->current_token.type == TOKEN_IDENTIFIER) {
        ast_node_t* node = ast_node_create(AST_VARIABLE, global_parser->current_token.text);
        parser_advance();
        return node;
    }
    log_error("Expected identifier");
    return NULL;
}

ast_node_t* parser_parse_program(parser_t* parser) {
    ast_node_t* root = ast_node_create(AST_PROGRAM, NULL);
    while (global_parser->current_token.type != TOKEN_EOF) {
        ast_node_t* node = parse_identifier();
        if (node) {
            ast_node_add_child(root, node);
        } else {
            break;
        }
    }
    return root;
}
