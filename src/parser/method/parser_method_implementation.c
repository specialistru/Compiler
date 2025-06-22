// parser_method_implementation.c
#include "parser_method.h"
#include "ast.h"
#include "parser_utils.h"
#include <stdio.h>

// Главная функция парсинга реализации метода:
// Разбирает конструкцию:
// METHOD method_name.
//    <тело метода>
// ENDMETHOD.
ast_node_t* parse_method_implementation(parser_context_t* ctx) {
    // Ожидаем ключевое слово METHOD
    if (!parser_match_keyword(ctx, "METHOD")) {
        parser_error(ctx, "Ожидалось ключевое слово METHOD");
        return NULL;
    }

    // Ожидаем идентификатор - имя метода
    if (ctx->current_token.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после ключевого слова METHOD");
        return NULL;
    }
    token_t method_name_token = ctx->current_token;
    parser_advance(ctx);

    // Создаем AST узел для метода
    ast_node_t* method_node = ast_node_create(AST_METHOD_IMPLEMENTATION, method_name_token);

    // Опционально: можно здесь парсить параметры метода, если в этом месте задаются
    // parse_method_parameters(ctx, method_node);

    // Ожидаем точку после имени метода
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после имени метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Парсим тело метода — набор инструкций
    ast_node_t* body_node = parse_method_body(ctx);
    if (!body_node) {
        parser_error(ctx, "Ошибка при разборе тела метода");
        ast_node_free(method_node);
        return NULL;
    }
    ast_node_add_child(method_node, body_node);

    // Ожидаем ключевое слово ENDMETHOD
    if (!parser_match_keyword(ctx, "ENDMETHOD")) {
        parser_error(ctx, "Ожидалось ключевое слово ENDMETHOD для завершения метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Ожидаем точку после ENDMETHOD
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ключевого слова ENDMETHOD");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}

// Функция для парсинга тела метода (примерная реализация)
ast_node_t* parse_method_body(parser_context_t* ctx) {
    ast_node_t* body_node = ast_node_create(AST_METHOD_BODY, ctx->current_token);

    // Пока не встретили ENDMETHOD, парсим инструкции
    while (!parser_check_keyword(ctx, "ENDMETHOD") && ctx->current_token.type != TOKEN_EOF) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parser_error(ctx, "Ошибка при разборе инструкции метода");
            ast_node_free(body_node);
            return NULL;
        }
        ast_node_add_child(body_node, stmt);
    }

    return body_node;
}

// Пример простой функции парсинга одной инструкции
ast_node_t* parse_statement(parser_context_t* ctx) {
    // Для примера — просто пропускаем токен и создаем "узел инструкции"
    token_t tok = ctx->current_token;
    parser_advance(ctx);
    return ast_node_create(AST_STATEMENT, tok);
}
