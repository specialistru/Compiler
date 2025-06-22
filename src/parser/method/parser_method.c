#include "parser_method.h"
#include "parser_method_definition.h"
#include "parser_method_implementation.h"
#include "parser_method_visibility.h"
#include "parser_method_error.h"
#include <stdio.h>
#include <string.h>

// Основная функция разбора метода
ast_node_t* parse_method(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_KEYWORD) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевой слово для метода, найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    // Определяем тип конструкции метода по текущему ключевому слову
    if (strcmp(ctx->current.lexeme, "METHOD") == 0) {
        return parse_method_definition(ctx);
    } else if (strcmp(ctx->current.lexeme, "IMPLEMENTATION") == 0) {
        return parse_method_implementation(ctx);
    } else if (strcmp(ctx->current.lexeme, "VISIBLE") == 0 ||
               strcmp(ctx->current.lexeme, "HIDDEN") == 0 ||
               strcmp(ctx->current.lexeme, "PRIVATE") == 0 ||
               strcmp(ctx->current.lexeme, "PROTECTED") == 0 ||
               strcmp(ctx->current.lexeme, "PUBLIC") == 0) {
        return parse_method_visibility(ctx);
    } else {
        // Ошибка или неизвестная конструкция
        fprintf(stderr, "[PARSER ERROR] Неизвестная конструкция метода: %s\n", ctx->current.lexeme);
        return NULL;
    }
}
