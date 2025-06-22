#include "parser_perform_errors.h"
#include <stdio.h>

// Универсальный обработчик ошибок парсинга PERFORM
void parse_perform_report_error(const char* message, parser_context_t* ctx) {
    fprintf(stderr, "[PERFORM PARSER ERROR] %s на позиции %d, токен: '%s'\n",
            message, ctx->current.position, ctx->current.lexeme);
    // Можно добавить механизм восстановления или логгирования
}
