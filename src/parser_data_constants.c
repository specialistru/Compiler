// parser_data_constants.c
#include "parser_data_constants.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для ожидания ключевого слова с конкретным лексемом
static int expect_keyword(parser_context_t* ctx, const char* keyword) {
    if (ctx->current.type == TOKEN_KEYWORD && strcmp(ctx->current.lexeme, keyword) == 0) {
        parser_advance(ctx);
        return 1;
    }
    return 0;
}

// Парсинг атрибута VALUE VALUE <literal>
static ast_node_t* parse_constants_value(parser_context_t* ctx) {
    if (!expect_keyword(ctx, "VALUE")) return NULL;

    if (ctx->current.type != TOKEN_LITERAL) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось литеральное значение после VALUE, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t val_tok = ctx->current;
    parser_advance(ctx);
    return ast_node_create(AST_EXPR_LITERAL, val_tok);
}

// Парсинг атрибута DECIMALS DECIMALS <number>
static ast_node_t* parse_constants_decimals(parser_context_t* ctx) {
    if (!expect_keyword(ctx, "DECIMALS")) return NULL;

    if (ctx->current.type != TOKEN_LITERAL || ctx->current.token_class != TOKEN_CLASS_NUMBER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось числовое значение после DECIMALS, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t dec_tok = ctx->current;
    parser_advance(ctx);
    return ast_node_create(AST_EXPR_LITERAL, dec_tok);
}

// Основная функция парсинга CONSTANTS
ast_node_t* parse_constants_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CONSTANTS")) {
        return NULL; // Не объявление CONSTANTS
    }

    token_t const_tok = ctx->previous;
    ast_node_t* node = ast_node_create(AST_CONSTANTS, const_tok);

    // Идентификатор константы
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор для CONSTANTS, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t ident_tok = ctx->current;
    parser_advance(ctx);

    ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, ident_tok);
    ast_node_add_child(node, ident_node);

    // Парсим атрибут TYPE (если есть)
    ast_node_t* type_node = NULL;
    if (parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался тип после TYPE в CONSTANTS\n");
            exit(EXIT_FAILURE);
        }
        token_t type_tok = ctx->current;
        parser_advance(ctx);
        type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
        ast_node_add_child(node, type_node);
    }

    // Парсим VALUE (обязательно для CONSTANTS)
    ast_node_t* value_node = parse_constants_value(ctx);
    if (!value_node) {
        fprintf(stderr, "[PARSER ERROR] Ожидался VALUE в объявлении CONSTANTS\n");
        exit(EXIT_FAILURE);
    }
    ast_node_add_child(node, value_node);

    // Парсим DECIMALS (опционально)
    ast_node_t* decimals_node = parse_constants_decimals(ctx);
    if (decimals_node) {
        ast_node_add_child(node, decimals_node);
    }

    // Проверка точки в конце объявления
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце объявления CONSTANTS\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
