#include "parser_data_initialization.h"
#include <stdio.h>

// Парсинг INITIAL VALUE <значение> (например, INITIAL VALUE 0)
ast_node_t* parse_initialization(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "INITIAL")) {
        return NULL;
    }
    if (!parser_match(ctx, TOKEN_KEYWORD, "VALUE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось VALUE после INITIAL\n");
        exit(EXIT_FAILURE);
    }

    token_t init_value_token = ctx->current;
    if (init_value_token.type != TOKEN_LITERAL && init_value_token.type != TOKEN_NUMBER && init_value_token.type != TOKEN_STRING) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось значение после INITIAL VALUE, найдено: %s\n", init_value_token.lexeme);
        exit(EXIT_FAILURE);
    }

    parser_advance(ctx);

    ast_node_t* init_node = ast_node_create(AST_EXPR_INITIAL_VALUE, init_value_token);

    return init_node;
}
