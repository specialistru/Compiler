// parser_class_end.c — Обработка завершения определения класса: ENDCLASS.
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг конструкции ENDCLASS.
ast_node_t* parse_class_end(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        return NULL;
    }

    token_t end_token = ctx->previous;
    ast_node_t* node = ast_node_create(AST_ENDCLASS, end_token);

    // Опционально: имя класса
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        ast_node_t* name = ast_node_create(AST_EXPR_IDENTIFIER, ctx->current);
        parser_advance(ctx);
        ast_node_add_child(node, name);
    }

    // Ожидаем точку после ENDCLASS
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDCLASS");
        ast_node_free(node);
        return NULL;
    }

    return node;
}
