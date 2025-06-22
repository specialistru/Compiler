#include "parser_if_condition.h"
#include "parser_if_logical_ops.h"
#include "lexer.h"
#include "ast.h"

// Прототипы вспомогательных функций
static ast_node_t* parse_simple_condition(token_stream_t *tokens);

// Парсинг условия IF (с поддержкой скобок и NOT)
ast_node_t* parse_if_condition(token_stream_t *tokens) {
    // Пример простой реализации с поддержкой NOT и скобок
    if (tokens->current_token.type == TOKEN_NOT) {
        token_advance(tokens);
        ast_node_t *not_node = ast_node_create(AST_EXPR_UNARY_OP, tokens->current_token);
        ast_node_t *cond = parse_if_condition(tokens);
        if (!cond) return NULL;
        ast_node_add_child(not_node, cond);
        return not_node;
    }
    if (tokens->current_token.type == TOKEN_LPAREN) {
        token_advance(tokens);
        ast_node_t *cond = parse_if_condition(tokens);
        if (!cond) return NULL;
        if (tokens->current_token.type != TOKEN_RPAREN) {
            // Ошибка: ожидалась ')'
            return NULL;
        }
        token_advance(tokens);
        return cond;
    }
    return parse_simple_condition(tokens);
}

// Простое условие, например, сравнение или идентификатор
static ast_node_t* parse_simple_condition(token_stream_t *tokens) {
    // TODO: реализовать парсинг простого условия: идентификатор, литерал, сравнения
    // Заготовка:
    ast_node_t *node = ast_node_create(AST_EXPR_IDENTIFIER, tokens->current_token);
    token_advance(tokens);
    return node;
}
