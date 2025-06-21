#include "parser_if_complex_conditions.h"
#include "parser_if.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для парсинга простого условия или вложенного выражения в скобках
static ast_node_t* parse_condition_atom(parser_t* parser);

// Парсинг сложных условий с приоритетом AND > OR
ast_node_t* parse_if_complex_conditions(parser_t* parser) {
    ast_node_t* left = parse_condition_atom(parser);
    if (!left) return NULL;

    while (true) {
        token_t* tok = parser_peek_token(parser);
        if (!tok) break;

        // Проверяем логический оператор AND/OR
        if (tok->type == TOKEN_AND || tok->type == TOKEN_OR) {
            token_t op_token = *tok;
            parser_next_token(parser); // съесть AND/OR

            ast_node_t* right = parse_condition_atom(parser);
            if (!right) {
                parse_if_error("Expected condition after AND/OR", parser->tokens);
                ast_node_free(left);
                return NULL;
            }

            ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
            ast_node_add_child(bin_op, left);
            ast_node_add_child(bin_op, right);
            left = bin_op; // новый левый узел
        } else {
            break;
        }
    }

    return left;
}

static ast_node_t* parse_condition_atom(parser_t* parser) {
    token_t* tok = parser_peek_token(parser);
    if (!tok) return NULL;

    // Обработка NOT
    if (tok->type == TOKEN_NOT) {
        token_t not_token = *tok;
        parser_next_token(parser);
        ast_node_t* operand = parse_condition_atom(parser);
        if (!operand) {
            parse_if_error("Expected condition after NOT", parser->tokens);
            return NULL;
        }
        ast_node_t* unary = ast_node_create(AST_EXPR_UNARY_OP, not_token);
        ast_node_add_child(unary, operand);
        return unary;
    }

    // Обработка скобок '(' <условие> ')'
    if (tok->type == TOKEN_LPAREN) {
        parser_next_token(parser); // съесть '('
        ast_node_t* expr = parse_if_complex_conditions(parser);
        if (!expr) {
            parse_if_error("Expected expression after '('", parser->tokens);
            return NULL;
        }
        tok = parser_peek_token(parser);
        if (!tok || tok->type != TOKEN_RPAREN) {
            parse_if_error("Expected ')' to close '('", parser->tokens);
            ast_node_free(expr);
            return NULL;
        }
        parser_next_token(parser); // съесть ')'
        return expr;
    }

    // Простое условие (например, идентификатор или литерал)
    if (tok->type == TOKEN_IDENTIFIER || tok->type == TOKEN_LITERAL) {
        token_t simple_token = *tok;
        parser_next_token(parser);
        return ast_node_create(AST_EXPR_IDENTIFIER, simple_token);
    }

    // Если не распознано
    parse_if_error("Unexpected token in condition", parser->tokens);
    return NULL;
}

// Функция для вывода ошибки парсинга условия IF
void parse_if_error(const char *message, token_stream_t *tokens) {
    fprintf(stderr, "Parse error in IF condition: %s\n", message);
    // Можно дополнительно вывести позицию в tokens
}
