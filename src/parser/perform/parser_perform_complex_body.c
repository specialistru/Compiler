#include "parser_perform_complex_body.h"
#include "parser_utils.h"

// Парсинг сложного тела PERFORM с несколькими инструкциями
ast_node_t* parse_perform_complex_body(parser_context_t* ctx) {
    ast_node_t* body_node = ast_node_create(AST_PERFORM_BODY, ctx->current);

    while (!parser_check_keyword(ctx, "ENDPERFORM") && !parser_is_at_end(ctx)) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parse_error("Ошибка в теле PERFORM", ctx);
        }
        ast_node_add_child(body_node, stmt);
    }

    if (!parser_match_keyword(ctx, "ENDPERFORM")) {
        parse_error("Ожидался ENDPERFORM для завершения блока PERFORM", ctx);
    }

    return body_node;
}
