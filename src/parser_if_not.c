#include "parser_if_not.h"
#include "parser_expr.h"
#include "parser_common.h"
#include <stdio.h>

ast_node_t* parse_if_not(parser_t* parser) {
    if (!match_token(parser, TOKEN_KEYWORD, "IF")) return NULL;

    // Проверка на наличие NOT
    if (!match_token(parser, TOKEN_KEYWORD, "NOT")) {
        report_error(parser, "Ожидалось ключевое слово 'NOT' после 'IF'");
        return NULL;
    }

    ast_node_t* node = ast_node_create(AST_IF, parser->previous_token);

    // Разбор выражения после NOT
    ast_node_t* condition = parse_expression(parser);
    if (!condition) {
        report_error(parser, "Неверное выражение после NOT");
        ast_node_free(node);
        return NULL;
    }

    ast_node_add_child(node, condition);

    // Разбор тела IF
    while (!check_token(parser, TOKEN_KEYWORD, "ENDIF") &&
           !check_token(parser, TOKEN_EOF, NULL)) {
        ast_node_t* stmt = parse_statement(parser);
        if (stmt) ast_node_add_child(node, stmt);
        else advance_token(parser);
    }

    // Закрытие ENDIF
    if (!match_token(parser, TOKEN_KEYWORD, "ENDIF")) {
        report_error(parser, "Ожидалось 'ENDIF'");
        ast_node_free(node);
        return NULL;
    }

    return node;
}
