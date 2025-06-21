#include "parser.h"
#include <stdio.h>
#include <string.h>

static int expect(Token* tokens, int* pos, const char* expected) {
    if (strcmp(tokens[*pos].text, expected) == 0) {
        (*pos)++;
        return 1;
    }
    printf("Syntax error: expected '%s', found '%s'\n", expected, tokens[*pos].text);
    return 0;
}

static int parse_methods(Token* tokens, int* pos) {
    if (!expect(tokens, pos, "METHODS")) return 0;
    if (!expect(tokens, pos, ":")) return 0;

    while (tokens[*pos].type != TOKEN_EOF) {
        if (strcmp(tokens[*pos].text, "ENDCLASS") == 0) break;
        // Пропускаем метод - очень упрощенно
        (*pos)++;
    }
    return 1;
}

ParseResult parse_class(Token* tokens) {
    int pos = 0;
    ParseResult result = {0, 0};

    if (!expect(tokens, &pos, "CLASS")) return result;
    if (tokens[pos].type != TOKEN_IDENTIFIER) {
        printf("Syntax error: expected class name\n");
        return result;
    }
    pos++;
    if (!expect(tokens, &pos, "DEFINITION")) return result;
    if (!expect(tokens, &pos, ".")) return result;

    if (!parse_methods(tokens, &pos)) return result;

    if (!expect(tokens, &pos, "ENDCLASS")) return result;
    if (!expect(tokens, &pos, ".")) return result;

    result.success = 1;
    result.pos = pos;
    return result;
}

