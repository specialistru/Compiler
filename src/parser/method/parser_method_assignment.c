#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для ожидания определенного токена
static void expect_token(parser_t* parser, token_type_t type, const char* lexeme) {
    if (parser->current_token.type != type || (lexeme && strcmp(parser->current_token.lexeme, lexeme) != 0)) {
        fprintf(stderr, "[PARSE ASSIGNMENT ERROR] Ожидался токен '%s', но найден '%s' на строке %d\n",
                lexeme ? lexeme : token_type_to_string(type), parser->current_token.lexeme, parser->current_line);
        exit(EXIT_FAILURE);
    }
}

// Разбор выражения справа от знака присвоения
static ast_node_t* parse_expression(parser_t* parser); // Предполагается, что реализовано в другом месте

// Главная функция разбора присвоения
ast_node_t* parse_assignment(parser_t* parser) {
    // Ожидаем идентификатор слева
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSE ASSIGNMENT ERROR] Ожидался идентификатор слева от '=' на строке %d\n", parser->current_line);
        exit(EXIT_FAILURE);
    }

    // Создаем узел для идентификатора (левый операнд)
    ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, parser->current_token);
    parser_advance(parser);

    // Ожидаем символ '='
    expect_token(parser, TOKEN_SYMBOL, "=");
    parser_advance(parser);

    // Парсим выражение справа от '='
    ast_node_t* expr_node = parse_expression(parser);
    if (!expr_node) {
        fprintf(stderr, "[PARSE ASSIGNMENT ERROR] Ошибка при разборе выражения справа от '=' на строке %d\n", parser->current_line);
        exit(EXIT_FAILURE);
    }

    // Создаем узел присвоения и добавляем детей
    ast_node_t* assign_node = ast_node_create(AST_STMT_ASSIGNMENT, parser->previous_token);
    ast_node_add_child(assign_node, ident_node);
    ast_node_add_child(assign_node, expr_node);

    // Ожидаем точку с запятой или другую разделяющую конструкцию
    if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ";") == 0) {
        parser_advance(parser);
    } else {
        fprintf(stderr, "[PARSE ASSIGNMENT ERROR] Ожидалась ';' после присвоения на строке %d\n", parser->current_line);
        exit(EXIT_FAILURE);
    }

    return assign_node;
}
