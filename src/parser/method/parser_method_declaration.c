#include "parser_method.h"
#include <stdio.h>

// Парсинг определения метода с телом
// Пример:
// METHOD method_name.
//   "тело метода"
// ENDMETHOD.
// Возвращает AST-узел с определением метода или NULL при ошибках.
ast_node_t* parse_method_definition(parser_t* parser) {
    if (!parser_expect_keyword(parser, "METHOD")) {
        parse_method_error(parser, "Ожидался ключевое слово 'METHOD'");
        return NULL;
    }

    if (!parser_expect_identifier(parser)) {
        parse_method_error(parser, "Ожидалось имя метода после 'METHOD'");
        return NULL;
    }

    token_t method_name = parser_previous_token(parser);
    ast_node_t* method_node = ast_node_create(AST_METHOD_DEFINITION, method_name);

    // Опционально парсим параметры метода
    ast_node_t* params = parse_method_parameters(parser);
    if (params) {
        ast_node_add_child(method_node, params);
    }

    if (!parser_expect_symbol(parser, ".")) {
        parse_method_error(parser, "Ожидалась точка '.' после объявления метода");
        ast_node_free(method_node);
        return NULL;
    }

    // Парсим тело метода — до ключевого слова ENDMETHOD
    ast_node_t* body = parse_method_body(parser);
    if (!body) {
        parse_method_error(parser, "Ошибка при разборе тела метода");
        ast_node_free(method_node);
        return NULL;
    }
    ast_node_add_child(method_node, body);

    if (!parser_expect_keyword(parser, "ENDMETHOD")) {
        parse_method_error(parser, "Ожидался 'ENDMETHOD' после тела метода");
        ast_node_free(method_node);
        return NULL;
    }

    if (!parser_expect_symbol(parser, ".")) {
        parse_method_error(parser, "Ожидалась точка '.' после 'ENDMETHOD'");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}

// Вспомогательная функция вывода ошибок
void parse_method_error(parser_t* parser, const char* message) {
    fprintf(stderr, "[METHOD PARSER ERROR] %s at line %d\n", message, parser->current_line);
}

// Заглушка: парсинг параметров метода
ast_node_t* parse_method_parameters(parser_t* parser) {
    // TODO: реализовать разбор параметров метода
    return NULL;
}

// Заглушка: парсинг тела метода
ast_node_t* parse_method_body(parser_t* parser) {
    // TODO: реализовать разбор тела метода (синтаксический анализ инструкций)
    return NULL;
}
