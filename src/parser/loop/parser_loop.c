#include "parser_loop.h"
#include "parser_loop_for.h"
#include "parser_loop_while.h"
#include "parser_loop_do_while.h"
#include <stdio.h>

// Основная функция разбора циклов
ast_node_t* parse_loop(parser_context_t* ctx) {
    // Проверяем, какой именно цикл ожидается, и вызываем соответствующую функцию
    if (ctx->current.type == TOKEN_KEYWORD) {
        if (strcmp(ctx->current.lexeme, "FOR") == 0) {
            return parse_loop_for(ctx);
        } else if (strcmp(ctx->current.lexeme, "WHILE") == 0) {
            return parse_loop_while(ctx);
        } else if (strcmp(ctx->current.lexeme, "DO") == 0) {
            return parse_loop_do_while(ctx);
        }
    }

    fprintf(stderr, "[PARSER ERROR] Неизвестная конструкция цикла: %s\n", ctx->current.lexeme);
    return NULL;
}
