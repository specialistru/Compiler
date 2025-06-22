#include "parser_loop_endloop.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>

// Функция парсинга конца конструкции LOOP (ENDLOOP)
ast_node_t* parse_loop_endloop(parser_context_t *ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDLOOP")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевой слово 'ENDLOOP', найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    token_t endloop_token = ctx->previous;
    ast_node_t *endloop_node = ast_node_create(AST_LOOP_END, endloop_token);

    return endloop_node;
}
