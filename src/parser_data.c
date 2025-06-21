#include "parser_data.h"
#include <stdio.h>

// Главная функция: анализирует любую конструкцию DATA/CONSTANTS/...
ast_node_t* parse_data_declaration(parser_context_t* ctx) {
    if (parser_check(ctx, TOKEN_KEYWORD, "DATA")) {
        return parse_data_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "CONSTANTS")) {
        return parse_constants_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "PARAMETERS")) {
        return parse_parameters_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "FIELD-SYMBOLS")) {
        return parse_field_symbols_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "TYPES")) {
        return parse_types_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "SELECT-OPTIONS")) {
        return parse_select_options_statement(ctx);
    }
    if (parser_check(ctx, TOKEN_KEYWORD, "RANGES")) {
        return parse_ranges_statement(ctx);
    }

    // Расширенные конструкции внутри DATA/CONSTANTS
    if (parser_check(ctx, TOKEN_KEYWORD, "INITIALIZATION")) {
        return parse_initialization_statement(ctx);
    }

    // Для сложных типов (структуры, таблицы и пр.)
    if (parser_check(ctx, TOKEN_KEYWORD, "DATA") && parser_peek_keyword(ctx, "BEGIN OF")) {
        return parse_complex_type_statement(ctx);
    }

    // Если ничего не подошло — сообщить об ошибке
    fprintf(stderr, "[PARSER ERROR] Неизвестная или неподдерживаемая конструкция данных: %s\n", ctx->current.lexeme);
    exit(EXIT_FAILURE);
}
