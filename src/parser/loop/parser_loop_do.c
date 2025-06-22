// parser_loop_do.c
#include "parser_loop.h"
#include "parser_utils.h"
#include <stdio.h>

// Парсит цикл DO ... ENDDO
ast_node_t* parse_loop_do(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "DO")) {
        parser_error(ctx, "Ожидалось ключевое слово DO");
        return NULL;
    }

    // Создаем AST узел для DO цикла
    ast_node_t* do_node = ast_node_create(AST_LOOP_DO, ctx->previous_token);

    // Опционально: ожидание точки после DO
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ключевого слова DO");
        ast_node_free(do_node);
        return NULL;
    }

    // Парсим тело цикла до ENDDO
    while (!parser_check_keyword(ctx, "ENDDO") && ctx->current_token.type != TOKEN_EOF) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parser_error(ctx, "Ошибка при разборе тела DO цикла");
            ast_node_free(do_node);
            return NULL;
        }
        ast_node_add_child(do_node, stmt);
    }

    // Ожидаем ENDDO
    if (!parser_match_keyword(ctx, "ENDDO")) {
        parser_error(ctx, "Ожидалось ключевое слово ENDDO для завершения DO цикла");
        ast_node_free(do_node);
        return NULL;
    }

    // Ожидаем точку после ENDDO
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDDO");
        ast_node_free(do_node);
        return NULL;
    }

    return do_node;
}
