// parser_class_method_definition.c — Парсинг METHOD ... ENDMETHOD
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг определения метода внутри реализации класса
ast_node_t* parse_class_method_definition(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        return NULL;
    }

    token_t method_token = ctx->previous;
    ast_node_t* method_node = ast_node_create(AST_CLASS_METHOD_DEF, method_token);

    // Имя метода
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после METHOD");
        ast_node_free(method_node);
        return NULL;
    }

    token_t method_name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(method_node, ast_node_create(AST_EXPR_IDENTIFIER, method_name_token));

    // Точка
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после имени метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Парсинг тела метода до ENDMETHOD
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDMETHOD") && !parser_is_at_end(ctx)) {
        ast_node_t* stmt = parse_statement(ctx);
        if (stmt) {
            ast_node_add_child(method_node, stmt);
        } else {
            parser_advance(ctx); // пропуск некорректных строк
        }
    }

    // Завершение метода
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDMETHOD")) {
        parser_error(ctx, "Ожидалось ENDMETHOD для завершения метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Опциональное имя метода (повтор)
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        parser_advance(ctx);
    }

    // Завершающая точка
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDMETHOD");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}
