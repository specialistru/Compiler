/*
#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>

// Разбор унарного выражения: например NOT expr, -expr, +expr
ast_node_t* parse_expression_unary(parser_context_t* ctx) {
    // Проверяем, является ли текущий токен унарным оператором
    if (ctx->current.type == TOKEN_OPERATOR) {
        // Примеры унарных операторов: NOT, -, +
        // Предполагаем, что у нас есть возможность проверить лексему
        if (ctx->current.lexeme == NULL) {
            fprintf(stderr, "[PARSER ERROR] Пустая лексема у оператора\n");
            return NULL;
        }

        const char* op = ctx->current.lexeme;

        if (strcmp(op, "NOT") == 0 || strcmp(op, "-") == 0 || strcmp(op, "+") == 0) {
            token_t op_token = ctx->current;
            parser_next_token(ctx);  // пропускаем оператор

            // Разбираем выражение справа от унарного оператора
            ast_node_t* operand = parse_expression_unary(ctx);
            if (!operand) {
                fprintf(stderr, "[PARSER ERROR] Ошибка разбора операнда унарного оператора %s\n", op);
                return NULL;
            }

            // Создаем узел AST для унарного оператора
            ast_node_t* node = ast_node_create(AST_UNARY_OP, op_token);
            ast_node_add_child(node, operand);
            return node;
        }
    }

    // Если не унарный оператор — разбираем дальше, например базовые выражения
    return parse_expression_primary(ctx);
}
*/

#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Разбор унарного выражения
ast_node_t* parse_expression_unary(parser_context_t* ctx) {
    token_t token = ctx->current;

    // Проверяем, является ли текущий токен унарным оператором
    if (token.type == TOKEN_SYMBOL && (strcmp(token.lexeme, "-") == 0 || strcmp(token.lexeme, "+") == 0)) {
        parser_next_token(ctx); // consume unary operator
        ast_node_t* operand = parse_expression_unary(ctx);
        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после унарного оператора '%s'\n", token.lexeme);
            return NULL;
        }
        ast_node_t* node = ast_node_create(AST_EXPR_UNARY_OP, token);
        ast_node_add_child(node, operand);
        return node;
    }

    if (token.type == TOKEN_KEYWORD && strcmp(token.lexeme, "NOT") == 0) {
        parser_next_token(ctx); // consume NOT
        ast_node_t* operand = parse_expression_unary(ctx);
        if (!operand) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось выражение после оператора NOT\n");
            return NULL;
        }
        ast_node_t* node = ast_node_create(AST_EXPR_UNARY_OP, token);
        ast_node_add_child(node, operand);
        return node;
    }

    // Если нет унарного оператора, переходим к разбору первичного выражения
    return parse_expression_primary(ctx);
}
