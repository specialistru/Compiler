// parser_class_definition.c — Парсинг CLASS ... DEFINITION.
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг объявления класса с блоком DEFINITION
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

    token_t class_name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(class_node, ast_node_create(AST_EXPR_IDENTIFIER, class_name_token));

    // Ожидаем ключевое слово DEFINITION
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

    // Внутренние объявления класса (методы, атрибуты, интерфейсы и т.п.)
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDCLASS") && !parser_is_at_end(ctx)) {
        ast_node_t* member = NULL;

        // Попытка распарсить метод
        member = parse_class_method_declaration(ctx);
        if (!member) {
            // Можно добавить сюда парсинг других членских конструкций: атрибутов и т.д.
            parser_advance(ctx);
            continue;
        }

        ast_node_add_child(class_node, member);
    }

    // Проверка закрытия класса
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        parser_error(ctx, "Ожидалось ENDCLASS для завершения объявления класса");
        ast_node_free(class_node);
        return NULL;
    }

    // Точка после ENDCLASS
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDCLASS");
        ast_node_free(class_node);
        return NULL;
    }

    return class_node;
}
