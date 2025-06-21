// parser_data_parameters.c
#include "parser_data_parameters.h"
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

// Парсинг PARAMETERS <param_name> TYPE <type_name>.
ast_node_t* parse_parameters_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "PARAMETERS")) {
        return NULL; // не PARAMETERS
    }

    token_t decl_tok = ctx->previous;
    ast_node_t* node = ast_node_create(AST_PARAMETERS, decl_tok);

    // Имя параметра
    token_t param_name_tok = expect_identifier(ctx);
    ast_node_t* param_name_node = ast_node_create(AST_EXPR_IDENTIFIER, param_name_tok);
    ast_node_add_child(node, param_name_node);

    // Ключевое слово TYPE (обязательно для PARAMETERS)
    if (!parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово TYPE после имени параметра в PARAMETERS\n");
        exit(EXIT_FAILURE);
    }

    // Тип параметра
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор типа после TYPE в PARAMETERS\n");
        exit(EXIT_FAILURE);
    }
    token_t type_tok = ctx->current;
    parser_advance(ctx);
    ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_tok);
    ast_node_add_child(node, type_node);

    // Проверка точки в конце
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалась '.' в конце PARAMETERS объявления\n");
        exit(EXIT_FAILURE);
    }

    return node;
}
