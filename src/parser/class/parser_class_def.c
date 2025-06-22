// parser_class_def.c — Парсинг определения класса CLASS ... DEFINITION
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Парсинг конструкции CLASS <name> DEFINITION ... ENDCLASS
ast_node_t* parse_class_definition(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CLASS")) {
        return NULL;
    }

    // Имя класса
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя класса после ключевого слова CLASS");
        return NULL;
    }

    token_t class_name = ctx->current;
    parser_advance(ctx);

    // Проверка на ключевое слово DEFINITION
    if (!parser_match(ctx, TOKEN_KEYWORD, "DEFINITION")) {
        parser_error(ctx, "Ожидалось ключевое слово DEFINITION после имени класса");
        return NULL;
    }

    ast_node_t* class_node = ast_node_create(AST_CLASS_DEF, class_name);

    // TODO: поддержка PUBLIC, FINAL, ABSTRACT и других атрибутов
    while (!parser_check(ctx, TOKEN_KEYWORD, "ENDCLASS") &&
           !parser_check(ctx, TOKEN_EOF, NULL)) {
        ast_node_t* child = parse_statement(ctx);
        if (child) {
            ast_node_add_child(class_node, child);
        } else {
            parser_advance(ctx); // пропуск неожиданных токенов
        }
    }

    // Завершающий ENDCLASS
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        parser_error(ctx, "Ожидался ENDCLASS для завершения определения класса");
        ast_node_free(class_node);
        return NULL;
    }

    return class_node;
}
