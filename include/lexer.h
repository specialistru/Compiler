#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_SYMBOL,
    TOKEN_OPERATOR,
    TOKEN_COMMENT,
    TOKEN_UNKNOWN
} token_type_t;

typedef struct {
    token_type_t type;
    char* lexeme;
    int line;
    int column;
} token_t;

typedef struct {
    const char* source;
    size_t pos;
    int line;
    int column;
} lexer_t;

void lexer_init(lexer_t* lexer, const char* source);
token_t lexer_next_token(lexer_t* lexer);
void lexer_free_token(token_t* token);

#endif // LEXER_H
