#include "parser_perform_bracketed.h"
#include "parser_utils.h"

// Парсинг условий в скобках ( ) в конструкции PERFORM
ast_node_t* parse_perform_bracketed(parser_context_t* ctx) {
    if (!parser_match_symbol(ctx, "(")) {
        return NULL;
    }

    ast_node_t* expr = parse_perform_condition(ctx);
    if (!expr) {
        parse_error("Ожидалось выражение внутри скобок", ctx);
    }

    if (!parser_match_symbol(ctx, ")")) {
        parse_error("Ожидалась закрывающая скобка ')'", ctx);
    }

    return expr;
}
