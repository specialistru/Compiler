// parser_loop_loop.c
#include "parser_loop.h"
#include "parser_utils.h"
#include <stdio.h>

// Парсинг конструкции LOOP ... ENDLOOP.
// Пример:
// LOOP.
//    ... тело цикла ...
// ENDLOOP.

ast_node_t* parse_loop_loop(parser_context_t* ctx) {
    // Проверяем ключевое слово LOOP
    if (!parser_match_keyword(ctx, "LOOP")) {
        parser_error(ctx, "Ожидалось ключевое слово LOOP");
        return NULL;
    }

    ast_node_t* loop_node = ast_node_create(AST_LOOP_LOOP, ctx->previous_token);

    // Обязательная точка после LOOP
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после LOOP");
        ast_node_free(loop_node);
        return NULL;
    }

    // Парсим тело цикла, пока не встретим ENDLOOP или EOF
    while (!parser_check_keyword(ctx, "ENDLOOP") && ctx->current_token.type != TOKEN_EOF) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parser_error(ctx, "Ошибка при разборе тела цикла LOOP");
            ast_node_free(loop_node);
            return NULL;
        }
        ast_node_add_child(loop_node, stmt);
    }

    // Проверяем наличие ключевого слова ENDLOOP
    if (!parser_match_keyword(ctx, "ENDLOOP")) {
        parser_error(ctx, "Ожидалось ключевое слово ENDLOOP");
        ast_node_free(loop_node);
        return NULL;
    }

    // Обязательная точка после ENDLOOP
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDLOOP");
        ast_node_free(loop_node);
        return NULL;
    }

    return loop_node;
}
