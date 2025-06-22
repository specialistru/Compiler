// parser_if_syntax_error.c
#include "parser_if.h"
#include <stdio.h>

void parser_error(parser_t* parser, const char* message) {
    fprintf(stderr, "Syntax error at line %d, col %d: %s\n",
            parser->current_token.line, parser->current_token.column, message);
    parser->had_error = true;
}

// Пример обработки ошибки в IF
ast_node_t* parse_if_statement(parser_t* parser) {
    if (!parser_match_token(parser, TOKEN_IF)) {
        parser_error(parser, "Expected IF");
        return NULL;
    }

    ast_node_t* condition = parse_complex_condition(parser);
    if (!condition) {
        parser_error(parser, "Invalid IF condition");
        return NULL;
    }

    ast_node_t* if_node = ast_node_create(AST_IF, parser->current_token);
    ast_node_add_child(if_node, condition);

    // Проверка тела IF
    if (!parse_statement_block(parser, if_node)) {
        parser_error(parser, "Expected statements inside IF block");
        ast_node_free(if_node);
        return NULL;
    }

    if (!parser_match_token(parser, TOKEN_ENDIF)) {
        parser_error(parser, "Expected ENDIF");
        ast_node_free(if_node);
        return NULL;
    }

    return if_node;
}
