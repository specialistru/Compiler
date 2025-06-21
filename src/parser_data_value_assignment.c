#include "parser_data_value_assignment.h"
#include <stdio.h>

// Пример разбора VALUE = <expression> в объявлении

static ast_node_t* parse_expression(parser_context_t* ctx); // Предполагается, что функция есть

ast_node_t* parse_data_value_assignment(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "VALUE")) {
        return NULL;
    }

    if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался '=' после VALUE\n");
        exit(EXIT_FAILURE);
    }

    ast_node_t* expr = parse_expression(ctx);
    if (!expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе выражения после VALUE =\n");
        exit(EXIT_FAILURE);
    }

    return expr;
}
