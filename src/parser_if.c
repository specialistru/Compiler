#include "parser_if.h"

#include "ast.h"
#include "lexer.h"

// Основная функция парсинга конструкции IF
ast_node_t* parse_if(token_stream_t *tokens) {
    // Создаем узел IF
    ast_node_t *if_node = ast_node_create(AST_IF, tokens->current_token);

    // Парсим условие
    ast_node_t *condition = parse_if_condition(tokens);
    if (!condition) {
        parse_if_error("Ошибка при разборе условия IF", tokens);
        return NULL;
    }
    ast_node_add_child(if_node, condition);

    // Парсим тело IF
    ast_node_t *body = parse_if_body(tokens);
    if (!body) {
        parse_if_error("Ошибка при разборе тела IF", tokens);
        return NULL;
    }
    ast_node_add_child(if_node, body);

    // Парсим ветвления ELSEIF / ELSE
    while (tokens->current_token.type == TOKEN_ELSEIF || tokens->current_token.type == TOKEN_ELSE) {
        if (tokens->current_token.type == TOKEN_ELSEIF) {
            ast_node_t *elseif_node = parse_if_elseif(tokens);
            if (!elseif_node) {
                parse_if_error("Ошибка при разборе ELSEIF", tokens);
                return NULL;
            }
            ast_node_add_child(if_node, elseif_node);
        } else {
            ast_node_t *else_node = parse_if_else(tokens);
            if (!else_node) {
                parse_if_error("Ошибка при разборе ELSE", tokens);
                return NULL;
            }
            ast_node_add_child(if_node, else_node);
            break; // ELSE - последняя ветка
        }
    }

    // Проверяем ENDIF
    if (!parse_if_end(tokens)) {
        parse_if_error("Отсутствует ENDIF", tokens);
        return NULL;
    }

    return if_node;
}
