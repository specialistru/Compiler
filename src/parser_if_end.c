// parser_if_end.c
#include "parser_if_end.h"
#include "lexer.h"

int parse_if_end(token_stream_t *tokens) {
    if (tokens->current_token.type != TOKEN_ENDIF) return 0;
    token_advance(tokens);
    return 1;
}
