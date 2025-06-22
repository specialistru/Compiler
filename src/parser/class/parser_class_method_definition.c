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

/*
// parser_class_method_declaration.c — парсинг объявления метода класса
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг объявления метода внутри класса
ast_node_t* parse_class_method_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        return NULL;
    }

    token_t method_token = ctx->previous;
    ast_node_t* method_node = ast_node_create(AST_CLASS_METHOD_DECLARATION, method_token);

    // Имя метода — обязательный идентификатор
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после ключевого слова METHOD");
        ast_node_free(method_node);
        return NULL;
    }

    token_t method_name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(method_node, ast_node_create(AST_EXPR_IDENTIFIER, method_name_token));

    // Опциональный блок PARAMETERS ... END PARAMETERS
    if (parser_match(ctx, TOKEN_KEYWORD, "PARAMETERS")) {
        ast_node_t* params_node = parse_method_parameters(ctx);
        if (!params_node) {
            parser_error(ctx, "Ошибка при разборе параметров метода");
            ast_node_free(method_node);
            return NULL;
        }
        ast_node_add_child(method_node, params_node);

        if (!parser_match(ctx, TOKEN_KEYWORD, "ENDPARAMETERS")) {
            parser_error(ctx, "Ожидалось END PARAMETERS после параметров метода");
            ast_node_free(method_node);
            return NULL;
        }
    }

    // Можно добавить парсинг тела метода здесь, если требуется
    // ...

    // Закрытие объявления метода: ключевое слово ENDMETHOD и точка
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDMETHOD")) {
        parser_error(ctx, "Ожидалось ENDMETHOD для завершения объявления метода");
        ast_node_free(method_node);
        return NULL;
    }

    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDMETHOD");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}
*/

    return method_node;
}
