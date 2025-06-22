// parser_class_visibility.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Функция проверяет, является ли текущий токен модификатором видимости
static int is_visibility_modifier(token_t token) {
    if (token.type != TOKEN_KEYWORD) return 0;
    return (strcmp(token.lexeme, "PUBLIC") == 0 ||
            strcmp(token.lexeme, "PRIVATE") == 0 ||
            strcmp(token.lexeme, "PROTECTED") == 0);
}

// Парсинг модификатора видимости класса
// Возвращает AST-узел с типом видимости или NULL, если не найден модификатор
ast_node_t* parse_class_visibility(parser_context_t* ctx) {
    if (!ctx) return NULL;

    if (!is_visibility_modifier(ctx->current)) {
        // Видимость не указана — можно считать по умолчанию, либо возврат NULL
        return NULL;
    }

    token_t visibility_token = ctx->current;
    parser_advance(ctx);

    // Создаем AST узел типа видимости
    ast_node_t* visibility_node = ast_node_create(AST_CLASS_VISIBILITY, visibility_token);
    return visibility_node;
}
