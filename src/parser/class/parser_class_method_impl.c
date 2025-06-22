/*
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
*/

// parser_class_method_impl.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг тела метода — произвольный набор инструкций до END_METHOD
ast_node_t* parse_method_implementation(parser_context_t* ctx) {
    // Создаем узел реализации метода
    ast_node_t* impl_node = ast_node_create(AST_METHOD_IMPL, ctx->current);

    // Ожидаем ключевое слово METHOD (уже пропущено) и имя метода
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя метода для реализации, найдено: %s\n", ctx->current.lexeme);
        ast_node_destroy(impl_node);
        return NULL;
    }
    token_t method_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* name_node = ast_node_create(AST_IDENTIFIER, method_name);
    ast_node_add_child(impl_node, name_node);

    // Ожидаем открывающую фигурную скобку или начало тела метода (например, "BEGIN")
    // Здесь допустим, что тело начинается сразу — для упрощения.

    // Парсим тело метода до ключевого слова END_METHOD или конца блока
    while (!(ctx->current.type == TOKEN_KEYWORD && 
             (strcmp(ctx->current.lexeme, "ENDMETHOD") == 0 || strcmp(ctx->current.lexeme, "END_METHOD") == 0))) {
        // Здесь вызов парсера для инструкций, например parse_statement(ctx)
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            fprintf(stderr, "[PARSER ERROR] Ошибка парсинга инструкции в теле метода\n");
            ast_node_destroy(impl_node);
            return NULL;
        }
        ast_node_add_child(impl_node, stmt);
        // parser_advance вызывается внутри parse_statement
    }

    // Пропускаем END_METHOD
    parser_advance(ctx);

    return impl_node;
}
