// parser_data_types.c
#include "parser_data_types.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция: ожидание идентификатора
static token_t expect_identifier(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t token = ctx->current;
    parser_advance(ctx);
    return token;
}

// Парсинг TYPES <typename> TYPE <type_name>.
ast_node_t* parse_types_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "TYPES")) {
        return NULL; // не TYPES
    }

    token_t decl_tok = ctx->previous;
    ast_node_t* node = ast_node_create(AST_TYPES, decl_tok);

    // Имя типа
    token_t type_name_tok = expect_identifier(ctx);
    ast_node_t* type_name_node = ast_node_create(AST_EXPR_IDENTIFIER, type_name_tok);
    ast_node_add_child(node, type_name_node);

    // Ключевое слово TYPE (обязательно для TYPES)
    if (!parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово TYPE после имени типа в TYPES\n");
        exit(EXIT_FAILURE);
    }

    // Тип, на который ссылаемся
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор типа после TYPE в TYPES\n");
        exit(EXIT_FAILURE);
    }
    token_t base_type_tok = ctx->current;
    parser_advance(ctx);
    ast_node_t* base_type_node = ast_node_create(AST_EXPR_IDENTIFIER, base_type_tok);
    ast_node_add_child(node, base_type_node);

    // Проверка точки в конце
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце TYPES объявления\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
