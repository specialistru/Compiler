#ifndef PARSER_LOOP_H
#define PARSER_LOOP_H

#include "parser_context.h"
#include "ast.h"

// Функции для парсинга различных конструкций циклов

// Парсинг цикла DO ... ENDDO
ast_node_t* parse_loop_do(parser_context_t* ctx);

// Парсинг цикла WHILE ... ENDWHILE
ast_node_t* parse_loop_while(parser_context_t* ctx);

// Парсинг цикла FOR ... ENDFOR
ast_node_t* parse_loop_for(parser_context_t* ctx);

// Парсинг цикла LOOP ... ENDLOOP
ast_node_t* parse_loop_loop(parser_context_t* ctx);

// Общая функция парсинга цикла (вызывает конкретные по типу)
ast_node_t* parse_loop(parser_context_t* ctx);

#endif // PARSER_LOOP_H
