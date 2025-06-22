#include "parser_method.h"
#include <stdio.h>

// Парсинг определения метода с телом
// Пример:
// METHOD method_name.
//   "тело метода"
// ENDMETHOD.
// Возвращает AST-узел с определением метода или NULL при ошибках.
ast_node_t* parse_method_definition(parser_t* parser) {
    if (!parser_expect_keyword(parser, "METHOD")) {
        parse_method_error(parser, "Ожидался ключевое слово 'METHOD'");
        return NULL;
    }

    if (!parser_expect_identifier(parser)) {
        parse_method_error(parser, "Ожидалось имя метода после 'METHOD'");
        return NULL;
    }

    token_t method_name = parser_previous_token(parser);
    ast_node_t* method_node = ast_node_create(AST_METHOD_DEFINITION, method_name);

    // Опционально парсим параметры метода
    ast_node_t* params = parse_method_parameters(parser);
    if (params) {
        ast_node_add_child(method_node, params);
    }

    if (!parser_expect_symbol(parser, ".")) {
        parse_method_error(parser, "Ожидалась точка '.' после объявления метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Парсим тело метода — до ключевого слова ENDMETHOD
    ast_node_t* body = parse_method_body(parser);
    if (!body) {
        parse_method_error(parser, "Ошибка при разборе тела метода");
        ast_node_free(method_node);
        return NULL;
    }
    ast_node_add_child(method_node, body);

    if (!parser_expect_keyword(parser, "ENDMETHOD")) {
        parse_method_error(parser, "Ожидался 'ENDMETHOD' после тела метода");
        ast_node_free(method_node);
        return NULL;
    }

    if (!parser_expect_symbol(parser, ".")) {
        parse_method_error(parser, "Ожидалась точка '.' после 'ENDMETHOD'");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}

// Вспомогательная функция вывода ошибок
void parse_method_error(parser_t* parser, const char* message) {
    fprintf(stderr, "[METHOD PARSER ERROR] %s at line %d\n", message, parser->current_line);
}

// Заглушка: парсинг параметров метода
ast_node_t* parse_method_parameters(parser_t* parser) {
    // TODO: реализовать разбор параметров метода
    return NULL;
}

// Заглушка: парсинг тела метода
ast_node_t* parse_method_body(parser_t* parser) {
    // TODO: реализовать разбор тела метода (синтаксический анализ инструкций)
    return NULL;
}


/*

#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для проверки и продвижения токена
static void expect_token(parser_t* parser, token_type_t type, const char* lexeme) {
    if (parser->current_token.type != type || (lexeme && strcmp(parser->current_token.lexeme, lexeme) != 0)) {
        fprintf(stderr, "[PARSE METHOD DEF ERROR] Ожидался токен '%s', но найден '%s' на строке %d\n",
                lexeme ? lexeme : token_type_to_string(type), parser->current_token.lexeme, parser->current_line);
        exit(EXIT_FAILURE);
    }
}

// Парсим список параметров метода в круглых скобках
static ast_node_t* parse_method_parameters(parser_t* parser) {
    expect_token(parser, TOKEN_SYMBOL, "(");
    parser_advance(parser);

    ast_node_t* params_node = ast_node_create(AST_METHOD_PARAMS, parser->previous_token);

    if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
        // Нет параметров
        parser_advance(parser);
        return params_node;
    }

    while (1) {
        // Парсим параметр — идентификатор (имя параметра)
        if (parser->current_token.type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "[PARSE METHOD DEF ERROR] Ожидался идентификатор параметра на строке %d, найден '%s'\n",
                    parser->current_line, parser->current_token.lexeme);
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
            fprintf(stderr, "[PARSE METHOD DEF ERROR] Ожидалась запятая или ')' после параметра на строке %d, найден '%s'\n",
                    parser->current_line, parser->current_token.lexeme);
            exit(EXIT_FAILURE);
        }
    }

    return params_node;
}

// Главная функция разбора определения метода
ast_node_t* parse_method_definition(parser_t* parser) {
    // Ожидаем ключевое слово METHOD
    expect_token(parser, TOKEN_KEYWORD, "METHOD");
    token_t method_token = parser->current_token;
    parser_advance(parser);

    // Имя метода
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSE METHOD DEF ERROR] Ожидалось имя метода после 'METHOD' на строке %d, найден '%s'\n",
                parser->current_line, parser->current_token.lexeme);
        exit(EXIT_FAILURE);
    }
    token_t method_name_token = parser->current_token;
    parser_advance(parser);

    // Парсим параметры метода
    ast_node_t* params_node = parse_method_parameters(parser);

    // Создаем узел метода
    ast_node_t* method_node = ast_node_create(AST_METHOD_DEF, method_name_token);
    ast_node_add_child(method_node, params_node);

    // Ожидаем ключевое слово "BODY"
    expect_token(parser, TOKEN_KEYWORD, "BODY");
    parser_advance(parser);

    // Парсим тело метода — блок операторов
    ast_node_t* body_node = parse_method_body(parser);
    if (!body_node) {
        fprintf(stderr, "[PARSE METHOD DEF ERROR] Ошибка при разборе тела метода '%s' на строке %d\n",
                method_name_token.lexeme, parser->current_line);
        exit(EXIT_FAILURE);
    }
    ast_node_add_child(method_node, body_node);

    // Ожидаем ключевое слово "ENDMETHOD"
    expect_token(parser, TOKEN_KEYWORD, "ENDMETHOD");
    parser_advance(parser);

    return method_node;
}

*/
