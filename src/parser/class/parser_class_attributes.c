// parser_class_attributes.c — парсинг объявления атрибута класса
#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг объявления атрибута класса
ast_node_t* parse_class_attribute_declaration(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "ATTRIBUTE")) {
        return NULL;
    }

    token_t attr_token = ctx->previous;
    ast_node_t* attr_node = ast_node_create(AST_CLASS_ATTRIBUTE_DECLARATION, attr_token);

    // Имя атрибута — обязательный идентификатор
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидалось имя атрибута после ключевого слова ATTRIBUTE");
        ast_node_free(attr_node);
        return NULL;
    }

    token_t attr_name_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(attr_node, ast_node_create(AST_EXPR_IDENTIFIER, attr_name_token));

    // Ожидаем ключевое слово TYPE
    if (!parser_match(ctx, TOKEN_KEYWORD, "TYPE")) {
        parser_error(ctx, "Ожидалось ключевое слово TYPE после имени атрибута");
        ast_node_free(attr_node);
        return NULL;
    }

    // Тип атрибута — идентификатор типа
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидался идентификатор типа после ключевого слова TYPE");
        ast_node_free(attr_node);
        return NULL;
    }

    token_t type_token = ctx->current;
    parser_advance(ctx);
    ast_node_add_child(attr_node, ast_node_create(AST_EXPR_IDENTIFIER, type_token));

    // Ожидаем точку в конце объявления
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parser_error(ctx, "Ожидалась точка '.' в конце объявления атрибута");
        ast_node_free(attr_node);
        return NULL;
    }

    return attr_node;
}

