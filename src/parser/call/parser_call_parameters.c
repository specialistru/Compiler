#include "parser_call.h"

// Парсинг параметров вызова функции (EXPORTING, IMPORTING, CHANGING)
ast_node_t* parse_call_parameters(parser_context_t* ctx) {
    ast_node_t* params_node = ast_node_create(AST_CALL_PARAMS, ctx->current);

    while (parser_match_keyword(ctx, "EXPORTING") || parser_match_keyword(ctx, "IMPORTING") || parser_match_keyword(ctx, "CHANGING")) {
        token_t param_type = ctx->previous; // EXPORTING, IMPORTING или CHANGING
        ast_node_t* param_type_node = ast_node_create(AST_CALL_PARAM_TYPE, param_type);

        ast_node_t* param_list_node = ast_node_create(AST_CALL_PARAM_LIST, param_type);
        // Считываем параметры: param = val [, param = val ...]
        while (!parser_check(ctx, TOKEN_SYMBOL, ".") && !parser_check_keyword(ctx, "EXCEPTIONS") && !parser_check_eof(ctx)) {
            token_t param_name = expect_identifier(ctx);
            if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
                parse_call_error("Expected '=' in parameter assignment", ctx);
                return NULL;
            }
            ast_node_t* param_assign_node = ast_node_create(AST_CALL_PARAM_ASSIGN, param_name);

            ast_node_t* expr = parse_expression(ctx);
            if (!expr) {
                parse_call_error("Expected expression after '='", ctx);
                return NULL;
            }
            ast_node_add_child(param_assign_node, expr);
            ast_node_add_child(param_list_node, param_assign_node);

            // Запятые между параметрами
            if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
                break;
            }
        }
        ast_node_add_child(param_type_node, param_list_node);
        ast_node_add_child(params_node, param_type_node);
    }

    return params_node;
}
