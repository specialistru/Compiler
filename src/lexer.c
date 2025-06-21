#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char* keywords[] = {
    "CLASS", "DEFINITION", "PUBLIC", "SECTION", "METHODS", "IMPORTING", "TYPE",
    "RETURNING", "VALUE", "ENDCLASS", "IMPLEMENTATION", "METHOD", "DATA",
    "IF", "RAISE", "EXCEPTION", "ENDIF", "ENDMETHOD"
};
static const int keywords_count = sizeof(keywords)/sizeof(keywords[0]);

static int is_keyword(const char* s) {
    for (int i=0; i<keywords_count; i++) {
        if (strcmp(s, keywords[i]) == 0) return 1;
    }
    return 0;
}

int lex(const char* input, Token* tokens, int max_tokens) {
    int pos = 0, token_count = 0;

    while (input[pos] != '\0' && token_count < max_tokens) {
        while (isspace(input[pos])) pos++;

        if (input[pos] == '\0') break;

        if (isalpha(input[pos]) || input[pos] == '_' || input[pos] == '>' || input[pos] == '-') {
            int start = pos;
            while (isalnum(input[pos]) || input[pos] == '_' || input[pos] == '>' || input[pos] == '-') pos++;
            int len = pos - start;
            if (len > 63) len = 63;
            strncpy(tokens[token_count].text, &input[start], len);
            tokens[token_count].text[len] = '\0';
            tokens[token_count].type = is_keyword(tokens[token_count].text) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
            token_count++;
            continue;
        }

        if (input[pos] == '\'') {
            pos++;
            int start = pos;
            while (input[pos] != '\'' && input[pos] != '\0') pos++;
            int len = pos - start;
            if (len > 63) len = 63;
            strncpy(tokens[token_count].text, &input[start], len);
            tokens[token_count].text[len] = '\0';
            tokens[token_count].type = TOKEN_STRING;
            token_count++;
            if (input[pos] == '\'') pos++;
            continue;
        }

        tokens[token_count].text[0] = input[pos];
        tokens[token_count].text[1] = '\0';
        tokens[token_count].type = TOKEN_SYMBOL;
        token_count++;
        pos++;
    }
    tokens[token_count].type = TOKEN_EOF;
    tokens[token_count].text[0] = '\0';
    return token_count;
}

