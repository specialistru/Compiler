// parser_expression_ternary.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для парсинга тернарного выражения:
// Ожидает, что текущий токен уже указывает на условие (expression)
// Формат: condition ? expr_true : expr_false
ast_node_t* parse_expression_ternary(parser_context_t* ctx) {
    // Парсим условие (левый операнд)
    ast_node_t* condition = parse_expression(ctx);
    if (!condition) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе условия тернарного оператора\n");
        return NULL;
    }

    // Проверяем наличие символа '?'
    if (ctx->current_token.type != TOKEN_SYMBOL || ctx->current_token.lexeme[0] != '?') {
        // Нет тернарного оператора, просто возвращаем условие (не тернарное выражение)
        return condition;
    }

    parser_advance(ctx); // пропускаем '?'

    // Парсим выражение для истинного результата
    ast_node_t* true_expr = parse_expression(ctx);
    if (!true_expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе true-ветви тернарного оператора\n");
        ast_node_free(condition);
        return NULL;
    }

    // Проверяем наличие символа ':'
    if (ctx->current_token.type != TOKEN_SYMBOL || ctx->current_token.lexeme[0] != ':') {
        fprintf(stderr, "[PARSER ERROR] Ожидался ':' в тернарном операторе\n");
        ast_node_free(condition);
        ast_node_free(true_expr);
        return NULL;
    }

    parser_advance(ctx); // пропускаем ':'

    // Парсим выражение для ложного результата
    ast_node_t* false_expr = parse_expression(ctx);
    if (!false_expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе false-ветви тернарного оператора\n");
        ast_node_free(condition);
        ast_node_free(true_expr);
        return NULL;
    }

    // Создаем узел AST для тернарного оператора
    ast_node_t* ternary_node = ast_node_create(AST_TERNARY_OPERATOR, token_create("?"));

    // Добавляем дочерние узлы: условие, true_expr, false_expr
    ast_node_add_child(ternary_node, condition);
    ast_node_add_child(ternary_node, true_expr);
    ast_node_add_child(ternary_node, false_expr);

    return ternary_node;
}
