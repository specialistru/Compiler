// parser_class_method.c
// Парсинг определения метода класса

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг определения метода класса
ast_node_t* parse_class_method(parser_context_t* ctx) {
    // Ожидаем ключевое слово METHOD
    if (!parser_match(ctx, TOKEN_KEYWORD, "METHOD")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово METHOD\n");
        return NULL;
    }

    // Ожидаем идентификатор — имя метода
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя метода после METHOD\n");
        return NULL;
    }

    token_t method_name = ctx->current;
    parser_advance(ctx);

    ast_node_t* method_node = ast_node_create(AST_METHOD_DEF, method_name);

    // Парсим параметры метода (если есть), в круглых скобках
    if (parser_match(ctx, TOKEN_SYMBOL, "(")) {
        ast_node_t* params_node = parse_method_parameters(ctx);
        if (params_node) {
            ast_node_add_child(method_node, params_node);
        }

        if (!parser_match(ctx, TOKEN_SYMBOL, ")")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалась закрывающая скобка ) после параметров метода\n");
            ast_node_destroy(method_node);
            return NULL;
        }
    }

    // Опционально парсим возвращаемый тип (RETURNING <type>)
    if (parser_match(ctx, TOKEN_KEYWORD, "RETURNING")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался тип после RETURNING\n");
            ast_node_destroy(method_node);
            return NULL;
        }
        ast_node_t* ret_type_node = ast_node_create(AST_TYPE, ctx->current);
        parser_advance(ctx);
        ast_node_add_child(method_node, ret_type_node);
    }

    // Парсим тело метода, если присутствует (до END METHOD)
    ast_node_t* body_node = parse_method_body(ctx);
    if (body_node) {
        ast_node_add_child(method_node, body_node);
    }

    // Ожидаем END METHOD
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDMETHOD") && !parser_match(ctx, TOKEN_KEYWORD, "END METHOD")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось END METHOD для завершения определения метода\n");
        ast_node_destroy(method_node);
        return NULL;
    }

    return method_node;
}

