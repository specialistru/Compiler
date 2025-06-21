#include "parser_if_error.h"
#include <stdio.h>
#include "lexer.h"

void parse_if_error(const char *message, token_stream_t *tokens) {
    fprintf(stderr, "Ошибка синтаксиса IF: %s в позиции %d\n", message, tokens->current_token.position);
    // Здесь можно добавить логику для восстановления парсинга или выхода
}
