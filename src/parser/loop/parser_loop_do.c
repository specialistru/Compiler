// parser_loop_do.c
#include "parser_loop.h"
#include "parser_utils.h"
#include <stdio.h>

// Парсинг цикла DO ... ENDDO
ast_node_t* parse_loop_do(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "DO")) {
        parser_error(ctx, "Ожидалось ключевое слово DO");
        return NULL;
    }

    ast_node_t* do_node = ast_node_create(AST_LOOP_DO, ctx->previous_token);

    // Опционально: точка после DO (обязательна в некоторых стандартах)
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после DO");
        ast_node_free(do_node);
        return NULL;
    }

    // Разбор тела цикла до ENDDO
    while (!parser_check_keyword(ctx, "ENDDO") && ctx->current_token.type != TOKEN_EOF) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parser_error(ctx, "Ошибка при разборе тела DO цикла");
            ast_node_free(do_node);
            return NULL;
        }
        ast_node_add_child(do_node, stmt);
    }

    // Проверка наличия ENDDO
    if (!parser_match_keyword(ctx, "ENDDO")) {
        parser_error(ctx, "Ожидалось ключевое слово ENDDO");
        ast_node_free(do_node);
        return NULL;
    }

    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDDO");
        ast_node_free(do_node);
        return NULL;
    }

    return do_node;
}
