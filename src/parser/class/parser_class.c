#include "parser_class.h"
#include "parser_class_attributes.h"
#include "parser_class_def.h"
#include "parser_class_definition.h"
#include "parser_class_end.h"
#include "parser_class_endclass.h"
#include "parser_class_endinterface.h"
#include "parser_class_errors.h"
#include "parser_class_implementation.h"
#include "parser_class_interface.h"
#include "parser_class_method.h"
#include "parser_class_method_def.h"
#include "parser_class_method_definition.h"
#include "parser_class_method_impl.h"
#include "parser_class_simple.h"
#include "parser_class_visibility.h"
#include <stdio.h>
#include <string.h>

// Главная функция для разбора конструкций класса
ast_node_t* parse_class(parser_context_t* ctx) {
    if (ctx->current.type != TOKEN_KEYWORD) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово для начала класса, найдено: %s\n", ctx->current.lexeme);
        return NULL;
    }

    // В зависимости от ключевого слова выбираем соответствующий парсер
    if (strcmp(ctx->current.lexeme, "CLASS") == 0) {
        return parse_class_def(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "CLASS-DEFINITION") == 0) {
        return parse_class_definition(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "CLASS-IMPLEMENTATION") == 0) {
        return parse_class_implementation(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "CLASS-INTERFACE") == 0) {
        return parse_class_interface(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "CLASS-END") == 0) {
        return parse_class_end(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "ENDCLASS") == 0) {
        return parse_class_endclass(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "ENDINTERFACE") == 0) {
        return parse_class_endinterface(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "METHOD") == 0) {
        return parse_class_method(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "METHOD-DEFINITION") == 0) {
        return parse_class_method_definition(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "METHOD-IMPLEMENTATION") == 0) {
        return parse_class_method_impl(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "METHOD-DEF") == 0) {
        return parse_class_method_def(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "ATTRIBUTES") == 0) {
        return parse_class_attributes(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "VISIBILITY") == 0) {
        return parse_class_visibility(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "SIMPLE") == 0) {
        return parse_class_simple(ctx);
    }
    else if (strcmp(ctx->current.lexeme, "ERRORS") == 0) {
        return parse_class_errors(ctx);
    }
    else {
        fprintf(stderr, "[PARSER ERROR] Неизвестная конструкция класса: %s\n", ctx->current.lexeme);
        return NULL;
    }
}

