#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция — ожидание и проверка токена
static void expect_token(parser_t* parser, token_type_t type, const char* lexeme) {
    if (parser->current_token.type != type ||
        (lexeme != NULL && strcmp(parser->current_token.lexeme, lexeme) != 0)) {
        fprintf(stderr,
            "[PARSE METHOD DEF ERROR] Ожидался токен '%s', но найден '%s' на строке %d\n",
            lexeme ? lexeme : token_type_to_string(type),
            parser->current_token.lexeme,
            parser->current_line);
        exit(EXIT_FAILURE);
    }
}

// Разбор списка параметров метода: (param1, param2, ...)
static ast_node_t* parse_method_parameters(parser_t* parser) {
    expect_token(parser, TOKEN_SYMBOL, "(");
    parser_advance(parser);

    ast_node_t* params_node = ast_node_create(AST_METHOD_PARAMS, parser->previous_token);

    if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
        // Параметров нет
        parser_advance(parser);
        return params_node;
    }

    while (1) {
        if (parser->current_token.type != TOKEN_IDENTIFIER) {
            fprintf(stderr,
                "[PARSE METHOD DEF ERROR] Ожидался идентификатор параметра на строке %d, найден '%s'\n",
                parser->current_line,
                parser->current_token.lexeme);
            exit(EXIT_FAILURE);
        }

        token_t param_token = parser->current_token;
        parser_advance(parser);

        ast_node_t* param_node = ast_node_create(AST_METHOD_PARAM, param_token);
        ast_node_add_child(params_node, param_node);

        if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ",") == 0) {
            parser_advance(parser);
            continue;
        } else if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
            parser_advance(parser);
            break;
        } else {
            fprintf(stderr,
                "[PARSE METHOD DEF ERROR] Ожидалась запятая или ')' после параметра на строке %d, найден '%s'\n",
                parser->current_line,
                parser->current_token.lexeme);
            exit(EXIT_FAILURE);
        }
    }

    return params_node;
}

// Основная функция разбора определения метода
ast_node_t* parse_method_definition(parser_t* parser) {
    // Ожидаем ключевое слово METHOD
    expect_token(parser, TOKEN_KEYWORD, "METHOD");
    token_t method_keyword = parser->current_token;
    parser_advance(parser);

    // Имя метода — идентификатор
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr,
            "[PARSE METHOD DEF ERROR] Ожидалось имя метода после 'METHOD' на строке %d, найден '%s'\n",
            parser->current_line,
            parser->current_token.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t method_name_token = parser->current_token;
    parser_advance(parser);

    // Парсим параметры метода
    ast_node_t* params_node = parse_method_parameters(parser);

    // Создаем узел метода
    ast_node_t* method_node = ast_node_create(AST_METHOD_DEF, method_name_token);
    ast_node_add_child(method_node, params_node);

    // Ожидаем ключевое слово BODY
    expect_token(parser, TOKEN_KEYWORD, "BODY");
    parser_advance(parser);

    // Парсим тело метода — блок операторов
    ast_node_t* body_node = parse_method_body(parser);
    if (!body_node) {
        fprintf(stderr,
            "[PARSE METHOD DEF ERROR] Ошибка при разборе тела метода '%s' на строке %d\n",
            method_name_token.lexeme,
            parser->current_line);
        exit(EXIT_FAILURE);
    }
    ast_node_add_child(method_node, body_node);

    // Ожидаем ключевое слово ENDMETHOD
    expect_token(parser, TOKEN_KEYWORD, "ENDMETHOD");
    parser_advance(parser);

    return method_node;
}
