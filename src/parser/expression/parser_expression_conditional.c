// parser_expression_conditional.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Прототип функции для парсинга базового выражения (например, логического)
extern ast_node_t* parse_expression_logical(parser_context_t* ctx);

// Функция парсинга условного (тернарного) выражения
ast_node_t* parse_expression_conditional(parser_context_t* ctx) {
    // Сначала парсим логическое или другое базовое выражение
    ast_node_t* condition = parse_expression_logical(ctx);
    if (!condition) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе условия тернарного выражения\n");
        return NULL;
    }

    // Проверяем наличие знака '?'
    if (ctx->current_token.type != TOKEN_QUESTION_MARK) {
        // Нет условного оператора — возвращаем просто условие
        return condition;
    }

    // Перейти после '?'
    parser_advance(ctx);

    // Парсим выражение для true-ветки
    ast_node_t* true_expr = parse_expression_logical(ctx);
    if (!true_expr) {
        ast_node_free(condition);
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе true-ветки тернарного выражения\n");
        return NULL;
    }

    // Проверяем наличие ':'
    if (ctx->current_token.type != TOKEN_COLON) {
        ast_node_free(condition);
        ast_node_free(true_expr);
        fprintf(stderr, "[PARSER ERROR] Ожидался ':' после true-ветки тернарного выражения\n");
        return NULL;
    }

    // Перейти после ':'
    parser_advance(ctx);

    // Парсим выражение для false-ветки
    ast_node_t* false_expr = parse_expression_logical(ctx);
    if (!false_expr) {
        ast_node_free(condition);
        ast_node_free(true_expr);
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе false-ветки тернарного выражения\n");
        return NULL;
    }

    // Создаем AST-узел для условного выражения
    ast_node_t* node = ast_node_create_conditional(condition, true_expr, false_expr);
    if (!node) {
        ast_node_free(condition);
        ast_node_free(true_expr);
        ast_node_free(false_expr);
        fprintf(stderr, "[PARSER ERROR] Не удалось создать AST-узел для тернарного выражения\n");
        return NULL;
    }

    return node;
}
