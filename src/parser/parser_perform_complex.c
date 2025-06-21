#include "parser_perform_complex.h"
#include "parser_utils.h"

// Парсинг сложных конструкций PERFORM, включающих параметры, вложенные вызовы и условия
ast_node_t* parse_perform_complex(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "PERFORM")) {
        return NULL;
    }

    token_t subroutine_name = expect_identifier(ctx);

    ast_node_t* perform_node = ast_node_create(AST_PERFORM_COMPLEX, ctx->previous);

    // Имя подпрограммы
    ast_node_t* sub_node = ast_node_create(AST_EXPR_IDENTIFIER, subroutine_name);
    ast_node_add_child(perform_node, sub_node);

    // Парсим параметры USING / CHANGING
    while (parser_match_keyword(ctx, "USING") || parser_match_keyword(ctx, "CHANGING")) {
        token_t param_type = ctx->previous;
        ast_node_t* param_node = ast_node_create(AST_PERFORM_PARAM, param_type);

        do {
            token_t param_ident = expect_identifier(ctx);
            ast_node_t* ident_node = ast_node_create(AST_EXPR_IDENTIFIER, param_ident);
            ast_node_add_child(param_node, ident_node);
        } while (parser_match_symbol(ctx, ","));

        ast_node_add_child(perform_node, param_node);
    }

    // Обработка условия (IF ... THEN ...)
    if (parser_match_keyword(ctx, "IF")) {
        ast_node_t* condition = parse_perform_condition(ctx);
        if (!condition) {
            parse_error("Ошибка в условии PERFORM IF", ctx);
        }
        ast_node_add_child(perform_node, condition);

        if (!parser_match_keyword(ctx, "THEN")) {
            parse_error("Ожидался THEN после условия IF в PERFORM", ctx);
        }
    }

    if (!parser_match_symbol(ctx, ".")) {
        parse_error("Ожидалась точка '.' после сложной конструкции PERFORM", ctx);
    }

    return perform_node;
}
