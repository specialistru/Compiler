#include "parser_call.h"
#include <stdio.h>

// Парсинг простого вызова функции: CALL FUNCTION 'func_name'.
ast_node_t* parse_call_simple(parser_context_t* ctx) {
    // Проверяем, что следующий токен — ключевое слово FUNCTION
    if (!parser_match(ctx, TOKEN_KEYWORD, "FUNCTION")) {
        parse_call_error("Ожидалось ключевое слово FUNCTION после CALL", ctx);
        return NULL;
    }

    // Ожидаем строковый литерал с именем функции
    if (ctx->current.type != TOKEN_STRING) {
        parse_call_error("Ожидалось имя функции в кавычках", ctx);
        return NULL;
    }
    token_t func_name_token = ctx->current;
    parser_advance(ctx);

    // Создаем AST узел для вызова функции
    ast_node_t* call_node = ast_node_create(AST_CALL_FUNCTION, func_name_token);

    // Проверяем наличие точки в конце
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parse_call_error("Ожидалась точка в конце вызова функции", ctx);
        ast_node_destroy(call_node);
        return NULL;
    }

    return call_node;
}
