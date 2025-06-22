/*
#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для определения приоритета оператора
static int get_precedence(const char* op) {
    if (strcmp(op, "OR") == 0) return 1;
    if (strcmp(op, "AND") == 0) return 2;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 3;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 4;
    return 0;  // неизвестный оператор
}

// Вспомогательная функция для разбора базового выражения (операнд)
static ast_node_t* parse_expression_primary(parser_context_t* ctx);

// Рекурсивный разбор бинарных выражений с учетом приоритета
static ast_node_t* parse_binary_op_rhs(parser_context_t* ctx, int expr_prec, ast_node_t* lhs) {
    while (1) {
        if (ctx->current.type != TOKEN_OPERATOR) {
            return lhs;
        }

        const char* op = ctx->current.lexeme;
        int token_prec = get_precedence(op);

        if (token_prec < expr_prec) {
            return lhs;
        }

        token_t op_token = ctx->current;
        parser_next_token(ctx);  // пропускаем оператор

        ast_node_t* rhs = parse_expression_primary(ctx);
        if (!rhs) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после оператора %s\n", op);
            return NULL;
        }

        // Проверка следующего оператора на приоритет
        if (ctx->current.type == TOKEN_OPERATOR) {
            int next_prec = get_precedence(ctx->current.lexeme);
            if (token_prec < next_prec) {
                rhs = parse_binary_op_rhs(ctx, token_prec + 1, rhs);
                if (!rhs) return NULL;
            }
        }

        // Создаем узел AST для бинарного оператора
        ast_node_t* new_lhs = ast_node_create(AST_BINARY_OP, op_token);
        ast_node_add_child(new_lhs, lhs);
        ast_node_add_child(new_lhs, rhs);

        lhs = new_lhs;
    }
}

// Главная функция разбора бинарного выражения
ast_node_t* parse_expression_binary(parser_context_t* ctx) {
    ast_node_t* lhs = parse_expression_primary(ctx);
    if (!lhs) {
        return NULL;
    }
    return parse_binary_op_rhs(ctx, 0, lhs);
}
*/

#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Предопределение приоритетов операций
int get_operator_precedence(const char* op) {
    if (strcmp(op, "=") == 0 || strcmp(op, "<>") == 0 || strcmp(op, "!=") == 0 ||
        strcmp(op, "<") == 0 || strcmp(op, ">") == 0 ||
        strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) {
        return 1;  // операторы сравнения
    } else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        return 2;
    } else if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        return 3;
    }
    return 0; // неизвестный оператор
}

// Проверка, является ли символ бинарным оператором
int is_binary_operator(const token_t* token) {
    if (token->type != TOKEN_SYMBOL) return 0;
    const char* op = token->lexeme;
    return (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
            strcmp(op, "*") == 0 || strcmp(op, "/") == 0 ||
            strcmp(op, "=") == 0 || strcmp(op, "<") == 0 ||
            strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 ||
            strcmp(op, ">=") == 0 || strcmp(op, "<>") == 0 || strcmp(op, "!=") == 0);
}

// Основной парсер бинарных выражений с учетом приоритета
ast_node_t* parse_expression_binary(parser_context_t* ctx, int precedence) {
    ast_node_t* left = parse_expression_primary(ctx);  // базовое выражение

    while (is_binary_operator(&ctx->current)) {
        const char* op = ctx->current.lexeme;
        int current_prec = get_operator_precedence(op);

        if (current_prec < precedence) break;

        token_t op_token = ctx->current;
        parser_next_token(ctx);  // consume operator

        // Парсим правую часть с более высоким приоритетом
        ast_node_t* right = parse_expression_binary(ctx, current_prec + 1);

        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось правое выражение после бинарного оператора '%s'\n", op);
            return NULL;
        }

        // Создаем узел бинарного выражения
        ast_node_t* node = ast_node_create(AST_EXPR_BINARY, op_token);
        ast_node_add_child(node, left);
        ast_node_add_child(node, right);
        left = node;
    }

    return left;
}
