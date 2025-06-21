/*
static const char* keywords[] = {
    "CLASS", "DEFINITION", "PUBLIC", "SECTION", "METHODS", "IMPORTING", "TYPE",
    "RETURNING", "VALUE", "ENDCLASS", "IMPLEMENTATION", "METHOD", "DATA",
    "IF", "RAISE", "EXCEPTION", "ENDIF", "ENDMETHOD"
};
*/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"

static const char* src_ptr;
static token_t current_token;

void lexer_init(const char* source) {
    src_ptr = source;
}

static void skip_whitespace() {
    while (*src_ptr && isspace(*src_ptr)) src_ptr++;
}

static bool is_keyword(const char* str) {
    // Минимальный набор ключевых слов для примера
    const char* keywords[] = {"IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", NULL};
    for (int i = 0; keywords[i]; i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

token_t lexer_next_token() {
    skip_whitespace();

    if (*src_ptr == '\0') {
        current_token.type = TOKEN_EOF;
        current_token.text[0] = '\0';
        return current_token;
    }

    // Идентификатор или ключевое слово
    if (isalpha(*src_ptr) || *src_ptr == '_') {
        int len = 0;
        while (isalnum(src_ptr[len]) || src_ptr[len] == '_') {
            if (len < MAX_TOKEN_LEN - 1) len++;
            else break;
        }
        strncpy(current_token.text, src_ptr, len);
        current_token.text[len] = '\0';
        src_ptr += len;

        if (is_keyword(current_token.text)) {
            current_token.type = TOKEN_KEYWORD;
        } else {
            current_token.type = TOKEN_IDENTIFIER;
        }
        return current_token;
    }

    // Число (только целое)
    if (isdigit(*src_ptr)) {
        int len = 0;
        while (isdigit(src_ptr[len])) {
            if (len < MAX_TOKEN_LEN - 1) len++;
            else break;
        }
        strncpy(current_token.text, src_ptr, len);
        current_token.text[len] = '\0';
        src_ptr += len;
        current_token.type = TOKEN_NUMBER;
        return current_token;
    }

    // Строка в кавычках (")
    if (*src_ptr == '"') {
        src_ptr++;
        int len = 0;
        while (*src_ptr && *src_ptr != '"' && len < MAX_TOKEN_LEN - 1) {
            current_token.text[len++] = *src_ptr++;
        }
        current_token.text[len] = '\0';
        if (*src_ptr == '"') src_ptr++;
        current_token.type = TOKEN_STRING;
        return current_token;
    }

    // Операторы (одиночные символы)
    current_token.text[0] = *src_ptr;
    current_token.text[1] = '\0';
    current_token.type = TOKEN_OPERATOR;
    src_ptr++;
    return current_token;
}
