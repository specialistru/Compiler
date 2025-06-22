// parser_class_simple.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг простой конструкции класса:
// Пример: CLASS classname.
// Возвращает AST-узел класса или NULL при ошибке
ast_node_t* parse_class_simple(parser_context_t* ctx) {
    if (!ctx) return NULL;

    // Ожидаем ключевое слово CLASS
    if (!(ctx->current.type == TOKEN_KEYWORD && strcmp(ctx->current.lexeme, "CLASS") == 0)) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово 'CLASS', найдено '%s'\n", ctx->current.lexeme);
        return NULL;
    }
    token_t class_token = ctx->current;
    parser_advance(ctx);

    // Ожидаем идентификатор (имя класса)
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя класса (идентификатор), найдено '%s'\n", ctx->current.lexeme);
        return NULL;
    }
    token_t class_name_token = ctx->current;
    parser_advance(ctx);

    // Создаем AST узел класса с именем
    ast_node_t* class_node = ast_node_create(AST_CLASS_DECLARATION, class_token);

    // Добавляем дочерний узел — имя класса
    ast_node_t* class_name_node = ast_node_create(AST_IDENTIFIER, class_name_token);
    ast_node_add_child(class_node, class_name_node);

    // Ожидаем точку после объявления
    if (!(ctx->current.type == TOKEN_SYMBOL && strcmp(ctx->current.lexeme, ".") == 0)) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась точка '.' после имени класса\n");
        ast_node_destroy(class_node);
        return NULL;
    }
    parser_advance(ctx);

    // Возвращаем успешно распарсенный узел класса
    return class_node;
}

