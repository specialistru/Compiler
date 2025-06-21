#include "parser_data_constants_value.h"
#include <stdio.h>

// Парсинг VALUE <значение> для CONSTANTS
ast_node_t* parse_constants_value(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "VALUE")) {
        return NULL;
    }

    token_t value_token = ctx->current;
    if (value_token.type != TOKEN_LITERAL && value_token.type != TOKEN_NUMBER && value_token.type != TOKEN_STRING) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось значение после VALUE в CONSTANTS, найдено: %s\n", value_token.lexeme);
        exit(EXIT_FAILURE);
    }

    parser_advance(ctx);

    ast_node_t* value_node = ast_node_create(AST_EXPR_VALUE, value_token);
    return value_node;
}
