#include "parser_call.h"

// Главная функция парсинга CALL FUNCTION конструкции
ast_node_t* parse_call(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CALL")) {
        parse_call_error("Ожидалось ключевое слово CALL", ctx);
        return NULL;
    }

    // Парсим простую часть CALL FUNCTION 'funcname'.
    ast_node_t* call_node = parse_call_simple(ctx);
    if (!call_node) return NULL;

    // Парсим опциональные секции EXPORTING, IMPORTING, EXCEPTIONS, TABLES
    ast_node_t* exporting = parse_call_exporting(ctx);
    if (exporting) ast_node_add_child(call_node, exporting);

    ast_node_t* importing = parse_call_importing(ctx);
    if (importing) ast_node_add_child(call_node, importing);

    ast_node_t* exceptions = parse_call_exceptions(ctx);
    if (exceptions) ast_node_add_child(call_node, exceptions);

    ast_node_t* tables = parse_call_tables(ctx);
    if (tables) ast_node_add_child(call_node, tables);

    // Проверка на обязательную точку в конце, если не была проверена ранее
    if (!parser_match(ctx, TOKEN_SYMBOL, ".")) {
        parse_call_error("Ожидалась точка в конце CALL FUNCTION", ctx);
        ast_node_destroy(call_node);
        return NULL;
    }

    return call_node;
}
