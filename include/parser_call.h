#ifndef PARSER_CALL_H
#define PARSER_CALL_H

#include "ast.h"
#include "lexer.h"
#include "parser.h"

//
// Основные функции парсинга вызовов CALL FUNCTION
//

// Парсинг простого вызова функции: CALL FUNCTION 'FUNC'.
ast_node_t* parse_call_simple(parser_context_t* ctx);

// Парсинг вызова функции с параметрами: EXPORTING, IMPORTING, CHANGING
ast_node_t* parse_call_parameters(parser_context_t* ctx);

// Парсинг возврата значений (IMPORTING и RETURNING)
ast_node_t* parse_call_return_values(parser_context_t* ctx);

// Парсинг сложного вызова: параметры, исключения, возврат, точка
ast_node_t* parse_call_complex(parser_context_t* ctx);

//
// Дополнительные конструкции
//

// Парсинг вложенных вызовов: CALL FUNCTION ... внутри CALL FUNCTION ...
ast_node_t* parse_call_nested(parser_context_t* ctx);

// Парсинг динамического вызова: CALL FUNCTION func_name (где func_name — переменная)
ast_node_t* parse_call_dynamic(parser_context_t* ctx);

// Вызов с указанием имени функции в скобках: CALL FUNCTION('FUNC')
ast_node_t* parse_call_bracketed(parser_context_t* ctx);

// Вызов функции в цикле: DO ... CALL FUNCTION ... ENDDO
ast_node_t* parse_call_loop(parser_context_t* ctx);

// Обработка секции EXCEPTIONS: ... EXCEPTIONS error1 = 1 error2 = 2 ...
ast_node_t* parse_call_exceptions(parser_context_t* ctx);

//
// Обработка ошибок
//

// Вывод синтаксической ошибки вызова CALL FUNCTION
void parse_call_error(const char* message, parser_context_t* ctx);

#endif // PARSER_CALL_H
