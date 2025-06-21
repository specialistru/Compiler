#include "parser_if_and_or.h"
#include "parser_if_not.h"
#include "parser_if_bracketed.h"

// Парсинг логических операций AND/OR в условиях IF
ast_node_t* parse_if_and_or(parser_t* parser) {
    // Парсим левый операнд: может быть NOT, скобка или простое условие
    ast_node_t *left = NULL;

    token_t *token = parser_peek_token(parser);
    if (!token) return NULL;

    if (token->type == TOKEN_NOT) {
        left = parse_if_not(parser);
    } else if (token->type == TOKEN_LPAREN) {
        left = parse_if_bracketed(parser);
    } else {
        left = parse_simple_condition(parser);
    }

    if (!left) {
        return NULL; // Не удалось распарсить левый операнд
    }

    while (1) {
        token_t *next = parser_peek_token(parser);
        if (!next) break;

        if (next->type != TOKEN_AND && next->type != TOKEN_OR) {
            break; // Логические операторы закончились
        }

        // Создаем узел бинарной операции AND/OR
        ast_node_t *op_node = ast_node_create(AST_EXPR_BINARY_OP, *next);
        parser_next_token(parser); // Съедаем AND/OR

        // Парсим правый операнд
        ast_node_t *right = NULL;
        token_t *lookahead = parser_peek_token(parser);
        if (!lookahead) {
            parse_if_error("Expected expression after AND/OR", parser->tokens);
            ast_node_free(op_node);
            ast_node_free(left);
            return NULL;
        }

        if (lookahead->type == TOKEN_NOT) {
            right = parse_if_not(parser);
        } else if (lookahead->type == TOKEN_LPAREN) {
            right = parse_if_bracketed(parser);
        } else {
            right = parse_simple_condition(parser);
        }

        if (!right) {
            parse_if_error("Expected expression after AND/OR", parser->tokens);
            ast_node_free(op_node);
            ast_node_free(left);
            return NULL;
        }

        // Строим дерево: оп_node -> left, right
        ast_node_add_child(op_node, left);
        ast_node_add_child(op_node, right);

        // Теперь op_node становится левым узлом для следующей итерации
        left = op_node;
    }

    return left;
}

// Вспомогательная функция парсинга простого условия
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
