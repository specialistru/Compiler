// parser_if_condition.c
#include "parser_if_condition.h"
#include "ast.h"
#include "parser.h"
#include "lexer.h"

// Пример функции парсинга условия IF и ELSEIF
bool parse_if_condition(parser_t* parser, ast_node_t* parent_node) {
    // TODO: Реализовать парсинг сложных условий с логическими операторами и скобками
    // Для простоты, пока парсим один идентификатор или выражение
    token_t token = parser_consume(parser, TOKEN_IDENTIFIER, "Ожидался идентификатор в условии");
    if (!token.lexeme) return false;

    ast_node_t* condition_node = ast_node_create(AST_EXPR_IDENTIFIER, token);
    ast_node_add_child(parent_node, condition_node);
    return true;
}
