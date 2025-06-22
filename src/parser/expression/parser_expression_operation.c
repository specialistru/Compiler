#include "parser_expression.h"
#include <stdio.h>
#include <string.h>

// Вспомогательная функция: возвращает приоритет оператора
static int get_operator_precedence(const char* op) {
    if (strcmp(op, "OR") == 0 || strcmp(op, "||") == 0) return 1;
    if (strcmp(op, "AND") == 0 || strcmp(op, "&&") == 0) return 2;
    if (strcmp(op, "=") == 0 || strcmp(op, "<>") == 0 || strcmp(op, "<") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) return 5;
    return 0; // Не оператор или низший приоритет
}

// Вспомогательная функция: проверяет, является ли токен оператором
static int is_operator(token_t token) {
    return token.type == TOKEN_SYMBOL || token.type == TOKEN_KEYWORD;
}

// Парсинг выражения с учетом приоритета (рекурсивный разбор)
static ast_node_t* parse_expression_prec(parser_context_t* ctx, int min_prec);

// Основная функция парсинга операций
ast_node_t* parse_expression_operation(parser_context_t* ctx) {
    return parse_expression_prec(ctx, 1);
}

static ast_node_t* parse_expression_prec(parser_context_t* ctx, int min_prec) {
    // Сначала парсим левый операнд — термин (идентификатор, число, скобки и т.п.)
    ast_node_t* left = parse_expression_term(ctx);
    if (!left) return NULL;

    while (is_operator(ctx->current)) {
        const char* op = ctx->current.lexeme;
        int prec = get_operator_precedence(op);
        if (prec < min_prec) break;

        token_t op_token = ctx->current;
        parser_next_token(ctx); // Сдвиг после оператора

        // Для операторов с ассоциативностью слева направо, следующий минимальный приоритет — prec + 1
        ast_node_t* right = parse_expression_prec(ctx, prec + 1);
        if (!right) {
            fprintf(stderr, "[PARSER ERROR] Ожидался операнд после оператора '%s'\n", op);
            ast_node_destroy(left);
            return NULL;
        }

        // Создаем AST узел операции и добавляем левого и правого ребенка
        ast_node_t* op_node = ast_node_create(AST_EXPR_OPERATION, op_token);
        ast_node_add_child(op_node, left);
        ast_node_add_child(op_node, right);

        left = op_node; // Новый левый операнд — это результат операции
    }

    return left;
}
