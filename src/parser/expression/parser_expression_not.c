#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Парсинг выражений с оператором NOT
ast_node_t* parse_expression_not(parser_context_t* ctx) {
    if (ctx->current.type == TOKEN_KEYWORD && strcmp(ctx->current.lexeme, "NOT") == 0) {
        token_t not_token = ctx->current;
        parser_next_token(ctx); // consume NOT

        ast_node_t* operand = parse_expression_comparison(ctx); // например: NOT a = 1

        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после 'NOT'\n");
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_NOT, not_token);
        ast_node_add_child(node, operand);
        return node;
    }

    return parse_expression_comparison(ctx); // без NOT — обычное сравнение
}
