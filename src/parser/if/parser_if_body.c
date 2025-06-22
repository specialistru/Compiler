#include "parser_if_body.h"
#include "parser_if_nested.h"
#include "lexer.h"
#include "ast.h"

// Здесь заглушка: тело IF может содержать множество инструкций, включая вложенный IF
ast_node_t* parse_if_body(token_stream_t *tokens) {
    ast_node_t *body_node = ast_node_create(AST_BODY, tokens->current_token);

    // Пока не встречаем ELSE/ELSEIF/ENDIF, парсим инструкции
    while (tokens->current_token.type != TOKEN_ELSE &&
           tokens->current_token.type != TOKEN_ELSEIF &&
           tokens->current_token.type != TOKEN_ENDIF &&
           tokens->current_token.type != TOKEN_EOF) {

        // Пробуем вложенный IF
        ast_node_t *nested_if = parse_if_nested(tokens);
        if (nested_if) {
            ast_node_add_child(body_node, nested_if);
            continue;
        }

        // TODO: добавить парсинг других инструкций (например, PERFORM, CALL FUNCTION и др.)
        // Для примера: пропускаем текущий токен (заглушка)
        token_advance(tokens);
    }
    return body_node;
}
