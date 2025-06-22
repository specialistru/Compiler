#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Проверка, является ли текущий токен логическим оператором
static int is_logical_operator(const token_t* token) {
    return (token->type == TOKEN_KEYWORD &&
            (strcmp(token->lexeme, "AND") == 0 ||
             strcmp(token->lexeme, "OR") == 0));
}

// Получить приоритет логических операторов
static int get_logical_precedence(const char* op) {
    if (strcmp(op, "AND") == 0) return 1;
    if (strcmp(op, "OR") == 0)  return 0;
    return -1;
}

// Парсинг логических выражений с учетом приоритетов
ast_node_t* parse_expression_logical(parser_context_t* ctx, int precedence) {
    ast_node_t* left = parse_expression_not(ctx); // обработка NOT

    while (ctx->current.type == TOKEN_KEYWORD && is_logical_operator(&ctx->current)) {
        const char* op = ctx->current.lexeme;
        int current_prec = get_logical_precedence(op);

        if (current_prec < precedence) break;

        token_t op_token = ctx->current;
        parser_next_token(ctx); // consume operator

        // Парсим правую часть
        ast_node_t* right = parse_expression_logical(ctx, current_prec + 1);

        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после логического оператора '%s'\n", op);
            return NULL;
        }

        // Создание узла логического выражения
        ast_node_t* node = ast_node_create(AST_EXPR_LOGICAL, op_token);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}
