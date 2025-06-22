#include "parser_method.h"
#include <stdio.h>

// Вспомогательные объявления для разбора разных типов операторов
static ast_node_t* parse_expression(parser_t* parser);
static ast_node_t* parse_assignment(parser_t* parser);
static ast_node_t* parse_function_call(parser_t* parser);
static ast_node_t* parse_if_statement(parser_t* parser);
static ast_node_t* parse_while_statement(parser_t* parser);

// Главная функция разбора одного оператора/выражения в теле метода
ast_node_t* parse_statement(parser_t* parser) {
    if (parser_is_at_end(parser)) {
        return NULL;
    }

    // Определяем тип оператора по текущему токену
    token_t token = parser->current_token;

    if (token.type == TOKEN_KEYWORD) {
        if (strcmp(token.lexeme, "IF") == 0) {
            return parse_if_statement(parser);
        } else if (strcmp(token.lexeme, "WHILE") == 0) {
            return parse_while_statement(parser);
        }
        // Здесь можно добавить другие ключевые слова (FOR, RETURN, etc.)
    }

    // Если это идентификатор, возможно, присвоение или вызов функции
    if (token.type == TOKEN_IDENTIFIER) {
        // Посмотрим вперед, чтобы понять, что за оператор
        token_t next = parser_peek_next(parser);
        if (next.type == TOKEN_SYMBOL && strcmp(next.lexeme, "=") == 0) {
            return parse_assignment(parser);
        } else if (next.type == TOKEN_SYMBOL && strcmp(next.lexeme, "(") == 0) {
            return parse_function_call(parser);
        } else {
            // Простое выражение или ошибка
            return parse_expression(parser);
        }
    }

    // Если не распознали, ошибка синтаксиса
    fprintf(stderr, "[PARSE STATEMENT ERROR] Неожиданный токен '%s' на строке %d\n", token.lexeme, parser->current_line);
    return NULL;
}

// Заглушки для вспомогательных функций, которые нужно реализовать отдельно

static ast_node_t* parse_expression(parser_t* parser) {
    // TODO: Реализация парсинга выражений
    // Для упрощения здесь просто возвращаем NULL
    fprintf(stderr, "parse_expression() не реализован\n");
    return NULL;
}

static ast_node_t* parse_assignment(parser_t* parser) {
    // TODO: Реализация парсинга присвоения
    fprintf(stderr, "parse_assignment() не реализован\n");
    return NULL;
}

static ast_node_t* parse_function_call(parser_t* parser) {
    // TODO: Реализация парсинга вызова функции
    fprintf(stderr, "parse_function_call() не реализован\n");
    return NULL;
}

static ast_node_t* parse_if_statement(parser_t* parser) {
    // TODO: Реализация парсинга оператора IF
    fprintf(stderr, "parse_if_statement() не реализован\n");
    return NULL;
}

static ast_node_t* parse_while_statement(parser_t* parser) {
    // TODO: Реализация парсинга оператора WHILE
    fprintf(stderr, "parse_while_statement() не реализован\n");
    return NULL;
}
