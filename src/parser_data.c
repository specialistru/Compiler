#include "parser_data.h"
#include <stdio.h>

// Вспомогательная функция: ожидает и возвращает идентификатор
static token_t expect_identifier(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, но найдено: %s\n", ctx->current.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t token = ctx->current;
    parser_advance(ctx);
    return token;
}

// Вспомогательная функция: обрабатывает конструкцию "TYPE typename"
static ast_node_t* parse_type_clause(parser_context_t* ctx) {
    if (parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        token_t type_tok = expect_identifier(ctx);
        ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
        return type_node;
    }
    return NULL;
}

// Основная функция разбора объявления
ast_node_t* parse_data_declaration(parser_context_t* ctx) {
    ast_node_type_t decl_type;
    if (parser_match(ctx, TOKEN_KEYWORD, "DATA")) {
        decl_type = AST_DATA;
    } else if (parser_match(ctx, TOKEN_KEYWORD, "CONSTANTS")) {
        decl_type = AST_CONSTANTS;
    } else if (parser_match(ctx, TOKEN_KEYWORD, "TYPES")) {
        decl_type = AST_TYPES;
    } else if (parser_match(ctx, TOKEN_KEYWORD, "FIELD-SYMBOLS")) {
        decl_type = AST_FIELD_SYMBOLS;
    } else if (parser_match(ctx, TOKEN_KEYWORD, "PARAMETERS")) {
        decl_type = AST_PARAMETERS;
    } else {
        return NULL; // Не является декларацией данных
    }

    token_t decl_tok = ctx->previous;
    ast_node_t* node = ast_node_create(decl_type, decl_tok);

    // Идентификатор переменной
    token_t ident_tok = expect_identifier(ctx);
    ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, ident_tok);
    ast_node_add_child(node, ident_node);

    // Обработка типа
    ast_node_t* type_clause = parse_type_clause(ctx);
    if (type_clause) {
        ast_node_add_child(node, type_clause);
    }

    // Проверка точки
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце объявления данных\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
