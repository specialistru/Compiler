#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Вспомогательная функция: проверка оператора +, -, *, /
static int is_arithmetic_operator(const token_t *token) {
    return token->type == TOKEN_SYMBOL &&
           (strcmp(token->lexeme, "+") == 0 ||
            strcmp(token->lexeme, "-") == 0 ||
            strcmp(token->lexeme, "*") == 0 ||
            strcmp(token->lexeme, "/") == 0);
}

// Парсинг факторов (чисел, идентификаторов, скобок)
static ast_node_t* parse_factor(parser_context_t* ctx) {
    return parse_expression_term(ctx);
}

// Парсинг членов: фактор [*|/] фактор ...
static ast_node_t* parse_term(parser_context_t* ctx) {
    ast_node_t* left = parse_factor(ctx);
    if (!left) return NULL;

    while (ctx->current.type == TOKEN_SYMBOL &&
           (strcmp(ctx->current.lexeme, "*") == 0 || strcmp(ctx->current.lexeme, "/") == 0)) {
        token_t op = ctx->current;
        parser_next_token(ctx);

        ast_node_t* right = parse_factor(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после оператора '%s'\n", op.lexeme);
            ast_node_free(left);
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_BINARY_OP, op);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}

// Основная функция: парсинг выражения с операциями + и -
ast_node_t* parse_expression_arithmetic(parser_context_t* ctx) {
    ast_node_t* left = parse_term(ctx);
    if (!left) return NULL;

    while (ctx->current.type == TOKEN_SYMBOL &&
           (strcmp(ctx->current.lexeme, "+") == 0 || strcmp(ctx->current.lexeme, "-") == 0)) {
        token_t op = ctx->current;
        parser_next_token(ctx);

        ast_node_t* right = parse_term(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после оператора '%s'\n", op.lexeme);
            ast_node_free(left);
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_BINARY_OP, op);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}
