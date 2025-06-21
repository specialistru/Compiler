#include "parser_data_declaration.h"
#include <stdio.h>

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
