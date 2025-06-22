#include "parser_data_complex_types.h"
#include <stdio.h>

// Парсинг сложных типов, например:
// TYPES ty_tab TYPE TABLE OF i.
// TYPES ty_struct TYPE STRUCTURE {...}

ast_node_t* parse_complex_type(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        return NULL;
    }

    if (parser_match(ctx, TOKEN_KEYWORD, "TABLE")) {
        if (!parser_match(ctx, TOKEN_KEYWORD, "OF")) {
            fprintf(stderr, "[PARSER ERROR] Ожидалось OF после TABLE\n");
            exit(EXIT_FAILURE);
        }
        token_t base_type = expect_identifier(ctx);
        ast_node_t* table_type_node = ast_node_create(AST_TYPE_TABLE_OF, base_type);
        return table_type_node;
    }

    if (parser_match(ctx, TOKEN_KEYWORD, "STRUCTURE")) {
        // Для простоты здесь может быть только имя структуры
        token_t struct_name = expect_identifier(ctx);
        ast_node_t* struct_node = ast_node_create(AST_TYPE_STRUCTURE, struct_name);
        return struct_node;
    }

    // Поддержка других сложных типов при необходимости

    // Если простой тип, возвращаем идентификатор типа
    token_t type_id = expect_identifier(ctx);
    ast_node_t* type_node = ast_node_create(AST_EXPR_IDENTIFIER, type_id);
    return type_node;
}
