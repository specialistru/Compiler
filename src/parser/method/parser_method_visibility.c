#include "parser_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для проверки и возврата типа видимости из ключевого слова
static method_visibility_t parse_visibility_keyword(const char* lexeme) {
    if (strcmp(lexeme, "PUBLIC") == 0) {
        return VISIBILITY_PUBLIC;
    } else if (strcmp(lexeme, "PRIVATE") == 0) {
        return VISIBILITY_PRIVATE;
    } else if (strcmp(lexeme, "PROTECTED") == 0) {
        return VISIBILITY_PROTECTED;
    } else {
        return VISIBILITY_UNKNOWN;
    }
}

// Парсинг видимости метода или класса
ast_node_t* parse_method_visibility(parser_t* parser) {
    if (parser->current_token.type != TOKEN_KEYWORD) {
        fprintf(stderr,
            "[PARSE METHOD VISIBILITY ERROR] Ожидалось ключевое слово видимости, но найден '%s' на строке %d\n",
            parser->current_token.lexeme,
            parser->current_line);
        exit(EXIT_FAILURE);
    }

    method_visibility_t visibility = parse_visibility_keyword(parser->current_token.lexeme);
    if (visibility == VISIBILITY_UNKNOWN) {
        fprintf(stderr,
            "[PARSE METHOD VISIBILITY ERROR] Неизвестный уровень видимости '%s' на строке %d\n",
            parser->current_token.lexeme,
            parser->current_line);
        exit(EXIT_FAILURE);
    }

    token_t vis_token = parser->current_token;
    parser_advance(parser);

    // Создаем AST узел для видимости
    ast_node_t* visibility_node = ast_node_create(AST_METHOD_VISIBILITY, vis_token);
    visibility_node->visibility = visibility;

    return visibility_node;
}
