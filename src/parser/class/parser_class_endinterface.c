// parser_class_endinterface.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для парсинга конструкции ENDINTERFACE
// Ожидается, что текущий токен указывает на ключевое слово ENDINTERFACE
ast_node_t* parse_class_endinterface(parser_context_t* ctx) {
    if (!ctx) return NULL;

    // Проверяем, что текущий токен — ENDINTERFACE
    if (ctx->current.type != TOKEN_KEYWORD || strcmp(ctx->current.lexeme, "ENDINTERFACE") != 0) {
        parse_class_error(ctx, "Ожидалось ключевое слово ENDINTERFACE");
        return NULL;
    }

    // Создаем AST-узел для ENDINTERFACE
    ast_node_t* node = ast_node_create(AST_CLASS_ENDINTERFACE, ctx->current);

    // Продвигаемся к следующему токену
    parser_advance(ctx);

    // В синтаксисе может ожидаться точка или другой завершающий символ
    if (ctx->current.type == TOKEN_SYMBOL && strcmp(ctx->current.lexeme, ".") == 0) {
        parser_advance(ctx);
    } else {
        // Можно добавить предупреждение или ошибку, если точка обязательна
        // parse_class_warning("Ожидалась точка после ENDINTERFACE");
    }

    return node;
}

