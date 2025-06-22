// parser_expression_complex.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Forward declaration: парсинг базового (примитивного) выражения
static ast_node_t* parse_primary_expression(parser_context_t* ctx);

// Функция для парсинга комплексного выражения с учетом приоритетов операторов
ast_node_t* parse_expression_complex(parser_context_t* ctx) {
    // Используем рекурсивный парсинг с разбором бинарных операторов по приоритету
    return parse_binary_expression(ctx, 0);
}

// Парсинг бинарного выражения с учетом приоритета
// min_precedence - минимальный приоритет оператора, который мы принимаем на текущем уровне
ast_node_t* parse_binary_expression(parser_context_t* ctx, int min_precedence) {
    ast_node_t* left = parse_primary_expression(ctx);
    if (!left) return NULL;

    while (is_binary_operator(ctx->current_token.type) &&
           get_operator_precedence(ctx->current_token.type) >= min_precedence) {
        token_t op = ctx->current_token;
        int precedence = get_operator_precedence(op.type);
        int next_min_precedence = precedence + 1;

        parser_advance(ctx);  // Сдвигаемся после оператора

        ast_node_t* right = parse_binary_expression(ctx, next_min_precedence);
        if (!right) {
            ast_node_free(left);
            return NULL;
        }

        // Создаем узел бинарного оператора
        ast_node_t* new_node = ast_node_create_binary(op, left, right);
        if (!new_node) {
            ast_node_free(left);
            ast_node_free(right);
            return NULL;
        }

        left = new_node;
    }

    return left;
}

// Парсинг базового выражения (переменные, литералы, скобки)
static ast_node_t* parse_primary_expression(parser_context_t* ctx) {
    switch (ctx->current_token.type) {
        case TOKEN_IDENTIFIER:
            return parse_expression_identifier(ctx);
        case TOKEN_LITERAL:
            return parse_expression_literal(ctx);
        case TOKEN_LPAREN:
            return parse_expression_bracket(ctx);
        // Добавьте другие типы базовых выражений, если необходимо
        default:
            fprintf(stderr, "[PARSER ERROR] Неожиданный токен в базовом выражении: %s\n", ctx->current_token.lexeme);
            return NULL;
    }
}

// Вспомогательные функции (предполагаются где-то определены):

// Проверяет, является ли токен бинарным оператором
int is_binary_operator(token_type_t type) {
    // Пример: +, -, *, /, &&, ||, ==, != и т.д.
    switch (type) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        case TOKEN_MUL:
        case TOKEN_DIV:
        case TOKEN_AND:
        case TOKEN_OR:
        case TOKEN_EQ:
        case TOKEN_NEQ:
        case TOKEN_LT:
        case TOKEN_GT:
        case TOKEN_LEQ:
        case TOKEN_GEQ:
            return 1;
        default:
            return 0;
    }
}

// Возвращает приоритет оператора для разборки с учетом правил языка
int get_operator_precedence(token_type_t type) {
    switch (type) {
        case TOKEN_OR:      return 1;
        case TOKEN_AND:     return 2;
        case TOKEN_EQ:
        case TOKEN_NEQ:     return 3;
        case TOKEN_LT:
        case TOKEN_GT:
        case TOKEN_LEQ:
        case TOKEN_GEQ:     return 4;
        case TOKEN_PLUS:
        case TOKEN_MINUS:   return 5;
        case TOKEN_MUL:
        case TOKEN_DIV:     return 6;
        default:            return 0;
    }
}
