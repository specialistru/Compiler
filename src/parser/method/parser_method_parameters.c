#include "parser_method.h"
#include <stdio.h>

// Парсинг списка параметров метода
// Пример:
// USING iv_param TYPE i,
//       iv_other TYPE string.
// Возвращает AST-узел с параметрами или NULL, если параметров нет
ast_node_t* parse_method_parameters(parser_t* parser) {
    if (!parser_expect_keyword(parser, "USING")) {
        // Нет параметров, это не ошибка
        return NULL;
    }

    ast_node_t* params_node = ast_node_create(AST_METHOD_PARAMETERS, parser->previous_token);

    while (true) {
        // Ожидаем идентификатор параметра
        if (!parser_expect_identifier(parser)) {
            parse_method_error(parser, "Ожидался идентификатор параметра");
            ast_node_free(params_node);
            return NULL;
        }
        token_t param_name = parser_previous_token(parser);
        ast_node_t* param_node = ast_node_create(AST_METHOD_PARAMETER, param_name);

        // Ожидаем ключевое слово TYPE
        if (!parser_expect_keyword(parser, "TYPE")) {
            parse_method_error(parser, "Ожидалось ключевое слово 'TYPE' после имени параметра");
            ast_node_free(param_node);
            ast_node_free(params_node);
            return NULL;
        }

        // Ожидаем идентификатор типа
        if (!parser_expect_identifier(parser)) {
            parse_method_error(parser, "Ожидался идентификатор типа параметра");
            ast_node_free(param_node);
            ast_node_free(params_node);
            return NULL;
        }
        token_t type_name = parser_previous_token(parser);
        ast_node_t* type_node = ast_node_create(AST_TYPE_IDENTIFIER, type_name);
        ast_node_add_child(param_node, type_node);

        ast_node_add_child(params_node, param_node);

        // Если дальше идет запятая — продолжаем
        if (parser_match_symbol(parser, ",")) {
            parser_advance(parser);
            continue;
        }

        // Если точка — конец параметров
        if (parser_match_symbol(parser, ".")) {
            parser_advance(parser);
            break;
        }

        // Если ничего из выше — ошибка
        parse_method_error(parser, "Ожидалась запятая ',' или точка '.' после параметра");
        ast_node_free(params_node);
        return NULL;
    }

    return params_node;
}

// Вспомогательная функция вывода ошибок
void parse_method_error(parser_t* parser, const char* message) {
    fprintf(stderr, "[METHOD PARAMETERS PARSER ERROR] %s at line %d\n", message, parser->current_line);
}
