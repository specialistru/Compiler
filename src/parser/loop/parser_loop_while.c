#include "parser_loop_while.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>

// Функция разбора конструкции WHILE ... ENDWHILE
ast_node_t* parse_loop_while(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "WHILE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ключевой слово 'WHILE', найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    token_t while_token = ctx->previous;
    ast_node_t* while_node = ast_node_create(AST_LOOP_WHILE, while_token);

    // Разбор условия цикла
    ast_node_t* condition = parse_expression(ctx);
    if (!condition) {
        fprintf(stderr, "[PARSER ERROR] Ошибка при разборе условия WHILE\n");
        ast_node_free(while_node);
        return NULL;
    }
    ast_node_add_child(while_node, condition);

    // Опционально: разбор тела цикла
    ast_node_t* body = parse_loop_body(ctx);
    if (body) {
        ast_node_add_child(while_node, body);
    }

    // Проверка закрывающего ENDWHILE
    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDWHILE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался 'ENDWHILE' после тела цикла WHILE\n");
        ast_node_free(while_node);
        return NULL;
    }

    return while_node;
}
