// parser_class_interface.c

#include "parser_class.h"
#include <stdio.h>
#include <stdlib.h>

// Парсинг определения интерфейса класса
// Пример: INTERFACE interface_name
ast_node_t* parse_class_interface(parser_context_t* ctx) {
    if (!ctx) return NULL;

    // Проверка ключевого слова INTERFACE
    if (!parser_match_keyword(ctx, "INTERFACE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово INTERFACE\n");
        return NULL;
    }

    // Ожидаем имя интерфейса (идентификатор)
    if (ctx->current.type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось имя интерфейса\n");
        return NULL;
    }
    token_t interface_name_token = ctx->current;
    parser_advance(ctx);

    // Создаем AST узел для интерфейса
    ast_node_t* interface_node = ast_node_create(AST_CLASS_INTERFACE, interface_name_token);

    // Парсим тело интерфейса (список методов, атрибутов)
    while (!parser_check_keyword(ctx, "ENDINTERFACE") && ctx->current.type != TOKEN_EOF) {
        ast_node_t* member_node = parse_class_member(ctx);
        if (!member_node) {
            fprintf(stderr, "[PARSER ERROR] Ошибка парсинга члена интерфейса\n");
            ast_node_destroy(interface_node);
            return NULL;
        }
        ast_node_add_child(interface_node, member_node);
    }

    // Проверяем ключевое слово ENDINTERFACE
    if (!parser_match_keyword(ctx, "ENDINTERFACE")) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось ключевое слово ENDINTERFACE\n");
        ast_node_destroy(interface_node);
        return NULL;
    }

    return interface_node;
}

