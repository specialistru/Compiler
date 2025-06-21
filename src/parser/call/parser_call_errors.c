#include "parser_call.h"
#include <stdio.h>

// Логирование ошибки парсинга CALL конструкции
void parse_call_error(const char* message, parser_context_t* ctx) {
    fprintf(stderr, "[PARSER CALL ERROR] %s. Текущий токен: %s\n", message, ctx->current.lexeme);
}
