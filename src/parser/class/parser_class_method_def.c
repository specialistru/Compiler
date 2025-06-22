/*
// parser_class_method_def.c — Парсинг определения метода внутри класса
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Парсинг METHOD <name> [IMPORTING/EXPORTING/...]
ast_node_t* parse_class_method_definition(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        return NULL;
    }

    // Ожидаем имя метода
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя метода после ключевого слова METHOD");
        return NULL;
    }

    token_t method_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* method_node = ast_node_create(AST_METHOD_DEF, method_name);

    // Парсим опциональные параметры IMPORTING/EXPORTING/CHANGING/RETURNING
    while (parser_check(ctx, TOKEN_KEYWORD, "IMPORTING") ||
           parser_check(ctx, TOKEN_KEYWORD, "EXPORTING") ||
           parser_check(ctx, TOKEN_KEYWORD, "CHANGING") ||
           parser_check(ctx, TOKEN_KEYWORD, "RETURNING")) {
        
        token_t param_token = ctx->current;
        parser_advance(ctx);

        while (ctx->current.type == TOKEN_IDENTIFIER) {
            token_t param_name = ctx->current;
            parser_advance(ctx);

            ast_node_t* param_node = ast_node_create(AST_PARAMETERS, param_name);
            ast_node_add_child(method_node, param_node);

            if (parser_check(ctx, TOKEN_SYMBOL, ".")) break;
        }
    }

    // Ожидается завершение точки
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась '.' в конце определения метода");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}
*/

// parser_class_method_def.c
// Парсинг определения метода (сигнатуры) класса — без тела

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг параметров метода (в круглых скобках)
ast_node_t* parse_method_parameters(parser_context_t* ctx);

// Парсинг определения метода (сигнатура без тела)
ast_node_t* parse_class_method_def(parser_context_t* ctx) {
    // Ожидаем ключевое слово METHOD
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово METHOD\n");
        return NULL;
    }

    // Имя метода — идентификатор
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя метода после METHOD\n");
        return NULL;
    }
    token_t method_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* method_def_node = ast_node_create(AST_METHOD_DEF, method_name);

    // Парсим параметры
    if (parser_match(ctx, TOKEN_SYMBOL, "(")) {
        ast_node_t* params_node = parse_method_parameters(ctx);
        if (params_node) {
            ast_node_add_child(method_def_node, params_node);
        }
        if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ) после параметров метода\n");
            ast_node_destroy(method_def_node);
            return NULL;
        }
    }

    // Опциональный возвращаемый тип
    if (parser_match(ctx, TOKEN_KEYWORD, "RETURNING")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался тип после RETURNING\n");
            ast_node_destroy(method_def_node);
            return NULL;
        }
        ast_node_t* ret_type_node = ast_node_create(AST_TYPE, ctx->current);
        parser_advance(ctx);
        ast_node_add_child(method_def_node, ret_type_node);
    }

    // Ожидаем точку с запятой, если это сигнатура без тела
    if (!parser_match(ctx, TOKEN_SYMBOL, ";")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась ';' после определения метода\n");
        ast_node_destroy(method_def_node);
        return NULL;
    }

    return method_def_node;
}
