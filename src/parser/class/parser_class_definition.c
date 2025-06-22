// parser_class_definition.c — Парсинг CLASS ... DEFINITION.
/*
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
*/

// parser_class_definition.c
// Парсинг тела класса — раздела определения (definition section)

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Основная функция парсинга тела класса
ast_node_t* parse_class_definition(parser_context_t* ctx) {
    // Проверяем, что текущий токен — начало определения класса
    if (!(parser_match(ctx, TOKEN_KEYWORD, "DEFINITION") ||
          parser_match(ctx, TOKEN_KEYWORD, "PUBLIC") ||
          parser_match(ctx, TOKEN_KEYWORD, "PRIVATE") ||
          parser_match(ctx, TOKEN_KEYWORD, "PROTECTED"))) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась секция определения класса (DEFINITION/PUBLIC/PRIVATE/PROTECTED)\n");
        return NULL;
    }

    ast_node_t* class_def_node = ast_node_create(AST_CLASS_BODY, ctx->previous);

    // Парсим содержимое класса: методы, атрибуты, внутренние классы
    while (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS") &&
           ctx->current.type != TOKEN_EOF) {
        ast_node_t* member_node = NULL;

        if (parser_check(ctx, TOKEN_KEYWORD, "METHOD")) {
            member_node = parse_class_method(ctx);
        } else if (parser_check(ctx, TOKEN_KEYWORD, "DATA") ||
                   parser_check(ctx, TOKEN_KEYWORD, "FIELD-SYMBOLS")) {
            member_node = parse_class_attributes(ctx);
        } else if (parser_check(ctx, TOKEN_KEYWORD, "CLASS")) {
            member_node = parse_class_def(ctx); // Вложенный класс
        } else {
            fprintf(stderr, "[PARSER ERROR] Неожиданный токен в теле класса: %s\n", ctx->current.lexeme);
            parser_advance(ctx); // Пропускаем ошибочный токен
            continue;
        }

        if (member_node) {
            ast_node_add_child(class_def_node, member_node);
        }
    }

    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDCLASS")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово ENDCLASS для завершения определения класса\n");
        ast_node_destroy(class_def_node);
        return NULL;
    }

    return class_def_node;
}
