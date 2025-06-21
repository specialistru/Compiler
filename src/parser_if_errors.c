#include "parser_if_errors.h"
#include "parser_common.h"
#include <stdio.h>

void check_if_syntax_errors(parser_t* parser) {
    if (match_token(parser, TOKEN_KEYWORD, "IF")) {
        if (check_token(parser, TOKEN_KEYWORD, "ENDIF")) {
            report_error(parser, "Пустой блок IF без условия");
            return;
        }

        if (!check_token(parser, TOKEN_IDENTIFIER, NULL) &&
            !check_token(parser, TOKEN_KEYWORD, "NOT")) {
            report_error(parser, "Ожидалось условие после IF");
        }

        // Проверка на ENDIF в конце
        bool found_end = false;
        size_t checkpoint = parser->current;

        while (parser->tokens[parser->current].type != TOKEN_EOF) {
            if (check_token(parser, TOKEN_KEYWORD, "ENDIF")) {
                found_end = true;
                break;
            }
            parser->current++;
        }

        parser->current = checkpoint; // Восстановление

        if (!found_end) {
            report_error(parser, "Конструкция IF не закрыта ENDIF");
        }
    }
}
