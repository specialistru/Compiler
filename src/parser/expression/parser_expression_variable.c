// parser_expression_variable.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Функция парсинга переменной в выражении
ast_node_t* parse_expression_variable(parser_context_t* ctx) {
    if (ctx->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор переменной, но получено: %s\n", ctx->current_token.lexeme);
        return NULL;
    }

    // Создаем AST узел для переменной
    ast_node_t* var_node = ast_node_create(AST_VARIABLE, ctx->current_token);
    parser_advance(ctx); // Сдвигаем токен

    // Возможен разбор сложных переменных с индексами или полями (например, obj.field или arr[3])
    while (ctx->current_token.type == TOKEN_DOT || ctx->current_token.type == TOKEN_LBRACKET) {
        if (ctx->current_token.type == TOKEN_DOT) {
            parser_advance(ctx);
            if (ctx->current_token.type != TOKEN_IDENTIFIER) {
                fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор после '.'\n");
                ast_node_free(var_node);
                return NULL;
            }
            // Создаем узел поля
            ast_node_t* field_node = ast_node_create(AST_FIELD_ACCESS, ctx->current_token);
            parser_advance(ctx);

            // Добавляем в древовидную структуру: поле как ребенок переменной
            ast_node_add_child(var_node, field_node);
            var_node = field_node; // текущий узел - новое поле
        }
        else if (ctx->current_token.type == TOKEN_LBRACKET) {
            parser_advance(ctx);
            // Парсим выражение индекса
            ast_node_t* index_expr = parse_expression(ctx);
            if (!index_expr) {
                ast_node_free(var_node);
                fprintf(stderr, "[PARSER ERROR] Ошибка при разборе индекса массива\n");
                return NULL;
            }
            if (ctx->current_token.type != TOKEN_RBRACKET) {
                fprintf(stderr, "[PARSER ERROR] Ожидался ']' после индекса\n");
                ast_node_free(var_node);
                ast_node_free(index_expr);
                return NULL;
            }
            parser_advance(ctx);

            // Создаем узел доступа по индексу
            ast_node_t* index_node = ast_node_create(AST_INDEX_ACCESS, ctx->current_token);
            ast_node_add_child(index_node, var_node);
            ast_node_add_child(index_node, index_expr);

            var_node = index_node; // текущий узел — индексированный доступ
        }
    }

    return var_node;
}
