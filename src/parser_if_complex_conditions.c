#include "parser_if.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для парсинга выражений с поддержкой скобок и логических операторов
// Пример: (a = b OR c = d) AND NOT e = f
ast_node_t* parse_complex_condition(parser_t* parser) {
    // Идея: рекурсивный спуск с поддержкой скобок
    // Простая версия:
    ast_node_t* node = NULL;

    if (parser_match_token(parser, TOKEN_LPAREN)) {
        // Вход в скобки
        node = parse_complex_condition(parser);
        if (!parser_match_token(parser, TOKEN_RPAREN)) {
            parser_error(parser, "Expected closing parenthesis");
            ast_node_free(node);
            return NULL;
        }
    } else if (parser_peek_token(parser)->type == TOKEN_NOT) {
        parser_next_token(parser);
        ast_node_t* operand = parse_complex_condition(parser);
        if (!operand) return NULL;
        node = ast_node_create(AST_EXPR_UNARY_OP, parser->current_token);
        node->token.lexeme = strdup("NOT");
        ast_node_add_child(node, operand);
    } else {
        // Базовое условие (идентификатор, оператор, значение)
        node = parse_simple_condition(parser);
        if (!node) return NULL;
    }

    // Обработка AND/OR после условия
    while (parser_peek_token(parser)->type == TOKEN_AND || parser_peek_token(parser)->type == TOKEN_OR) {
        token_t op_token = parser_next_token(parser);
        ast_node_t* right = parse_complex_condition(parser);
        if (!right) {
            ast_node_free(node);
            return NULL;
        }

        ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
        ast_node_add_child(bin_op, node);
        ast_node_add_child(bin_op, right);
        node = bin_op;
    }

    return node;
}

// Здесь parse_simple_condition — парсит простое сравнение: идентификатор OP значение
// Остальной код остался без изменений
