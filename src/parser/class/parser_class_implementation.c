// parser_class_implementation.c — Обработка CLASS ... IMPLEMENTATION.
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг конструкции: CLASS <name> IMPLEMENTATION. ... ENDCLASS.
ast_node_t* parse_class_implementation(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CLASS")) {
        return NULL;
    }

    token_t class_token = ctx->previous;
    ast_node_t* impl_node = ast_node_create(AST_CLASS_IMPLEMENTATION, class_token);

    // Имя класса
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя класса после CLASS");
        ast_node_free(impl_node);
        return NULL;
    }

    token_t name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(impl_node, ast_node_create(AST_EXPR_IDENTIFIER, name_token));

    // Ожидаем ключевое слово IMPLEMENTATION
    if (!parser_match(ctx, TOKEN_KEYWORD, "IMPLEMENTATION")) {
        parser_error(ctx, "Ожидалось IMPLEMENTATION после имени класса");
        ast_node_free(impl_node);
        return NULL;
    }

    // Точка после IMPLEMENTATION
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после IMPLEMENTATION");
        ast_node_free(impl_node);
        return NULL;
    }

    // Парсим содержимое реализации
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDCLASS") && !parser_is_at_end(ctx)) {
        ast_node_t* stmt = parse_statement(ctx);
        if (stmt) {
            ast_node_add_child(impl_node, stmt);
        } else {
            parser_advance(ctx);  // пропускаем ошибочные или пустые строки
        }
    }

    // ENDCLASS имя .
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        parser_error(ctx, "Ожидалось ENDCLASS для завершения реализации класса");
        ast_node_free(impl_node);
        return NULL;
    }

    // Повторное имя класса (опционально)
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        parser_advance(ctx);
    }

    // Завершающая точка
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDCLASS");
        ast_node_free(impl_node);
        return NULL;
    }

    return impl_node;
}
