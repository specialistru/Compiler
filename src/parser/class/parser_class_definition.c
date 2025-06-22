// parser_class_definition.c — Обработка объявления класса: CLASS ... DEFINITION.
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг CLASS <name> DEFINITION ... ENDCLASS.
ast_node_t* parse_class_definition(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CLASS")) {
        return NULL;
    }

    token_t class_token = ctx->previous;
    ast_node_t* class_node = ast_node_create(AST_CLASS_DEFINITION, class_token);

    // Имя класса
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя класса после CLASS");
        ast_node_free(class_node);
        return NULL;
    }

    token_t name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(class_node, ast_node_create(AST_EXPR_IDENTIFIER, name_token));

    // Ожидаем DEFINITION
    if (!parser_match(ctx, TOKEN_KEYWORD, "DEFINITION")) {
        parser_error(ctx, "Ожидалось ключевое слово DEFINITION после имени класса");
        ast_node_free(class_node);
        return NULL;
    }

    // Точка после DEFINITION
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после DEFINITION");
        ast_node_free(class_node);
        return NULL;
    }

    // Парсим содержимое объявления класса до ENDCLASS
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDCLASS") && !parser_is_at_end(ctx)) {
        ast_node_t* stmt = parse_statement(ctx);
        if (stmt) {
            ast_node_add_child(class_node, stmt);
        } else {
            parser_advance(ctx);  // избегаем зацикливания
        }
    }

    // ENDCLASS имя .
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        parser_error(ctx, "Ожидалось завершение класса: ENDCLASS");
        ast_node_free(class_node);
        return NULL;
    }

    // Имя класса (опционально)
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        ast_node_add_child(class_node, ast_node_create(AST_EXPR_IDENTIFIER, ctx->current));
        parser_advance(ctx);
    }

    // Завершающая точка
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDCLASS");
        ast_node_free(class_node);
        return NULL;
    }

    return class_node;
}
