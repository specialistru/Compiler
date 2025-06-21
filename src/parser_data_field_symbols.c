// parser_data_field_symbols.c
#include "parser_data_field_symbols.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для ожидания идентификатора
static token_t expect_identifier(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t token = ctx->current;
    parser_advance(ctx);
    return token;
}

// Парсинг FIELD-SYMBOLS <fs_name> TYPE <type_name>.
ast_node_t* parse_field_symbols_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "FIELD-SYMBOLS")) {
        return NULL; // не FIELD-SYMBOLS
    }

    token_t decl_tok = ctx->previous;
    ast_node_t* node = ast_node_create(AST_FIELD_SYMBOLS, decl_tok);

    // Идентификатор field-symbol
    token_t fs_name_tok = expect_identifier(ctx);
    ast_node_t* fs_name_node = ast_node_create(AST_EXPR_IDENTIFIER, fs_name_tok);
    ast_node_add_child(node, fs_name_node);

    // Опционально TYPE <typename>
    if (parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        if (ctx->current.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался тип после TYPE в FIELD-SYMBOLS\n");
            exit(EXIT_FAILURE);
        }
        token_t type_tok = ctx->current;
        parser_advance(ctx);
        ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
        ast_node_add_child(node, type_node);
    }

    // Проверка точки
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце FIELD-SYMBOLS объявления\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
