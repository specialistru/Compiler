#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Вспомогательная функция для парсинга логических операторов AND, OR, NOT
static ast_node_t* parse_logical_expr(parser_t* parser);

// Вспомогательная функция для парсинга базовых терминальных выражений (идентификаторы, числа, вызовы функций)
static ast_node_t* parse_primary_expr(parser_t* parser);

// Вспомогательная функция для парсинга выражения в скобках
static ast_node_t* parse_paren_expr(parser_t* parser);

// Парсинг условия if
static ast_node_t* parse_condition(parser_t* parser) {
    // Здесь парсим логическое выражение с поддержкой AND, OR, NOT, скобок, вызовов функций
    return parse_logical_expr(parser);
}

// Парсинг блока кода (список инструкций)
static ast_node_t* parse_block(parser_t* parser);

// Главная функция парсинга IF конструкции
ast_node_t* parse_if(parser_t* parser) {
    // Предполагается, что текущий токен - IF
    token_t if_token = parser->current_token;
    if (!match_token(parser, TOKEN_KEYWORD, "IF")) {
        fprintf(stderr, "Expected IF token\n");
        return NULL;
    }

    ast_node_t* if_node = ast_node_create(AST_IF, if_token);

    // Парсим условие
    ast_node_t* condition = parse_condition(parser);
    if (!condition) {
        fprintf(stderr, "Failed to parse IF condition at line %d\n", parser->current_token.line);
        ast_node_free(if_node);
        return NULL;
    }
    ast_node_add_child(if_node, condition);

    // Тело IF (блок кода)
    ast_node_t* then_block = parse_block(parser);
    if (!then_block) {
        fprintf(stderr, "Failed to parse IF block at line %d\n", parser->current_token.line);
        ast_node_free(if_node);
        return NULL;
    }
    ast_node_add_child(if_node, then_block);

    // Парсим опциональные ELSEIF и ELSE
    while (true) {
        if (match_token(parser, TOKEN_KEYWORD, "ELSEIF")) {
            token_t elseif_token = parser->previous_token;
            ast_node_t* elseif_node = ast_node_create(AST_ELSEIF, elseif_token);

            ast_node_t* elseif_condition = parse_condition(parser);
            if (!elseif_condition) {
                fprintf(stderr, "Failed to parse ELSEIF condition at line %d\n", parser->current_token.line);
                ast_node_free(if_node);
                return NULL;
            }
            ast_node_add_child(elseif_node, elseif_condition);

            ast_node_t* elseif_block = parse_block(parser);
            if (!elseif_block) {
                fprintf(stderr, "Failed to parse ELSEIF block at line %d\n", parser->current_token.line);
                ast_node_free(if_node);
                return NULL;
            }
            ast_node_add_child(elseif_node, elseif_block);

            ast_node_add_child(if_node, elseif_node);
        } else if (match_token(parser, TOKEN_KEYWORD, "ELSE")) {
            token_t else_token = parser->previous_token;
            ast_node_t* else_node = ast_node_create(AST_ELSE, else_token);

            ast_node_t* else_block = parse_block(parser);
            if (!else_block) {
                fprintf(stderr, "Failed to parse ELSE block at line %d\n", parser->current_token.line);
                ast_node_free(if_node);
                return NULL;
            }
            ast_node_add_child(else_node, else_block);

            ast_node_add_child(if_node, else_node);
        } else {
            break; // Нет ELSEIF или ELSE - выходим
        }
    }

    // Ожидаем ENDIF
    if (!match_token(parser, TOKEN_KEYWORD, "ENDIF")) {
        fprintf(stderr, "Expected ENDIF token to close IF block at line %d\n", parser->current_token.line);
        ast_node_free(if_node);
        return NULL;
    }

    token_t endif_token = parser->previous_token;
    ast_node_t* endif_node = ast_node_create(AST_ENDIF, endif_token);
    ast_node_add_child(if_node, endif_node);

    return if_node;
}

// --- Реализация вспомогательных функций ---

// Парсинг блока инструкций (пока упрощённо: пока не ENDIF, ELSEIF, ELSE)
static ast_node_t* parse_block(parser_t* parser) {
    ast_node_t* block_node = ast_node_create(AST_BLOCK, parser->current_token);

    while (true) {
        if (parser->current_token.type == TOKEN_EOF) {
            fprintf(stderr, "Unexpected EOF inside block\n");
            ast_node_free(block_node);
            return NULL;
        }
        // Если следующий токен - ключевое слово, закрывающее блок IF/ELSEIF/ELSE - выходим
        if ((parser->current_token.type == TOKEN_KEYWORD) &&
            (strcasecmp(parser->current_token.lexeme, "ENDIF") == 0 ||
             strcasecmp(parser->current_token.lexeme, "ELSEIF") == 0 ||
             strcasecmp(parser->current_token.lexeme, "ELSE") == 0)) {
            break;
        }

        // Здесь вместо полной реализации парсера других инструкций вставим упрощённый заглушечный узел
        // Обычно тут вызывается парсер следующей инструкции
        ast_node_t* stmt_node = ast_node_create(AST_UNKNOWN, parser->current_token);
        ast_node_add_child(block_node, stmt_node);

        // Пропускаем текущий токен, чтобы избежать зацикливания
        if (!advance_token(parser)) {
            ast_node_free(block_node);
            return NULL;
        }
    }
    return block_node;
}

// --- Парсинг выражений ---

// Парсинг базового терминала (идентификатор, число, вызов функции)
static ast_node_t* parse_primary_expr(parser_t* parser) {
    token_t tok = parser->current_token;
    if (tok.type == TOKEN_IDENTIFIER) {
        ast_node_t* node = ast_node_create(AST_EXPR_IDENTIFIER, tok);
        advance_token(parser);
        // Проверяем, вызов ли это функции (следующий токен - '(')
        if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, "(") == 0) {
            // Пропускаем '('
            advance_token(parser);
            // TODO: парсинг параметров функции (пропущено для упрощения)
            // Пропускаем ')'
            if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
                advance_token(parser);
            } else {
                fprintf(stderr, "Expected ')' after function call at line %d\n", parser->current_token.line);
            }
            ast_node_t* func_call_node = ast_node_create(AST_EXPR_FUNCTION_CALL, tok);
            ast_node_add_child(func_call_node, node);
            return func_call_node;
        }
        return node;
    } else if (tok.type == TOKEN_NUMBER) {
        ast_node_t* node = ast_node_create(AST_EXPR_LITERAL, tok);
        advance_token(parser);
        return node;
    }
    // Добавьте сюда поддержку строк, вызовов методов и т.п.
    return NULL;
}

// Парсинг выражения в скобках
static ast_node_t* parse_paren_expr(parser_t* parser) {
    if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, "(") == 0) {
        advance_token(parser);
        ast_node_t* expr = parse_logical_expr(parser);
        if (parser->current_token.type == TOKEN_SYMBOL && strcmp(parser->current_token.lexeme, ")") == 0) {
            advance_token(parser);
            return expr;
        } else {
            fprintf(stderr, "Expected ')' at line %d\n", parser->current_token.line);
            ast_node_free(expr);
            return NULL;
        }
    }
    return parse_primary_expr(parser);
}

// Парсинг NOT выражений
static ast_node_t* parse_not_expr(parser_t* parser) {
    if (parser->current_token.type == TOKEN_KEYWORD && strcasecmp(parser->current_token.lexeme, "NOT") == 0) {
        token_t not_token = parser->current_token;
        advance_token(parser);
        ast_node_t* expr = parse_not_expr(parser);
        if (!expr) return NULL;
        ast_node_t* node = ast_node_create(AST_EXPR_UNARY_OP, not_token);
        ast_node_add_child(node, expr);
        return node;
    }
    return parse_paren_expr(parser);
}

// Парсинг бинарных операций AND/OR
static ast_node_t* parse_and_or_expr(parser_t* parser) {
    ast_node_t* left = parse_not_expr(parser);
    if (!left) return NULL;

    while (parser->current_token.type == TOKEN_KEYWORD &&
          (strcasecmp(parser->current_token.lexeme, "AND") == 0 || strcasecmp(parser->current_token.lexeme, "OR") == 0)) {
        token_t op_token = parser->current_token;
        advance_token(parser);
        ast_node_t* right = parse_not_expr(parser);
        if (!right) {
            ast_node_free(left);
            return NULL;
        }
        ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
        ast_node_add_child(bin_op, left);
        ast_node_add_child(bin_op, right);
        left = bin_op;
    }
    return left;
}

// Парсинг базового сравнения (например, x = 1)
static ast_node_t* parse_comparison_expr(parser_t* parser) {
    ast_node_t* left = parse_primary_expr(parser);
    if (!left) return NULL;

    // Поддержка операторов сравнения =, <>, >, <, >=, <=
    if (parser->current_token.type == TOKEN_SYMBOL ||
        (parser->current_token.type == TOKEN_OPERATOR)) {
        const char* op = parser->current_token.lexeme;
        if (strcmp(op, "=") == 0 || strcmp(op, "<>") == 0 ||
            strcmp(op, ">") == 0 || strcmp(op, "<") == 0 ||
            strcmp(op, ">=") == 0 || strcmp(op, "<=") == 0) {
            token_t op_token = parser->current_token;
            advance_token(parser);

            ast_node_t* right = parse_primary_expr(parser);
            if (!right) {
                ast_node_free(left);
                return NULL;
            }

            ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
            ast_node_add_child(bin_op, left);
            ast_node_add_child(bin_op, right);
            return bin_op;
        }
    }
    return left;
}

// Вершина - логические операции AND, OR над сравнениями
static ast_node_t* parse_logical_expr(parser_t* parser) {
    ast_node_t* left = parse_comparison_expr(parser);
    if (!left) return NULL;

    while (parser->current_token.type == TOKEN_KEYWORD &&
          (strcasecmp(parser->current_token.lexeme, "AND") == 0 || strcasecmp(parser->current_token.lexeme, "OR") == 0)) {
        token_t op_token = parser->current_token;
        advance_token(parser);
        ast_node_t* right = parse_comparison_expr(parser);
        if (!right) {
            ast_node_free(left);
            return NULL;
        }
        ast_node_t* bin_op = ast_node_create(AST_EXPR_BINARY_OP, op_token);
        ast_node_add_child(bin_op, left);
        ast_node_add_child(bin_op, right);
        left = bin_op;
    }
    return left;
}
