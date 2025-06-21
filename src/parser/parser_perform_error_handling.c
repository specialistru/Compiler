#include "parser_perform.h"
#include <stdio.h>
#include <stdlib.h>

// Обработка ошибки: отсутствует идентификатор подпрограммы
void perform_error_missing_identifier(parser_t* parser, const char* construct) {
    fprintf(stderr, "[PARSER ERROR] В конструкции %s ожидается имя подпрограммы (строка %d)\n",
            construct, parser->current.line);
    exit(EXIT_FAILURE);
}

// Обработка ошибки: отсутствует ENDFORM
void perform_error_missing_endform(parser_t* parser) {
    fprintf(stderr, "[PARSER ERROR] Ожидался ENDFORM (строка %d), но достигнут конец блока.\n",
            parser->current.line);
    exit(EXIT_FAILURE);
}

// Обработка ошибки: USING без параметров
void perform_error_using_no_params(parser_t* parser) {
    fprintf(stderr, "[PARSER ERROR] Ключевое слово USING без указания параметров (строка %d)\n",
            parser->current.line);
    exit(EXIT_FAILURE);
}

