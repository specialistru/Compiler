#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для проверки и продвижения токена
static void expect_token(parser_t* parser, token_type_t type, const char* lexeme) {
    if (parser->current_token.type != type || (lexeme && strcmp(parser->current_token.lexeme, lexeme) != 0)) {
        fprintf(stderr, "[PARSE RETURN ERROR] Ожидался токен '%s', но найден '%s' на строке %d\n",
                lexeme ? lexeme : token_type_to_string(type), parser->current_token.lexeme, parser->current_line);
        exit(EXIT_FAILURE);
    }
}

// Разбор выражения после RETURN (если есть)
static ast_node_t* parse_expression(parser_t* parser); // Предполагается, что реализовано в другом месте

// Главная функция разбора RETURN
ast_node_t* parse_return(parser_t* parser) {
    // Ожидаем ключевое слово RETURN
    expect_token(parser, TOKEN_KEYWORD, "RETURN");
    token_t return_token = parser->current_token;
    parser_advance(parser);

    // Проверяем, есть ли выражение после RETURN
    ast_node_t* expr_node = NULL;
    if (parser->current_token.type != TOKEN_SYMBOL || strcmp(parser->current_token.lexeme, ";") != 0) {
        expr_node = parse_expression(parser);
        if (!expr_node) {
            fprintf(stderr, "[PARSE RETURN ERROR] Ошибка при разборе выражения после RETURN на строке %d\n", parser->current_line);
            exit(EXIT_FAILURE);
        }
    }

    // Создаем узел RETURN
    ast_node_t* return_node = ast_node_create(AST_STMT_RETURN, return_token);

    // Если есть выражение, добавляем его как дочерний узел
    if (expr_node) {
        ast_node_add_child(return_node, expr_node);
    }

    // Ожидаем точку с запятой
    expect_token(parser, TOKEN_SYMBOL, ";");
    parser_advance(parser);

    return return_node;
}
