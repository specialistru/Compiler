#include "parser_perform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Парсинг вызова подпрограммы: PERFORM name USING ... CHANGING ...
ast_node_t* parse_perform_call(parser_t* parser) {
    if (!parser_match(parser, TOKEN_KEYWORD, "PERFORM")) {
        return NULL;
    }

    token_t perform_tok = parser_previous(parser);

    // Имя подпрограммы
    if (!parser_check(parser, TOKEN_IDENTIFIER)) {
        parser_error(parser, "Ожидалось имя подпрограммы после 'PERFORM'");
        return NULL;
    }

    token_t name_tok = parser_advance(parser);
    ast_node_t* perform_node = ast_node_create(AST_PERFORM, perform_tok);

    ast_node_t* name_node = ast_node_create(AST_EXPR_IDENTIFIER, name_tok);
    ast_node_add_child(perform_node, name_node);

    // Обработка USING и CHANGING параметров (если есть)
    while (parser_match(parser, TOKEN_KEYWORD, "USING") || parser_match(parser, TOKEN_KEYWORD, "CHANGING")) {
        token_t keyword = parser_previous(parser);
        ast_node_type_t param_type = (strcmp(keyword.lexeme, "USING") == 0)
                                     ? AST_EXPR_USING
                                     : AST_EXPR_CHANGING;

        ast_node_t* param_section = ast_node_create(param_type, keyword);

        // Список параметров
        while (parser_check(parser, TOKEN_IDENTIFIER)) {
            token_t param_tok = parser_advance(parser);
            ast_node_t* param_node = ast_node_create(AST_EXPR_IDENTIFIER, param_tok);
            ast_node_add_child(param_section, param_node);
        }

        ast_node_add_child(perform_node, param_section);
    }

    // Завершающая точка
    if (!parser_match(parser, TOKEN_SYMBOL, ".")) {
        parser_error(parser, "Ожидалась '.' после PERFORM вызова");
        return NULL;
    }

    return perform_node;
}

