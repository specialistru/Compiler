#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 1024

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_SYMBOL,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
} Token;

int lex(const char* input, Token* tokens, int max_tokens);

#endif

