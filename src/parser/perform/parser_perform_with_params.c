#include "parser_perform.h"
#include <stdio.h>

// Разбор конструкции PERFORM ... USING ... CHANGING ...
ast_node_t* parse_perform_with_params(parser_t* parser) {
    if (!parser_match(parser, TOKEN_KEYWORD, "PERFORM")) {
        parse_perform_error("Ожидалось ключевое слово PERFORM", parser);
        return NULL;
    }

    // Основной узел PERFORM
    token_t perform_token = parser->previous;
    ast_node_t* perform_node = ast_node_create(AST_PERFORM, perform_token);

    // Идентификатор подпрограммы
    if (!parser_expect(parser, TOKEN_IDENTIFIER, "Ожидался идентификатор подпрограммы")) {
        ast_node_free(perform_node);
        return NULL;
    }

    token_t form_token = parser->previous;
    ast_node_t* form_name_node = ast_node_create(AST_EXPR_IDENTIFIER, form_token);
    ast_node_add_child(perform_node, form_name_node);

    // Параметры USING
    if (parser_match(parser, TOKEN_KEYWORD, "USING")) {
        while (parser_check(parser, TOKEN_IDENTIFIER)) {
            token_t param_tok = parser->current;
            parser_advance(parser);
            ast_node_t* param_node = ast_node_create(AST_EXPR_IDENTIFIER, param_tok);
            ast_node_add_child(perform_node, param_node);
        }
    }

    // Параметры CHANGING
    if (parser_match(parser, TOKEN_KEYWORD, "CHANGING")) {
        while (parser_check(parser, TOKEN_IDENTIFIER)) {
            token_t change_tok = parser->current;
            parser_advance(parser);
            ast_node_t* change_node = ast_node_create(AST_EXPR_IDENTIFIER, change_tok);
            ast_node_add_child(perform_node, change_node);
        }
    }

    // Проверка точки
    if (!parser_expect(parser, TOKEN_SYMBOL, "Ожидалась точка после PERFORM")) {
        ast_node_free(perform_node);
        return NULL;
    }

    return perform_node;
}
