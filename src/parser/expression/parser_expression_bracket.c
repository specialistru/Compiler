// parser_expression_bracket.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг выражения в круглых скобках: ( expression )
ast_node_t* parse_expression_bracket(parser_context_t* ctx) {
    if (ctx->current_token.type != TOKEN_LPAREN) {
        fprintf(stderr, "[PARSER ERROR] Ожидался '(' в начале скобочного выражения, но получено: %s\n", ctx->current_token.lexeme);
        return NULL;
    }

    // Сдвигаем токен после '('
    parser_advance(ctx);

    // Парсим вложенное выражение
    ast_node_t* expr = parse_expression(ctx);
    if (!expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе вложенного выражения в скобках\n");
        return NULL;
    }

    // Проверяем наличие закрывающей скобки ')'
    if (ctx->current_token.type != TOKEN_RPAREN) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась ')' после скобочного выражения\n");
        ast_node_free(expr);
        return NULL;
    }

    // Сдвигаем токен после ')'
    parser_advance(ctx);

    // Возвращаем узел вложенного выражения
    // Можно вернуть expr напрямую, т.к. скобки не меняют структуру AST
    return expr;
}
