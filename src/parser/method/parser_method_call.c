#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для проверки и продвижения токена
static void expect_token(parser_t* parser, token_type_t type, const char* lexeme) {
    if (parser->current_token.type != type || (lexeme && strcmp(parser->current_token.lexeme, lexeme) != 0)) {
        fprintf(stderr, "[PARSE METHOD CALL ERROR] Ожидался токен '%s', но найден '%s' на строке %d\n",
                lexeme ? lexeme : token_type_to_string(type), parser->current_token.lexeme, parser->current_line);
        exit(EXIT_FAILURE);
    }
}

// Вспомогательная функция для парсинга аргументов метода (в круглых скобках)
static ast_node_t* parse_arguments(parser_t* parser) {
    expect_token(parser, TOKEN_SYMBOL, "(");
    parser_advance(parser);

    ast_node_t* args_node = ast_node_create(AST_ARGS_LIST, parser->previous_token);

    if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
        // Нет аргументов
        parser_advance(parser);
        return args_node;
    }

    while (1) {
        // Парсим выражение — аргумент
        ast_node_t* expr = parse_expression(parser);
        if (!expr) {
            fprintf(stderr, "[PARSE METHOD CALL ERROR] Ошибка при разборе аргумента на строке %d\n", parser->current_line);
            exit(EXIT_FAILURE);
        }
        ast_node_add_child(args_node, expr);

        if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ",") == 0) {
            parser_advance(parser);
            continue;
        } else if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
            parser_advance(parser);
            break;
        } else {
            fprintf(stderr, "[PARSE METHOD CALL ERROR] Ожидалась запятая или ')' после аргумента на строке %d, найден '%s'\n",
                    parser->current_line, parser->current_token.lexeme);
            exit(EXIT_FAILURE);
        }
    }

    return args_node;
}

// Главная функция разбора вызова метода
ast_node_t* parse_method_call(parser_t* parser) {
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSE METHOD CALL ERROR] Ожидался идентификатор метода на строке %d, найден '%s'\n",
                parser->current_line, parser->current_token.lexeme);
        exit(EXIT_FAILURE);
    }

    token_t method_name_token = parser->current_token;
    parser_advance(parser);

    // Парсим аргументы (обязательны круглые скобки)
    ast_node_t* args_node = parse_arguments(parser);

    ast_node_t* call_node = ast_node_create(AST_METHOD_CALL, method_name_token);
    ast_node_add_child(call_node, args_node);

    // Ожидаем точку с запятой
    expect_token(parser, TOKEN_SYMBOL, ";");
    parser_advance(parser);

    return call_node;
}
