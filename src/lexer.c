#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TOKEN_SIZE 256

// === Ключевые слова ABAP (можно заменить загрузкой из файла) ===
static const char* keywords[] = {
    "DATA", "TYPES", "CLASS", "METHOD", "ENDCLASS", "IF", "ENDIF", "PERFORM", "CALL",
    "FUNCTION", "ENDFUNCTION", "LOOP", "ENDLOOP", "DO", "ENDDO", "SELECT", "FROM", "WHERE",
    "RAISE", "MODULE", "ENDMODULE", "FORM", "ENDFORM", "WRITE", "READ", "MOVE", "CLEAR",
    "APPEND", "DELETE", "EXPORTING", "IMPORTING", "CHANGING", "RAISING", "TRY", "CATCH",
    "ENDTRY", "CONTINUE", "STOP", "AND", "OR", "NOT", "INTO", "NEW", "RETURNING"
};

#define KEYWORDS_COUNT (sizeof(keywords) / sizeof(keywords[0]))

static bool is_keyword(const char* str) {
    for (size_t i = 0; i < KEYWORDS_COUNT; i++) {
        if (strcasecmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

// === Лексер ===

void lexer_init(lexer_t* lexer, const char* source) {
    lexer->source = source;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->column = 1;
}

static char peek(lexer_t* lexer) {
    return lexer->source[lexer->pos];
}

static char peek_next(lexer_t* lexer) {
    return lexer->source[lexer->pos + 1];
}

static char advance(lexer_t* lexer) {
    char c = lexer->source[lexer->pos++];
    if (c == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    return c;
}

static token_t make_token(token_type_t type, const char* start, size_t len, int line, int col) {
    char* lexeme = (char*)malloc(len + 1);
    strncpy(lexeme, start, len);
    lexeme[len] = '\0';
    return (token_t){ type, lexeme, line, col };
}

void lexer_free_token(token_t* token) {
    if (token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}

token_t lexer_next_token(lexer_t* lexer) {
    while (isspace(peek(lexer))) advance(lexer);

    int line = lexer->line;
    int col = lexer->column;
    char c = peek(lexer);

    if (c == '\0') return make_token(TOKEN_EOF, "", 0, line, col);

    // Комментарии
    if (c == '*' || c == '"') {
        while (peek(lexer) != '\n' && peek(lexer) != '\0') advance(lexer);
        return lexer_next_token(lexer); // пропустить комментарий
    }

    // Идентификаторы / ключевые слова
    if (isalpha(c) || c == '_') {
        const char* start = &lexer->source[lexer->pos];
        while (isalnum(peek(lexer)) || peek(lexer) == '_') advance(lexer);
        size_t len = &lexer->source[lexer->pos] - start;
        return make_token(is_keyword(start) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER, start, len, line, col);
    }

    // Числа (целые, десятичные, научные)
    if (isdigit(c)) {
        const char* start = &lexer->source[lexer->pos];
        bool dot_found = false;
        while (isdigit(peek(lexer)) || (!dot_found && peek(lexer) == '.')) {
            if (peek(lexer) == '.') dot_found = true;
            advance(lexer);
        }
        if (tolower(peek(lexer)) == 'e') {
            advance(lexer);
            if (peek(lexer) == '+' || peek(lexer) == '-') advance(lexer);
            while (isdigit(peek(lexer))) advance(lexer);
        }
        size_t len = &lexer->source[lexer->pos] - start;
        return make_token(TOKEN_NUMBER, start, len, line, col);
    }

    // Строки в одинарных кавычках с экранированием
    if (c == '\'') {
        advance(lexer); // начальная кавычка
        const char* start = &lexer->source[lexer->pos];
        size_t len = 0;
        while (peek(lexer) != '\0') {
            if (peek(lexer) == '\'' && peek_next(lexer) == '\'') {
                advance(lexer); advance(lexer); // двойная кавычка = экранирование
                len += 1;
            } else if (peek(lexer) == '\'') {
                break;
            } else {
                advance(lexer);
                len++;
            }
        }
        advance(lexer); // закрывающая кавычка
        return make_token(TOKEN_STRING, start, len, line, col);
    }

    // Операторы
    if (c == '=' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "=>", 2, line, col);
    }
    if (c == '-' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "->", 2, line, col);
    }
    if (c == '<' && peek_next(lexer) == '>') {
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, "<>", 2, line, col);
    }
    if ((c == '<' || c == '>') && peek_next(lexer) == '=') {
        char op[3] = { c, '=', '\0' };
        advance(lexer); advance(lexer);
        return make_token(TOKEN_OPERATOR, op, 2, line, col);
    }

    // Символы
    if (strchr("+-*/=()[],.;:", c)) {
        advance(lexer);
        return make_token(TOKEN_SYMBOL, &lexer->source[lexer->pos - 1], 1, line, col);
    }

    // Неизвестный символ
    fprintf(stderr, "[LEXER ERROR] Unknown character '%c' at %d:%d\n", c, line, col);
    advance(lexer);
    return make_token(TOKEN_UNKNOWN, &lexer->source[lexer->pos - 1], 1, line, col);
}
