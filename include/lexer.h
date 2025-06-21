#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} token_type_t;

typedef struct {
    token_type_t type;
    char text[MAX_TOKEN_LEN];
} token_t;

void lexer_init(const char* source);
token_t lexer_next_token();

#endif // LEXER_H
