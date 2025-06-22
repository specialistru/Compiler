#include "lexer.h"
#include <stdio.h>

int main() {
    const char* code = "DATA var1 TYPE i. * Comment\nWRITE 'Hello!'.\nIF var1 >= 10.\nENDIF.";
    lexer_t lexer;
    lexer_init(&lexer, code);

    token_t token;
    do {
        token = lexer_next_token(&lexer);
        printf("%d:%d\t%-15s\t%s\n", token.line, token.column,
               (token.type == TOKEN_KEYWORD ? "KEYWORD" :
                token.type == TOKEN_IDENTIFIER ? "IDENTIFIER" :
                token.type == TOKEN_NUMBER ? "NUMBER" :
                token.type == TOKEN_STRING ? "STRING" :
                token.type == TOKEN_SYMBOL ? "SYMBOL" :
                token.type == TOKEN_OPERATOR ? "OPERATOR" :
                token.type == TOKEN_COMMENT ? "COMMENT" :
                token.type == TOKEN_EOF ? "EOF" : "UNKNOWN"),
               token.lexeme);
        lexer_free_token(&token);
    } while (token.type != TOKEN_EOF);

    return 0;
}
