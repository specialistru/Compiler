#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Вспомогательная функция: проверяет, является ли токен оператором сравнения
static int is_comparison_operator(token_t *token) {
    const char *ops[] = { "=", "<>", "<", ">", "<=", ">=" };
    for (int i = 0; i < sizeof(ops)/sizeof(ops[0]); ++i) {
        if (strcmp(token->lexeme, ops[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Парсинг выражения сравнения: expr <op> expr (например: a = 1)
ast_node_t* parse_expression_comparison(parser_context_t* ctx) {
    ast_node_t* left = parse_expression_term(ctx);
    if (!left) {
        return NULL;
    }

    while (ctx->current.type == TOKEN_SYMBOL && is_comparison_operator(&ctx->current)) {
        token_t op_token = ctx->current;
        parser_next_token(ctx); // consume оператор сравнения

        ast_node_t* right = parse_expression_term(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение справа от оператора сравнения '%s'\n", op_token.lexeme);
            ast_node_free(left);
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_COMPARISON, op_token);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node; // для возможных цепочек сравнений (например: a = b = c)
    }

    return left;
}
