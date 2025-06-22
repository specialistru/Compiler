#include "parser_call.h"
#include <stdio.h>

// Разбор секции EXPORTING параметров в CALL FUNCTION
ast_node_t* parse_call_exporting(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "EXPORTING")) {
        return NULL; // Нет секции EXPORTING
    }

    ast_node_t* exporting_node = ast_node_create(AST_CALL_EXPORTING, ctx->previous);

    while (ctx->current.type == TOKEN_IDENTIFIER) {
        token_t param_name = ctx->current;
        parser_advance(ctx);

        if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
            parse_call_error("Ожидался знак '=' после имени параметра EXPORTING", ctx);
            ast_node_destroy(exporting_node);
            return NULL;
        }

        // Ожидается выражение (здесь для примера — идентификатор или литерал)
        if (ctx->current.type != TOKEN_IDENTIFIER && ctx->current.type != TOKEN_STRING && ctx->current.type != TOKEN_NUMBER) {
            parse_call_error("Ожидалось значение параметра EXPORTING", ctx);
            ast_node_destroy(exporting_node);
            return NULL;
        }
        token_t param_value = ctx->current;
        parser_advance(ctx);

        // Создаем узел параметра
        ast_node_t* param_node = ast_node_create(AST_CALL_PARAM, param_name);
        ast_node_t* value_node = ast_node_create(AST_EXPR_LITERAL, param_value);
        ast_node_add_child(param_node, value_node);

        ast_node_add_child(exporting_node, param_node);

        // Проверка на запятую или окончание секции
        if (!parser_match(ctx, TOKEN_SYMBOL, ",")) {
            break;
        }
    }

    return exporting_node;
}
