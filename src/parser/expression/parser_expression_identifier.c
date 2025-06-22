// parser_expression_identifier.c
#include "parser_expression.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг идентификатора: простого или квалифицированного (например, с точками)
ast_node_t* parse_expression_identifier(parser_context_t* ctx) {
    if (ctx->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор, найден '%s'\n", ctx->current_token.lexeme);
        return NULL;
    }

    // Создаем начальный узел с первым идентификатором
    token_t first_ident = ctx->current_token;
    ast_node_t* node = ast_node_create(AST_IDENTIFIER, first_ident);
    parser_advance(ctx);

    // Проверяем цепочку квалификаторов, например: object.property.subproperty
    while (ctx->current_token.type == TOKEN_SYMBOL && ctx->current_token.lexeme[0] == '.') {
        parser_advance(ctx);  // пропускаем точку

        if (ctx->current_token.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор после '.', найден '%s'\n", ctx->current_token.lexeme);
            ast_node_free(node);
            return NULL;
        }

        // Создаем узел для идентификатора после точки
        token_t next_ident = ctx->current_token;
        ast_node_t* child_node = ast_node_create(AST_IDENTIFIER, next_ident);
        parser_advance(ctx);

        // Добавляем child_node как дочерний к текущему node
        ast_node_add_child(node, child_node);
    }

    return node;
}
