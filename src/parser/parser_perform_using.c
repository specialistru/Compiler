#include "parser_perform.h"
#include <stdio.h>

// Разбор секции USING после FORM или PERFORM
ast_node_t* parse_using_clause(parser_t* parser) {
    if (!parser_match(parser, TOKEN_KEYWORD, "USING")) {
        return NULL; // Не ошибка, если USING отсутствует
    }

    token_t using_tok = parser->previous;
    ast_node_t* using_node = ast_node_create(AST_USING, using_tok);

    // Один или несколько идентификаторов
    do {
        if (!parser_expect(parser, TOKEN_IDENTIFIER, "Ожидался параметр после USING")) {
            ast_node_free(using_node);
            return NULL;
        }

        token_t param_tok = parser->previous;
        ast_node_t* param_node = ast_node_create(AST_EXPR_IDENTIFIER, param_tok);
        ast_node_add_child(using_node, param_node);

    } while (parser_match(parser, TOKEN_SYMBOL, ",")); // Поддержка списка через запятую (опционально)

    return using_node;
}
