#include "parser_if_not.h"
#include "parser_if_logical_ops.h" // для поддержки AND/OR
#include "parser_if_bracketed.h"   // для поддержки скобок

// Парсинг условия IF с оператором NOT
ast_node_t* parse_if_not(parser_t* parser) {
    token_t *token = parser_peek_token(parser);

    if (!token || token->type != TOKEN_NOT) {
        return NULL; // NOT нет, обработать дальше другим парсером
    }

    // Создаем AST узел для оператора NOT
    ast_node_t *not_node = ast_node_create(AST_EXPR_UNARY_OP, *token);

    // Съедаем токен NOT
    parser_next_token(parser);

    // Парсим выражение после NOT (может быть скобка или простое условие)
    ast_node_t *operand = NULL;

    token_t *next_token = parser_peek_token(parser);
    if (next_token && next_token->type == TOKEN_LPAREN) {
        // Сложное условие в скобках
        operand = parse_if_bracketed(parser);
    } else {
        // Пробуем распарсить логические операции или простое условие
        operand = parse_if_logical_ops(parser);
        if (!operand) {
            // Попытка парсинга простого условия (идентификатор, литерал и т.п.)
            operand = parse_simple_condition(parser);
            if (!operand) {
                parse_if_error("Expected expression after NOT", parser->tokens);
                ast_node_free(not_node);
                return NULL;
            }
        }
    }

    // Присоединяем операнд к узлу NOT
    ast_node_add_child(not_node, operand);

    return not_node;
}

// Вспомогательная функция парсинга простого условия (идентификатор, литерал, сравнение и т.д.)
ast_node_t* parse_simple_condition(parser_t* parser) {
    token_t *token = parser_peek_token(parser);
    if (!token) return NULL;

    if (token->type == TOKEN_IDENTIFIER || token->type == TOKEN_LITERAL) {
        ast_node_t *node = ast_node_create(AST_EXPR_LITERAL, *token);
        parser_next_token(parser);
        return node;
    }
    return NULL;
}
