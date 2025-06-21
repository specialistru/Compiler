// parser_if.c
#include "parser_if_condition.h"
#include "parser_if_body.h"
#include "parser_if_elseif.h"
#include "parser_if_else.h"
#include "parser_if_end.h"
#include "ast.h"
#include "lexer.h"
#include "parser.h"

// Входная функция парсинга IF
ast_node_t* parse_if(parser_t* parser) {
    // Проверка ключевого слова IF и парсинг условия
    ast_node_t* if_node = ast_node_create(AST_IF, parser_peek_token(parser));
    if (!parse_if_condition(parser, if_node)) {
        parser_error(parser, "Ошибка парсинга условия IF");
        ast_node_free(if_node);
        return NULL;
    }

    // Парсинг тела IF
    if (!parse_if_body(parser, if_node)) {
        parser_error(parser, "Ошибка парсинга тела IF");
        ast_node_free(if_node);
        return NULL;
    }

    // Парсинг конструкции ELSEIF (0 или более)
    while (parser_match_keyword(parser, "ELSEIF")) {
        if (!parse_if_elseif(parser, if_node)) {
            parser_error(parser, "Ошибка парсинга ELSEIF");
            ast_node_free(if_node);
            return NULL;
        }
    }

    // Парсинг конструкции ELSE (0 или 1)
    if (parser_match_keyword(parser, "ELSE")) {
        if (!parse_if_else(parser, if_node)) {
            parser_error(parser, "Ошибка парсинга ELSE");
            ast_node_free(if_node);
            return NULL;
        }
    }

    // Парсинг ENDIF
    if (!parse_if_end(parser)) {
        parser_error(parser, "Ожидался ENDIF");
        ast_node_free(if_node);
        return NULL;
    }

    return if_node;
}
