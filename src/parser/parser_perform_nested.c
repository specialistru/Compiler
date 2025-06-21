#include "parser_perform_nested.h"
#include "parser_utils.h"
#include <stdio.h>

// Парсинг вложенного PERFORM
// Форматы:
// PERFORM subroutine_name [USING ... CHANGING ...].
// PERFORM subroutine_name.
//    PERFORM nested_subroutine.
// END PERFORM.
//
ast_node_t* parse_perform_nested(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "PERFORM")) {
        return NULL;
    }

    token_t subroutine_name = expect_identifier(ctx);

    ast_node_t* perform_node = ast_node_create(AST_PERFORM_NESTED, ctx->previous);

    // Добавляем имя подпрограммы
    ast_node_t* sub_node = ast_node_create(AST_EXPR_IDENTIFIER, subroutine_name);
    ast_node_add_child(perform_node, sub_node);

    // Парсим параметры USING / CHANGING (если есть)
    while (parser_match_keyword(ctx, "USING") || parser_match_keyword(ctx, "CHANGING")) {
        token_t param_type = ctx->previous;
        ast_node_t* param_node = ast_node_create(AST_PERFORM_PARAM, param_type);

        // Ожидаем список идентификаторов параметров
        do {
            token_t param_ident = expect_identifier(ctx);
            ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, param_ident);
            ast_node_add_child(param_node, ident_node);
        } while (parser_match_symbol(ctx, ","));

        ast_node_add_child(perform_node, param_node);
    }

    // Проверяем точку в конце
    if (!parser_match_symbol(ctx, ".")) {
        parse_error("Ожидалась точка '.' после PERFORM", ctx);
    }

    // Проверка на вложенный PERFORM внутри тела
    if (parser_check_keyword(ctx, "PERFORM")) {
        ast_node_t* nested = parse_perform_nested(ctx);
        if (nested) {
            ast_node_add_child(perform_node, nested);
        }
    }

    return perform_node;
}
