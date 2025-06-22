#include "parser_method.h"
#include <stdio.h>

// Парсинг объявления метода (без тела)
// Пример: METHOD method_name.
// Возвращает AST-узел для объявления метода или NULL при ошибке.
ast_node_t* parse_method_declaration(parser_t* parser) {
    if (!parser_expect_keyword(parser, "METHOD")) {
        parse_method_error(parser, "Ожидался ключевой слово 'METHOD'");
        return NULL;
    }

    if (!parser_expect_identifier(parser)) {
        parse_method_error(parser, "Ожидалось имя метода после 'METHOD'");
        return NULL;
    }

    token_t method_name = parser_previous_token(parser);
    ast_node_t* method_node = ast_node_create(AST_METHOD_DECLARATION, method_name);

    // Опционально парсим параметры метода
    ast_node_t* params = parse_method_parameters(parser);
    if (params) {
        ast_node_add_child(method_node, params);
    }

    if (!parser_expect_symbol(parser, ".")) {
        parse_method_error(parser, "Ожидалась точка '.' в конце объявления метода");
        ast_node_free(method_node);
        return NULL;
    }

    return method_node;
}

// Вспомогательная функция для вывода ошибок
void parse_method_error(parser_t* parser, const char* message) {
    fprintf(stderr, "[METHOD PARSER ERROR] %s at line %d\n", message, parser->current_line);
}
