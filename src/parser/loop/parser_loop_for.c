// parser_loop_for.c
#include "parser_loop.h"
#include "parser_utils.h"
#include <stdio.h>

// Пример:
// FOR i = 1 TO 10.
//    ... тело ...
// ENDFOR.

ast_node_t* parse_loop_for(parser_context_t* ctx) {
    if (!parser_match_keyword(ctx, "FOR")) {
        parser_error(ctx, "Ожидалось ключевое слово FOR");
        return NULL;
    }

    ast_node_t* for_node = ast_node_create(AST_LOOP_FOR, ctx->previous_token);

    // Ожидаем идентификатор цикла
    if (ctx->current_token.type != TOKEN_IDENTIFIER) {
        parser_error(ctx, "Ожидался идентификатор цикла после FOR");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_t* var_node = ast_node_create(AST_EXPR_IDENTIFIER, ctx->current_token);
    parser_advance(ctx);

    ast_node_add_child(for_node, var_node);

    // Ожидаем '='
    if (!parser_match_symbol(ctx, "=")) {
        parser_error(ctx, "Ожидался '=' после идентификатора в цикле FOR");
        ast_node_free(for_node);
        return NULL;
    }

    // Разбор выражения начального значения
    ast_node_t* start_expr = parse_expression(ctx);
    if (!start_expr) {
        parser_error(ctx, "Ошибка при разборе начального значения в FOR");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_add_child(for_node, start_expr);

    // Ожидаем TO или DOWNTO
    if (parser_match_keyword(ctx, "TO")) {
        ast_node_t* to_node = ast_node_create(AST_KEYWORD_TO, ctx->previous_token);
        ast_node_add_child(for_node, to_node);
    } else if (parser_match_keyword(ctx, "DOWNTO")) {
        ast_node_t* downto_node = ast_node_create(AST_KEYWORD_DOWNTO, ctx->previous_token);
        ast_node_add_child(for_node, downto_node);
    } else {
        parser_error(ctx, "Ожидалось ключевое слово TO или DOWNTO в цикле FOR");
        ast_node_free(for_node);
        return NULL;
    }

    // Разбор выражения конечного значения
    ast_node_t* end_expr = parse_expression(ctx);
    if (!end_expr) {
        parser_error(ctx, "Ошибка при разборе конечного значения в FOR");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_add_child(for_node, end_expr);

    // Ожидаем точку после заголовка FOR
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после заголовка FOR");
        ast_node_free(for_node);
        return NULL;
    }

    // Разбор тела цикла до ENDFOR
    while (!parser_check_keyword(ctx, "ENDFOR") && ctx->current_token.type != TOKEN_EOF) {
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) {
            parser_error(ctx, "Ошибка при разборе тела цикла FOR");
            ast_node_free(for_node);
            return NULL;
        }
        ast_node_add_child(for_node, stmt);
    }

    // Ожидаем ENDFOR
    if (!parser_match_keyword(ctx, "ENDFOR")) {
        parser_error(ctx, "Ожидалось ключевое слово ENDFOR");
        ast_node_free(for_node);
        return NULL;
    }

    // Ожидаем точку после ENDFOR
    if (!parser_match_symbol(ctx, ".")) {
        parser_error(ctx, "Ожидалась '.' после ENDFOR");
        ast_node_free(for_node);
        return NULL;
    }

    return for_node;
}

/*

#include "parser_loop_for.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>

// Функция разбора конструкции FOR ... ENDFOR
ast_node_t* parse_loop_for(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "FOR")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевой слово 'FOR', найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    token_t for_token = ctx->previous;
    ast_node_t* for_node = ast_node_create(AST_LOOP_FOR, for_token);

    // Разбор переменной цикла (ожидается идентификатор)
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидался идентификатор после 'FOR', найдено: %s\n", ctx->current.lexeme);
        ast_node_free(for_node);
        return NULL;
    }
    token_t loop_var = ctx->current;
    parser_advance(ctx);
    ast_node_t* var_node = ast_node_create(AST_EXPR_IDENTIFIER, loop_var);
    ast_node_add_child(for_node, var_node);

    // Ожидается '='
    if (!parser_match(ctx, TOKEN_SYMBOL, "=")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался символ '=' после переменной цикла\n");
        ast_node_free(for_node);
        return NULL;
    }

    // Разбор начального значения (выражение)
    ast_node_t* start_expr = parse_expression(ctx);
    if (!start_expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе начального значения цикла FOR\n");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_add_child(for_node, start_expr);

    // Ожидается ключевое слово TO
    if (!parser_match(ctx, TOKEN_KEYWORD, "TO")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевое слово 'TO' после начального значения цикла\n");
        ast_node_free(for_node);
        return NULL;
    }

    // Разбор конечного значения (выражение)
    ast_node_t* end_expr = parse_expression(ctx);
    if (!end_expr) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе конечного значения цикла FOR\n");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_add_child(for_node, end_expr);

    // Опционально: STEP
    if (parser_match(ctx, TOKEN_KEYWORD, "STEP")) {
        ast_node_t* step_expr = parse_expression(ctx);
        if (!step_expr) {
            fprintf(stderr, "[PARSER ERROR] Ошибка при разборе шага цикла FOR\n");
            ast_node_free(for_node);
            return NULL;
        }
        ast_node_add_child(for_node, step_expr);
    }

    // Разбор тела цикла
    ast_node_t* body = parse_loop_body(ctx);
    if (!body) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе тела цикла FOR\n");
        ast_node_free(for_node);
        return NULL;
    }
    ast_node_add_child(for_node, body);

    // Проверка закрывающего ENDFOR
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDFOR")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался 'ENDFOR' после тела цикла FOR\n");
        ast_node_free(for_node);
        return NULL;
    }

    return for_node;
}

*/
