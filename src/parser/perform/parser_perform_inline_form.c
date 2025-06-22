#include "parser_perform.h"
#include <stdio.h>

// Разбор конструкции FORM ... ENDFORM
ast_node_t* parse_form_block(parser_t* parser) {
    if (!parser_match(parser, TOKEN_KEYWORD, "FORM")) {
        parse_perform_error("Ожидалось ключевое слово FORM", parser);
        return NULL;
    }

    token_t form_token = parser->previous;
    ast_node_t* form_node = ast_node_create(AST_FORM, form_token);

    // Имя формы
    if (!parser_expect(parser, TOKEN_IDENTIFIER, "Ожидалось имя подпрограммы после FORM")) {
        ast_node_free(form_node);
        return NULL;
    }

    token_t form_name_tok = parser->previous;
    ast_node_t* form_name_node = ast_node_create(AST_EXPR_IDENTIFIER, form_name_tok);
    ast_node_add_child(form_node, form_name_node);

    // Пропуск точки
    if (!parser_expect(parser, TOKEN_SYMBOL, "Ожидалась точка после имени формы")) {
        ast_node_free(form_node);
        return NULL;
    }

    // Тело формы (до ENDFORM)
    while (!parser_check_keyword(parser, "ENDFORM") && !parser_is_at_end(parser)) {
        ast_node_t* statement = parse_statement(parser);
        if (statement) {
            ast_node_add_child(form_node, statement);
        } else {
            parser_advance(parser); // избегание зацикливания при ошибках
        }
    }

    // Проверка ENDFORM
    if (!parser_match(parser, TOKEN_KEYWORD, "ENDFORM")) {
        parse_perform_error("Ожидался ENDFORM для завершения подпрограммы", parser);
        ast_node_free(form_node);
        return NULL;
    }

    token_t endform_tok = parser->previous;
    ast_node_t* endform_node = ast_node_create(AST_ENDFORM, endform_tok);
    ast_node_add_child(form_node, endform_node);

    // Заканчиваем точкой
    if (!parser_expect(parser, TOKEN_SYMBOL, "Ожидалась точка после ENDFORM")) {
        ast_node_free(form_node);
        return NULL;
    }

    return form_node;
}
