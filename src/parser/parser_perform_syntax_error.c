#include "parser_perform_syntax_error.h"
#include <stdio.h>

// Обработка ошибок синтаксиса конструкции PERFORM
void parse_perform_error(const char* message, parser_context_t* ctx) {
    fprintf(stderr, "[PERFORM PARSER ERROR] %s на позиции %d: '%s'\n",
        message, ctx->current.position, ctx->current.lexeme);
    // Можно добавить логику восстановления или выход из парсера
}
