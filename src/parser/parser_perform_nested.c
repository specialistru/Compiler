#include "parser_perform.h"
#include <stdio.h>

// Парсинг вложенного вызова PERFORM
// Поддержка вложенных блоков PERFORM внутри тела другой процедуры
ast_node_t* parse_perform_nested(parser_context_t* ctx) {
    // Проверяем, что текущий токен - PERFORM
    if (!parser_match(ctx, TOKEN_KEYWORD, "PERFORM")) {
        return NULL; // Не PERFORM - выходим
    }

    // Сохраняем имя подпрограммы
    token_t subroutine_token = expect_identifier(ctx);

    // Создаем AST узел для вызова PERFORM
    ast_node_t* node = ast_node_create(AST_PERFORM_NESTED, subroutine_token);

    // Далее парсим возможные параметры и тело (если есть)
    // Пример вложенного PERFORM с телом
    // PERFORM subroutine.
    //   PERFORM nested_subroutine.
    // END_PERFORM.

    // Проверяем тело PERFORM (опционально)
    if (parser_match(ctx, TOKEN_SYMBOL, ".")) {
        // Простое окончание вызова
        return node;
    }

    // Если после имени нет точки, пытаемся распарсить вложенный блок
    while (!parser_check(ctx, TOKEN_KEYWORD, "END_PERFORM")) {
        ast_node_t* child = parse_perform_nested(ctx);
        if (!child) {
            fprintf(stderr, "[PARSER ERROR] Ожидался вложенный PERFORM или END_PERFORM\n");
            exit(EXIT_FAILURE);
        }
        ast_node_add_child(node, child);
    }

    // Съедаем END_PERFORM
    parser_advance(ctx);

    return node;
}
