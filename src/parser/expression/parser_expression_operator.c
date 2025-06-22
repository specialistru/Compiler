// parser_expression_operator.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для определения приоритета оператора
static int operator_precedence(token_t op) {
    // Пример приоритетов, чем больше — тем выше
    switch (op.type) {
        case TOKEN_OPERATOR:
            if (op.lexeme[0] == '+' || op.lexeme[0] == '-')
                return 1;
            if (op.lexeme[0] == '*' || op.lexeme[0] == '/')
                return 2;
            if (op.lexeme[0] == '^')
                return 3;
            if (op.lexeme[0] == '=' || op.lexeme[0] == '<' || op.lexeme[0] == '>')
                return 0; // пример приоритетов для сравнений
            break;
        default:
            return -1;
    }
    return -1;
}

// Основная функция для парсинга выражений с операторами
ast_node_t* parse_expression_operator(parser_context_t* ctx, int min_prec) {
    // Разбор левого операнда
    ast_node_t* left = parse_expression_operand(ctx);
    if (!left) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе левого операнда оператора\n");
        return NULL;
    }

    while (ctx->current_token.type == TOKEN_OPERATOR) {
        token_t op = ctx->current_token;
        int prec = operator_precedence(op);
        if (prec < min_prec) {
            break;
        }
        parser_advance(ctx);

        // Рекурсивно парсим правый операнд с учетом приоритета
        ast_node_t* right = parse_expression_operator(ctx, prec + 1);
        if (!right) {
            ast_node_free(left);
            fprintf(stderr, "[PARSER ERROR] Ошибка при разборе правого операнда оператора\n");
            return NULL;
        }

        // Формируем узел AST для бинарного оператора
        ast_node_t* op_node = ast_node_create(AST_BINARY_OPERATOR, op);
        ast_node_add_child(op_node, left);
        ast_node_add_child(op_node, right);

        // Теперь этот оператор становится левым выражением для следующего шага
        left = op_node;
    }

    return left;
}
