#include "parser_perform.h"
#include <stdio.h>

// Сообщение об ошибке при парсинге PERFORM
void parse_perform_error(parser_t* parser, const char* message) {
    fprintf(stderr, "[PERFORM PARSER ERROR] %s at token '%s' (line %d)\n",
            message,
            parser->current.lexeme,
            parser->current.line);
    // Можно добавить стратегию восстановления: пропуск токенов до точки или ключевого слова
}
