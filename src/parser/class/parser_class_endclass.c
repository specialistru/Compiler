// parser_class_endclass.c
//
// Парсер конструкции ENDCLASS
//

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция обработки ошибки парсинга в классе
static void parse_class_error(parser_context_t* ctx, const char* message) {
    fprintf(stderr, "[PARSER ERROR] %s на позиции %d: '%s'\n",
            message, ctx->current.position, ctx->current.lexeme);
    exit(EXIT_FAILURE);
}

// Функция для парсинга конструкции ENDCLASS
// Возвращает AST-узел для ENDCLASS
ast_node_t* parse_class_endclass(parser_context_t* ctx) {
    if (!ctx) {
        fprintf(stderr, "[PARSER ERROR] null parser context\n");
        exit(EXIT_FAILURE);
    }

    // Проверка, что текущий токен - ключевое слово ENDCLASS
    if (ctx->current.type != TOKEN_KEYWORD || strcmp(ctx->current.lexeme, "ENDCLASS") != 0) {
        parse_class_error(ctx, "Ожидалось ключевое слово ENDCLASS");
    }

    // Создаем AST-узел для ENDCLASS
    ast_node_t* node = ast_node_create(AST_CLASS_ENDCLASS, ctx->current);

    // Продвигаем токен
    parser_advance(ctx);

    // Проверяем наличие точки в конце (если синтаксис требует)
    if (ctx->current.type == TOKEN_SYMBOL && strcmp(ctx->current.lexeme, ".") == 0) {
        parser_advance(ctx);
    } else {
        // В зависимости от требований синтаксиса - можно выдавать ошибку или предупреждение
        // parse_class_error(ctx, "Ожидалась точка после ENDCLASS");
    }

    return node;
}

