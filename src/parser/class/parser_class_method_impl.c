// parser_class_method_impl.c — Реализация метода: METHOD ... [логика] ... ENDMETHOD.
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг реализации метода: METHOD <name> ... ENDMETHOD.
ast_node_t* parse_class_method_impl(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        return NULL;
    }

    token_t method_token = ctx->previous;
    ast_node_t* method_node = ast_node_create(AST_METHOD_IMPL, method_token);

    // Имя метода обязательно
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после ключевого слова METHOD");
        ast_node_free(method_node);
        return NULL;
    }

    // Добавляем имя метода
    token_t name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(method_node, ast_node_create(AST_EXPR_IDENTIFIER, name_token));

    // Парсим тело метода до ENDMETHOD
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDMETHOD") && !parser_is_at_end(ctx)) {
        ast_node_t* stmt = parse_statement(ctx);
        if (stmt) {
            ast_node_add_child(method_node, stmt);
        } else {
            parser_advance(ctx); // избегаем зависания на ошибочном токене
        }
    }

    // Проверка завершения: ENDMETHOD
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDMETHOD")) {
        parser_error(ctx, "Ожидалось завершение метода ENDMETHOD");
        ast_node_free(method_node);
        return NULL;
    }

    // Опционально имя метода после ENDMETHOD
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        ast_node_add_child(method_node, ast_node_create(AST_EXPR_IDENTIFIER, ctx->current));
        parser_advance(ctx);
    }

    // Точка обязательна
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDMETHOD");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}
