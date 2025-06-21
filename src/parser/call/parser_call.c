#include "parser_call.h"

// Главная точка входа для парсинга конструкции CALL
ast_node_t* parse_call(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "CALL")) {
        return NULL;
    }

    // Дальше определяем тип вызова
    // Например, CALL FUNCTION, CALL METHOD и т.д.
    if (parser_match(ctx, TOKEN_KEYWORD, "FUNCTION")) {
        return parse_call_function(ctx);
    } 
    // Добавить поддержку других типов CALL при необходимости

    parse_call_error("Ожидался тип вызова после CALL", ctx);
    return NULL;
}
