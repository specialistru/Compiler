// parser_class_method_def.c — Парсинг определения метода внутри класса
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Парсинг METHOD <name> [IMPORTING/EXPORTING/...]
ast_node_t* parse_class_method_definition(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        return NULL;
    }

    // Ожидаем имя метода
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после ключевого слова METHOD");
        return NULL;
    }

    token_t method_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* method_node = ast_node_create(AST_METHOD_DEF, method_name);

    // Парсим опциональные параметры IMPORTING/EXPORTING/CHANGING/RETURNING
    while (parser_check(ctx, TOKEN_KEYWORD, "IMPORTING") ||
           parser_check(ctx, TOKEN_KEYWORD, "EXPORTING") ||
           parser_check(ctx, TOKEN_KEYWORD, "CHANGING") ||
           parser_check(ctx, TOKEN_KEYWORD, "RETURNING")) {
        
        token_t param_token = ctx->current;
        parser_advance(ctx);

        while (ctx->current.type == TOKEN_IDENTIFIER) {
            token_t param_name = ctx->current;
            parser_advance(ctx);

            ast_node_t* param_node = ast_node_create(AST_PARAMETERS, param_name);
            ast_node_add_child(method_node, param_node);

            if (parser_check(ctx, TOKEN_SYMBOL, ".")) break;
        }
    }

    // Ожидается завершение точки
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' в конце определения метода");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}
