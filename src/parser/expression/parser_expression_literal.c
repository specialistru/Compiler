// parser_expression_literal.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для парсинга литеральных значений (числа, строки, true/false и т.д.)
ast_node_t* parse_expression_literal(parser_context_t* ctx) {
    token_t token = ctx->current_token;

    switch (token.type) {
        case TOKEN_INTEGER_LITERAL:
        case TOKEN_FLOAT_LITERAL:
        case TOKEN_STRING_LITERAL:
        case TOKEN_BOOLEAN_LITERAL:
        case TOKEN_NULL_LITERAL:
            // Создаем AST-узел литерала
            ast_node_t* literal_node = ast_node_create(AST_LITERAL, token);
            parser_advance(ctx);  // продвигаемся к следующему токену
            return literal_node;

        default:
            fprintf(stderr, "[PARSER ERROR] Ожидался литерал, найден '%s'\n", token.lexeme);
            return NULL;
    }
}
