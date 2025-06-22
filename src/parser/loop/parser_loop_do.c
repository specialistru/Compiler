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

/*

#include "parser_loop_do.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>

// Функция разбора конструкции DO ... ENDDO
ast_node_t* parse_loop_do(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "DO")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевой слово 'DO', найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    token_t do_token = ctx->previous;
    ast_node_t* do_node = ast_node_create(AST_LOOP_DO, do_token);

    // Опционально: тело цикла
    ast_node_t* body = parse_loop_body(ctx);
    if (!body) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе тела цикла DO\n");
        ast_node_free(do_node);
        return NULL;
    }
    ast_node_add_child(do_node, body);

    // Проверка закрывающего ENDDO
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDDO")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался 'ENDDO' после тела цикла DO\n");
        ast_node_free(do_node);
        return NULL;
    }

    // Опционально: условие выхода (WHILE/UNTIL) может идти после ENDDO
    // Если нужно - сюда можно добавить разбор условия, например:
    // if (parser_match(ctx, TOKEN_KEYWORD, "WHILE") || parser_match(ctx, TOKEN_KEYWORD, "UNTIL")) { ... }

    return do_node;
}


*/
