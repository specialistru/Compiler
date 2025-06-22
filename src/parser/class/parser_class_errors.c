// parser_class_errors.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для обработки и вывода ошибок парсинга классов
void parse_class_error(parser_context_t* ctx, const char* message) {
    if (!ctx) return;

    fprintf(stderr, "[PARSER ERROR] %s\n", message);
    if (ctx->current.type != TOKEN_EOF) {
        fprintf(stderr, "Ошибка на токене: '%s' (тип: %d)\n", ctx->current.lexeme, ctx->current.type);
    } else {
        fprintf(stderr, "Достигнут конец файла\n");
    }
    // В зависимости от архитектуры парсера можно остановить выполнение,
    // бросить исключение или установить флаг ошибки.
    exit(EXIT_FAILURE);
}

// Проверка ожидания конкретного токена с выводом ошибки при несоответствии
void expect_token(parser_context_t* ctx, token_type_t expected_type, const char* expected_lexeme) {
    if (!ctx) return;

    if (ctx->current.type != expected_type || 
       (expected_lexeme && strcmp(ctx->current.lexeme, expected_lexeme) != 0)) {
        char err_msg[256];
        if (expected_lexeme)
            snprintf(err_msg, sizeof(err_msg), "Ожидался токен '%s', найден '%s'", expected_lexeme, ctx->current.lexeme);
        else
            snprintf(err_msg, sizeof(err_msg), "Ожидался токен типа %d, найден '%s'", expected_type, ctx->current.lexeme);
        parse_class_error(ctx, err_msg);
    }
}

// Возможное расширение: логирование предупреждений
void parse_class_warning(const char* message) {
    fprintf(stderr, "[PARSER WARNING] %s\n", message);
}


