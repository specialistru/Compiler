// parser_class_def.c — Парсинг определения класса CLASS ... DEFINITION
// parser_class_def.c
// Парсинг объявления класса (class <имя> [интерфейсы] [модификаторы])

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Основная функция парсинга объявления класса
ast_node_t* parse_class_def(parser_context_t* ctx) {
    // Проверяем наличие ключевого слова "CLASS"
    if (!parser_match(ctx, TOKEN_KEYWORD, "CLASS")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово 'CLASS', найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    // Ожидаем идентификатор — имя класса
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя класса, найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }
    token_t class_name = ctx->current;
    parser_advance(ctx);

    // Создаем AST узел для класса
    ast_node_t* class_node = ast_node_create(AST_CLASS_DEF, class_name);

    // Парсим опциональные интерфейсы, которые реализует класс
    while (parser_match(ctx, TOKEN_KEYWORD, "IMPLEMENTS")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось имя интерфейса после IMPLEMENTS, найдено: %s\n", ctx->current.lexeme);
            ast_node_destroy(class_node);
            return NULL;
        }
        token_t iface_name = ctx->current;
        parser_advance(ctx);
        ast_node_t* iface_node = ast_node_create(AST_INTERFACE_REF, iface_name);
        ast_node_add_child(class_node, iface_node);
    }

    // Опционально парсим модификаторы (например, ABSTRACT, FINAL)
    while (parser_match(ctx, TOKEN_KEYWORD, "ABSTRACT") || parser_match(ctx, TOKEN_KEYWORD, "FINAL")) {
        token_t mod_tok = ctx->previous;
        ast_node_t* mod_node = ast_node_create(AST_MODIFIER, mod_tok);
        ast_node_add_child(class_node, mod_node);
    }

    // Ожидаем начало тела класса — ключевое слово "DEFINITION" или "PUBLIC SECTION"
    if (!(parser_match(ctx, TOKEN_KEYWORD, "DEFINITION") ||
          parser_match(ctx, TOKEN_KEYWORD, "PUBLIC") ||
          parser_match(ctx, TOKEN_KEYWORD, "PRIVATE"))) {
        fprintf(stderr, "[PARSER ERROR] Ожидался 'DEFINITION' или 'PUBLIC' секция после объявления класса\n");
        ast_node_destroy(class_node);
        return NULL;
    }

    // Возвращаем AST узел класса с началом парсинга тела в другом модуле
    return class_node;
}
