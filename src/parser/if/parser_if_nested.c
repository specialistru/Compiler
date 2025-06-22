#include "parser_if_nested.h"
#include "parser_if.h"
#include "lexer.h"
#include "ast.h"

// Парсинг вложенного IF внутри тела IF или ELSE
ast_node_t* parse_if_nested(token_stream_t *tokens) {
    if (tokens->current_token.type == TOKEN_IF) {
        return parse_if(tokens);
    }
    // Если не IF, возвращаем NULL (или парсим другие инструкции)
    return NULL;
}
