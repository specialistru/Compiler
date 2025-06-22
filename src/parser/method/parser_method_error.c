#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для вывода сообщения об ошибке парсинга метода и прекращения работы парсера
void parser_method_error(parser_t *parser, const char *message) {
    fprintf(stderr, "[PARSER METHOD ERROR] %s на строке %d, токен: '%s'\n",
            message,
            parser->current_line,
            parser->current_token.lexeme);
    exit(EXIT_FAILURE);
}

// Проверка, что текущий токен соответствует ожидаемому типу и лексеме
void expect_token_method(parser_t *parser, token_type_t expected_type, const char *expected_lexeme) {
    if (parser->current_token.type != expected_type ||
        (expected_lexeme && strcmp(parser->current_token.lexeme, expected_lexeme) != 0)) {
        fprintf(stderr,
                "[PARSER METHOD ERROR] Ожидался токен '%s' типа %d, но найден '%s' типа %d на строке %d\n",
                expected_lexeme ? expected_lexeme : "(любой)",
                expected_type,
                parser->current_token.lexeme,
                parser->current_token.type,
                parser->current_line);
        exit(EXIT_FAILURE);
    }
    parser_advance(parser);
}

// Универсальная функция для проверки ошибок в процессе парсинга метода
void check_method_syntax_error(parser_t *parser, const char *context) {
    if (parser->current_token.type == TOKEN_ERROR) {
        fprintf(stderr,
                "[PARSER METHOD SYNTAX ERROR] Синтаксическая ошибка в контексте '%s' на строке %d, токен: '%s'\n",
                context,
                parser->current_line,
                parser->current_token.lexeme);
        exit(EXIT_FAILURE);
    }
}
