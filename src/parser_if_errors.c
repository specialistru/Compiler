#include "parser_if_errors.h"
#include "parser_if.h"
#include <stdio.h>

// Вывод сообщения об ошибке с указанием позиции токена
void parse_if_error(const char *message, token_stream_t *tokens) {
    token_t *current = token_stream_peek(tokens);
    if (current) {
        fprintf(stderr, "Syntax error at line %d, col %d: %s (found '%s')\n",
                current->line, current->col, message, current->lexeme);
    } else {
        fprintf(stderr, "Syntax error: %s (at end of input)\n", message);
    }
}

// Проверка на ожидаемые токены, иначе ошибка и попытка восстановления
int expect_token(token_stream_t *tokens, token_type_t expected_type, const char *error_message) {
    token_t *tok = token_stream_peek(tokens);
    if (!tok || tok->type != expected_type) {
        parse_if_error(error_message, tokens);
        // Попытка восстановления: пропустить токены пока не встретится ожидаемый или конец
        while (tok && tok->type != expected_type && tok->type != TOKEN_EOF) {
            token_stream_next(tokens);
            tok = token_stream_peek(tokens);
        }
        if (tok && tok->type == expected_type) {
            token_stream_next(tokens); // съесть ожидаемый токен
            return 1;
        }
        return 0; // не удалось восстановиться
    }
    token_stream_next(tokens);
    return 1;
}

// Проверка правильности конструкции IF ... ENDIF
int check_if_block_syntax(token_stream_t *tokens) {
    int if_depth = 1;
    token_t *tok = NULL;
    while ((tok = token_stream_peek(tokens)) && tok->type != TOKEN_EOF) {
        if (tok->type == TOKEN_IF) {
            if_depth++;
        } else if (tok->type == TOKEN_ENDIF) {
            if_depth--;
            if (if_depth == 0) {
                token_stream_next(tokens); // съесть ENDIF
                return 1; // блок корректно закрыт
            }
        }
        token_stream_next(tokens);
    }
    parse_if_error("Missing ENDIF for IF block", tokens);
    return 0; // не нашли ENDIF
}

// Обработка ошибок в конструкции IF с попыткой пропуска до безопасной точки
void handle_if_syntax_errors(token_stream_t *tokens) {
    parse_if_error("Invalid syntax in IF construct, attempting to recover", tokens);
    // Пропустить токены пока не найдём ENDIF или EOF
    token_t *tok = token_stream_peek(tokens);
    while (tok && tok->type != TOKEN_ENDIF && tok->type != TOKEN_EOF) {
        token_stream_next(tokens);
        tok = token_stream_peek(tokens);
    }
    if (tok && tok->type == TOKEN_ENDIF) {
        token_stream_next(tokens); // съесть ENDIF
    }
}
