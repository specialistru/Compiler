#include "parser_method.h"
#include <stdio.h>

// Функция для парсинга тела метода (последовательность операторов)
// Возвращает AST-узел с телом метода или NULL при ошибке
ast_node_t* parse_method_body(parser_t* parser) {
    // Создаем узел тела метода
    ast_node_t* body_node = ast_node_create(AST_METHOD_BODY, parser->current_token);

    while (!parser_is_at_end(parser)) {
        // Проверяем на конец метода (например, ключевое слово ENDMETHOD)
        if (parser_match_keyword(parser, "ENDMETHOD")) {
            break;
        }

        // Парсим отдельное выражение/оператор
        ast_node_t* stmt = parse_statement(parser);
        if (!stmt) {
            fprintf(stderr, "[METHOD BODY PARSER ERROR] Ошибка при разборе оператора тела метода на строке %d\n", parser->current_line);
            ast_node_free(body_node);
            return NULL;
        }

        ast_node_add_child(body_node, stmt);
    }

    // Проверяем, что встретили END METHOD
    if (!parser_match_keyword(parser, "ENDMETHOD")) {
        fprintf(stderr, "[METHOD BODY PARSER ERROR] Ожидался 'ENDMETHOD' в конце тела метода на строке %d\n", parser->current_line);
        ast_node_free(body_node);
        return NULL;
    }
    parser_advance(parser);  // Пропускаем токен ENDMETHOD

    return body_node;
}

// Заглушка для parse_statement - должна быть реализована отдельно
extern ast_node_t* parse_statement(parser_t* parser);
