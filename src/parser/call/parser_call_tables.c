#include "parser_call.h"
#include <stdio.h>

// Разбор секции TABLES в CALL FUNCTION
ast_node_t* parse_call_tables(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "TABLES")) {
        return NULL;
    }

    ast_node_t* tables_node = ast_node_create(AST_CALL_TABLES, ctx->previous);

    while (ctx->current.type == TOKEN_IDENTIFIER) {
        token_t table_name = ctx->current;
        parser_advance(ctx);

        ast_node_t* table_node = ast_node_create(AST_CALL_TABLE, table_name);
        ast_node_add_child(tables_node, table_node);

        if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
            break;
        }
    }

    return tables_node;
}
