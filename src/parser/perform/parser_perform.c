#include "parser_perform.h"
#include "parser_perform_simple.h"
#include "parser_perform_nested.h"
#include "parser_perform_logical_ops.h"
#include "parser_perform_syntax_error.h"
#include "parser_perform_complex.h"
#include "parser_perform_and_or.h"
#include "parser_perform_errors.h"
#include "parser_perform_elseif.h"
#include "parser_perform_else.h"
#include "parser_perform_not.h"
#include "parser_perform_bracketed.h"
#include "parser_perform_deep_nested.h"
#include "parser_perform_complex_body.h"
#include <stdio.h>
#include <string.h>

// Основная функция разбора конструкции PERFORM
ast_node_t* parse_perform(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_KEYWORD || strcmp(ctx->current.lexeme, "PERFORM") != 0) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово PERFORM, но найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    parser_advance(ctx); // перейти к следующему токену после PERFORM

    // Далее анализируем следующий токен, чтобы понять какой тип PERFORM обрабатывать
    if (ctx->current.type == TOKEN_IDENTIFIER) {
        // Простое выполнение процедуры
        return parse_perform_simple(ctx);
    } 
    else if (ctx->current.type == TOKEN_KEYWORD) {
        // Сложные конструкции в зависимости от ключевых слов
        if (strcmp(ctx->current.lexeme, "NESTED") == 0) {
            return parse_perform_nested(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "LOGICAL_OPS") == 0) {
            return parse_perform_logical_ops(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "COMPLEX") == 0) {
            return parse_perform_complex(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "AND_OR") == 0) {
            return parse_perform_and_or(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "ELSEIF") == 0) {
            return parse_perform_elseif(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "ELSE") == 0) {
            return parse_perform_else(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "NOT") == 0) {
            return parse_perform_not(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "BRACKETED") == 0) {
            return parse_perform_bracketed(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "DEEP_NESTED") == 0) {
            return parse_perform_deep_nested(ctx);
        }
        else if (strcmp(ctx->current.lexeme, "COMPLEX_BODY") == 0) {
            return parse_perform_complex_body(ctx);
        }
        else {
            fprintf(stderr, "[PARSER ERROR] Неизвестная конструкция PERFORM: %s\n", ctx->current.lexeme);
            return NULL;
        }
    }
    else {
        // Если не распознано, пробуем базовый разбор простого PERFORM
        return parse_perform_simple(ctx);
    }
}
