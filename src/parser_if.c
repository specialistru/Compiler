#include "parser_if.h"
#include <stdio.h>

static ast_node_t* parse_expression(parser_context_t* ctx);

// Парсинг блока инструкций до следующего ключевого слова ELSEIF/ELSE/ENDIF
static ast_node_t* parse_block(parser_context_t* ctx) {
    ast_node_t* block = ast_node_create(AST_BLOCK, (token_t){TOKEN_UNKNOWN, NULL, 0, 0});
    while (ctx->current.type != TOKEN_EOF) {
        if (ctx->current.type == TOKEN_KEYWORD) {
            if (strcasecmp(ctx->current.lexeme, "ELSEIF") == 0 ||
                strcasecmp(ctx->current.lexeme, "ELSE") == 0 ||
                strcasecmp(ctx->current.lexeme, "ENDIF") == 0) {
                break;
            }
        }
        ast_node_t* stmt = parse_statement(ctx);
        if (!stmt) break;
        ast_node_add_child(block, stmt);
    }
    return block;
}

ast_node_t* parse_if_statement(parser_context_t* ctx) {
    if (!parser_match(ctx, TOKEN_KEYWORD, "IF")) return NULL;

    token_t if_tok = ctx->previous;
    ast_node_t* if_node = ast_node_create(AST_IF, if_tok);

    // Разбор условия
    ast_node_t* cond = parse_expression(ctx);
    if (!cond) {
        fprintf(stderr, "[PARSER ERROR] Ожидалось условие после IF\n");
        exit(EXIT_FAILURE);
    }
    ast_node_add_child(if_node, cond);

    // Разбор тела IF
    ast_node_t* if_block = parse_block(ctx);
    ast_node_add_child(if_node, if_block);

    // Обработка ELSEIF и ELSE
    while (ctx->current.type == TOKEN_KEYWORD) {
        if (parser_match(ctx, TOKEN_KEYWORD, "ELSEIF")) {
            token_t elseif_tok = ctx->previous;
            ast_node_t* elseif_node = ast_node_create(AST_ELSEIF, elseif_tok);

            ast_node_t* elseif_cond = parse_expression(ctx);
            if (!elseif_cond) {
                fprintf(stderr, "[PARSER ERROR] Ожидалось условие после ELSEIF\n");
                exit(EXIT_FAILURE);
            }
            ast_node_add_child(elseif_node, elseif_cond);

            ast_node_t* elseif_block = parse_block(ctx);
            ast_node_add_child(elseif_node, elseif_block);

            ast_node_add_child(if_node, elseif_node);
        }
        else if (parser_match(ctx, TOKEN_KEYWORD, "ELSE")) {
            token_t else_tok = ctx->previous;
            ast_node_t* else_node = ast_node_create(AST_ELSE, else_tok);

            ast_node_t* else_block = parse_block(ctx);
            ast_node_add_child(else_node, else_block);

            ast_node_add_child(if_node, else_node);
        }
        else {
            break;
        }
    }

    if (!parser_match(ctx, TOKEN_KEYWORD, "ENDIF")) {
        fprintf(stderr, "[PARSER ERROR] Ожидался ENDIF\n");
        exit(EXIT_FAILURE);
    }

    return if_node;
}
