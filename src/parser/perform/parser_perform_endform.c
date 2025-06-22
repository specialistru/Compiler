#include "parser_perform.h"
#include <stdio.h>
#include <stdlib.h>

// Обработка ключевого слова ENDFORM
ast_node_t* parse_perform_endform(parser_t* parser) {
    if (parser_match(parser, TOKEN_KEYWORD, "ENDFORM")) {
        token_t tok = parser_previous(parser);
        
        // Проверка точки в конце
        if (!parser_expect(parser, TOKEN_SYMBOL, ".")) {
            fprintf(stderr, "[PARSER ERROR] После ENDFORM ожидается '.' (строка %d)\n", tok.line);
            exit(EXIT_FAILURE);
        }

        return ast_node_create(AST_ENDFORM, tok);
    }

    // Если ENDFORM не найден, сигнализировать о критической ошибке
    fprintf(stderr, "[PARSER ERROR] Ожидался ENDFORM, но найдено: '%s' (строка %d)\n",
            parser->current.lexeme, parser->current.line);
    exit(EXIT_FAILURE);
}
