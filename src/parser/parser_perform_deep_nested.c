#include "parser_perform_deep_nested.h"
#include "parser_utils.h"

// Парсинг глубоко вложенных конструкций PERFORM (например, PERFORM внутри PERFORM)
ast_node_t* parse_perform_deep_nested(parser_context_t* ctx) {
    ast_node_t* node = parse_perform(ctx);
    if (!node) {
        parse_error("Ошибка при парсинге вложенного PERFORM", ctx);
    }
    return node;
}
