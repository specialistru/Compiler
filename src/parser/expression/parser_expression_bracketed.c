#include "parser_expression.h"
#include <stdio.h>
#include <stdlib.h>

// Разбор выражения в круглых скобках: (expression)
// Если текущий токен не '(', возвращаем ошибку.
ast_node_t* parse_expression_bracketed(parser_context_t* ctx) {
    // Проверяем, что текущий токен - открывающая скобка '('
    if (ctx->current.type != TOKEN_SYMBOL || ctx->current.symbol != '(') {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '(' для начала скобочного выражения, но получен другой токен\n");
        return NULL;
    }

    // Пропускаем токен '('
    parser_next_token(ctx);

    // Рекурсивно парсим выражение внутри скобок
    ast_node_t* inner_expr = parse_expression(ctx);
    if (!inner_expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе выражения внутри скобок\n");
        return NULL;
    }

    // Проверяем наличие закрывающей скобки ')'
    if (ctx->current.type != TOKEN_SYMBOL || ctx->current.symbol != ')') {
        fprintf(stderr, "[PARSER ERROR] Ожидалась ')' после выражения в скобках\n");
        ast_node_free(inner_expr);  // освобождаем память
        return NULL;
    }

    // Пропускаем токен ')'
    parser_next_token(ctx);

    // Возвращаем разобранное внутреннее выражение
    return inner_expr;
}
