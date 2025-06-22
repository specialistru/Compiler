#include "parser_perform.h"
#include <stdio.h>

// Разбор простой формы: PERFORM form_name.
ast_node_t* parse_perform_simple(parser_t* parser) {
    // Проверка на ключевое слово PERFORM
    if (!parser_match(parser, TOKEN_KEYWORD, "PERFORM")) {
        parse_perform_error("Ожидалось ключевое слово PERFORM", parser);
        return NULL;
    }

    // Сохраняем токен PERFORM
    token_t perform_token = parser->previous;
    ast_node_t* node = ast_node_create(AST_PERFORM, perform_token);

    // Ожидаем идентификатор подпрограммы
    if (!parser_expect(parser, TOKEN_IDENTIFIER, "Ожидался идентификатор подпрограммы")) {
        ast_node_free(node);
        return NULL;
    }

    token_t form_name_token = parser->previous;
    ast_node_t* form_name_node = ast_node_create(AST_EXPR_IDENTIFIER, form_name_token);
    ast_node_add_child(node, form_name_node);

    // Проверка точки в конце
    if (!parser_expect(parser, TOKEN_SYMBOL, "Ожидалась точка после PERFORM")) {
        ast_node_free(node);
        return NULL;
    }

    return node;
}
