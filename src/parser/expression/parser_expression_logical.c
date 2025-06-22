/*
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

#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Проверка на логические операторы
static int is_logical_operator(const token_t* token) {
    return token->type == TOKEN_KEYWORD &&
           (strcmp(token->lexeme, "AND") == 0 || strcmp(token->lexeme, "OR") == 0);
}

// Парсинг базового условия (фактор или выражение в скобках)
static ast_node_t* parse_logical_factor(parser_context_t* ctx) {
    if (parser_match(ctx, TOKEN_SYMBOL, "(")) {
        ast_node_t* expr = parse_expression_logical(ctx);
        if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ')' после логического выражения\n");
            ast_node_free(expr);
            return NULL;
        }
        return expr;
    }

    // Простейшее выражение (например, сравнение или идентификатор)
    return parse_expression_term(ctx);
}

// Парсинг логического выражения с учетом приоритета (AND выше OR)
ast_node_t* parse_expression_logical(parser_context_t* ctx) {
    ast_node_t* left = parse_logical_factor(ctx);
    if (!left) return NULL;

    while (is_logical_operator(&ctx->current)) {
        token_t op = ctx->current;
        parser_next_token(ctx);

        ast_node_t* right = parse_logical_factor(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось логическое выражение после '%s'\n", op.lexeme);
            ast_node_free(left);
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_LOGICAL_OP, op);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}
*/

// parser_expression_logical.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для разбора логического выражения
// Поддерживает операторы AND, OR, NOT с правильным приоритетом

static ast_node_t* parse_logical_not(parser_context_t* ctx);
static ast_node_t* parse_logical_and(parser_context_t* ctx);
static ast_node_t* parse_logical_or(parser_context_t* ctx);

// Парсим выражение с оператором NOT
static ast_node_t* parse_logical_not(parser_context_t* ctx) {
    if (parser_match(ctx, TOKEN_OPERATOR, "NOT")) {
        token_t op_token = ctx->previous;
        ast_node_t* operand = parse_logical_not(ctx);  // Рекурсивно парсим дальше
        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после NOT\n");
            exit(EXIT_FAILURE);
        }
        ast_node_t* node = ast_node_create(AST_EXPR_UNARY_OP, op_token);
        ast_node_add_child(node, operand);
        return node;
    }
    // Если NOT нет, пытаемся распарсить базовое логическое выражение (например, скобки, переменные)
    return parse_expression_primary(ctx);
}

// Парсим выражение с операторами AND
static ast_node_t* parse_logical_and(parser_context_t* ctx) {
    ast_node_t* left = parse_logical_not(ctx);
    if (!left) return NULL;

    while (parser_match(ctx, TOKEN_OPERATOR, "AND")) {
        token_t op_token = ctx->previous;
        ast_node_t* right = parse_logical_not(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после AND\n");
            exit(EXIT_FAILURE);
        }
        ast_node_t* node = ast_node_create(AST_EXPR_BINARY_OP, op_token);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;  // Обновляем левый операнд для дальнейших цепочек
    }

    return left;
}

// Парсим выражение с операторами OR
static ast_node_t* parse_logical_or(parser_context_t* ctx) {
    ast_node_t* left = parse_logical_and(ctx);
    if (!left) return NULL;

    while (parser_match(ctx, TOKEN_OPERATOR, "OR")) {
        token_t op_token = ctx->previous;
        ast_node_t* right = parse_logical_and(ctx);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после OR\n");
            exit(EXIT_FAILURE);
        }
        ast_node_t* node = ast_node_create(AST_EXPR_BINARY_OP, op_token);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}

// Внешняя функция для разбора логических выражений
ast_node_t* parse_expression_logical(parser_context_t* ctx) {
    return parse_logical_or(ctx);
}
