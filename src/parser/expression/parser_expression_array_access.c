// parser_expression_array_access.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Прототип функции парсинга первичных выражений (идентификаторы, литералы и др.)
extern ast_node_t* parse_expression_primary(parser_context_t* ctx);

// Функция парсинга доступа к элементу массива, например: arr[expr]
ast_node_t* parse_expression_array_access(parser_context_t* ctx) {
    // Сначала парсим базовое выражение (обычно идентификатор массива)
    ast_node_t* base = parse_expression_primary(ctx);
    if (!base) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе базового выражения для доступа к массиву\n");
        return NULL;
    }

    // Пока следующий токен — это открывающая скобка '[' — парсим доступ к элементу массива
    while (ctx->current_token.type == TOKEN_LBRACKET) {
        parser_advance(ctx); // пропускаем '['

        // Парсим выражение внутри скобок (индекс массива)
        ast_node_t* index_expr = parse_expression_assignment(ctx);
        if (!index_expr) {
            ast_node_free(base);
            fprintf(stderr, "[PARSER ERROR] Ошибка при разборе индекса массива\n");
            return NULL;
        }

        // Ожидаем закрывающую скобку ']'
        if (ctx->current_token.type != TOKEN_RBRACKET) {
            ast_node_free(base);
            ast_node_free(index_expr);
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ']' после индекса массива\n");
            return NULL;
        }
        parser_advance(ctx); // пропускаем ']'

        // Создаем AST-узел для доступа к массиву
        ast_node_t* array_access_node = ast_node_create_array_access(base, index_expr);
        if (!array_access_node) {
            ast_node_free(base);
            ast_node_free(index_expr);
            fprintf(stderr, "[PARSER ERROR] Не удалось создать AST-узел для доступа к массиву\n");
            return NULL;
        }

        base = array_access_node; // базовое выражение теперь - доступ к элементу
    }

    return base;
}
