/*
#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Парсинг выражений с оператором NOT
ast_node_t* parse_expression_not(parser_context_t* ctx) {
    if (ctx->current.type == TOKEN_KEYWORD && strcmp(ctx->current.lexeme, "NOT") == 0) {
        token_t not_token = ctx->current;
        parser_next_token(ctx); // consume NOT

        ast_node_t* operand = parse_expression_comparison(ctx); // например: NOT a = 1

        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после 'NOT'\n");
            return NULL;
        }

        ast_node_t* node = ast_node_create(AST_EXPR_NOT, not_token);
        ast_node_add_child(node, operand);
        return node;
    }

    return parse_expression_comparison(ctx); // без NOT — обычное сравнение
}
*/

#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Проверка, является ли токен ключевым словом NOT
static int is_not_operator(const token_t* token) {
    return token->type == TOKEN_KEYWORD && strcmp(token->lexeme, "NOT") == 0;
}

// Парсинг выражения с поддержкой оператора NOT
ast_node_t* parse_expression_not(parser_context_t* ctx) {
    if (is_not_operator(&ctx->current)) {
        token_t not_token = ctx->current;
        parser_next_token(ctx);

        // Рекурсивно парсим фактор после NOT (например, идентификатор или выражение в скобках)
        ast_node_t* operand = parse_expression_not(ctx);
        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после оператора NOT\n");
            return NULL;
        }

        // Создаем AST узел для NOT
        ast_node_t* not_node = ast_node_create(AST_EXPR_LOGICAL_NOT, not_token);
        ast_node_add_child(not_node, operand);
        return not_node;
    }

    // Если NOT не найден — передаём парсинг дальше
    return parse_expression_logical(ctx);
}
