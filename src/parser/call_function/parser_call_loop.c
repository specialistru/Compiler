#include "parser_call.h"

// Пример парсера вызова функции в цикле DO ... ENDDO
ast_node_t* parse_call_loop(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "DO")) {
        return NULL;
    }

    // Парсим количество повторов
    ast_node_t* count_expr = parse_expression(ctx);
    if (!count_expr) {
        parse_call_error("Expected count expression after DO", ctx);
        return NULL;
    }

    ast_node_t* loop_node = ast_node_create(AST_LOOP_DO, ctx->previous);
    ast_node_add_child(loop_node, count_expr);

    // Тело цикла — один или несколько вызовов функций
    while (!parser_check_keyword(ctx, "ENDDO") && !parser_check_eof(ctx)) {
        ast_node_t* call = parse_call_simple(ctx);
        if (!call) {
            parse_call_error("Expected function call inside DO loop", ctx);
            return NULL;
        }
        ast_node_add_child(loop_node, call);
    }

    if (!parser_match_keyword(ctx, "ENDDO")) {
        parse_call_error("Expected ENDDO at end of loop", ctx);
        return NULL;
    }

    return loop_node;
}
