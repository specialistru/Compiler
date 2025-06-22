// parser_expression_assignment.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Прототип функции для парсинга более приоритетных выражений
extern ast_node_t* parse_expression_logical(parser_context_t* ctx);

// Функция парсинга выражения с оператором присваивания
ast_node_t* parse_expression_assignment(parser_context_t* ctx) {
    // Сначала парсим левую часть (идентификатор, переменную и т.д.)
    ast_node_t* left = parse_expression_logical(ctx);
    if (!left) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе левой части присваивания\n");
        return NULL;
    }

    // Проверяем наличие оператора присваивания '='
    if (ctx->current_token.type != TOKEN_ASSIGN) {
        // Оператор присваивания отсутствует — возвращаем левую часть как есть
        return left;
    }

    // Переходим к следующему токену после '='
    parser_advance(ctx);

    // Парсим правую часть присваивания (выражение)
    ast_node_t* right = parse_expression_assignment(ctx); 
    // Рекурсивный вызов для поддержки цепочек присваивания (a = b = c)

    if (!right) {
        ast_node_free(left);
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе правой части присваивания\n");
        return NULL;
    }

    // Создаем AST-узел для присваивания
    ast_node_t* node = ast_node_create_assignment(left, right);
    if (!node) {
        ast_node_free(left);
        ast_node_free(right);
        fprintf(stderr, "[PARSER ERROR] Не удалось создать AST-узел для присваивания\n");
        return NULL;
    }

    return node;
}
