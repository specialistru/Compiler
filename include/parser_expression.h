#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

#include "parser_types.h"  // Определения parser_context_t, ast_node_t, token_t и т.п.

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Парсит функцию в выражении.
 * 
 * Обрабатывает синтаксис вызова или определения функции внутри выражения.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST, представляющий функцию или вызов функции.
 */
ast_node_t* parse_expression_function(parser_context_t* ctx);

/**
 * @brief Парсит логические операции в выражении.
 * 
 * Обрабатывает операции AND, OR, NOT и другие логические выражения.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для логического выражения.
 */
ast_node_t* parse_expression_logical(parser_context_t* ctx);

/**
 * @brief Парсит вызов функции в выражении.
 * 
 * Обрабатывает синтаксис вызова функции с аргументами.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для вызова функции.
 */
ast_node_t* parse_expression_function_call(parser_context_t* ctx);

/**
 * @brief Парсит литералы в выражении.
 * 
 * Обрабатывает константные значения: числа, строки, булевы значения и т.п.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST с литеральным значением.
 */
ast_node_t* parse_expression_literal(parser_context_t* ctx);

/**
 * @brief Парсит идентификаторы в выражении.
 * 
 * Обрабатывает имена переменных, функций, полей и прочих символов.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST с идентификатором.
 */
ast_node_t* parse_expression_identifier(parser_context_t* ctx);

/**
 * @brief Парсит тернарные операторы в выражении.
 * 
 * Обрабатывает условные выражения вида `условие ? выражение1 : выражение2`.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для тернарного оператора.
 */
ast_node_t* parse_expression_ternary(parser_context_t* ctx);

/**
 * @brief Парсит операторы в выражении.
 * 
 * Обрабатывает арифметические, побитовые и другие операторы.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для оператора.
 */
ast_node_t* parse_expression_operator(parser_context_t* ctx);

/**
 * @brief Парсит переменные в выражении.
 * 
 * Обрабатывает обращения к переменным, возможно с модификаторами.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для переменной.
 */
ast_node_t* parse_expression_variable(parser_context_t* ctx);

/**
 * @brief Парсит скобочные выражения.
 * 
 * Обрабатывает выражения в круглых скобках, для управления приоритетом.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для скобочного выражения.
 */
ast_node_t* parse_expression_bracket(parser_context_t* ctx);

/**
 * @brief Парсит сложные выражения.
 * 
 * Обрабатывает составные выражения, включая вложенные структуры.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для сложного выражения.
 */
ast_node_t* parse_expression_complex(parser_context_t* ctx);

/**
 * @brief Парсит условные выражения.
 * 
 * Обрабатывает конструкции с условиями (if-else в выражениях).
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для условного выражения.
 */
ast_node_t* parse_expression_conditional(parser_context_t* ctx);

/**
 * @brief Парсит операции присваивания в выражениях.
 * 
 * Обрабатывает присваивание значений переменным.
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для операции присваивания.
 */
ast_node_t* parse_expression_assignment(parser_context_t* ctx);

/**
 * @brief Парсит доступ к элементам массивов.
 * 
 * Обрабатывает выражения с индексами массива, например arr[5].
 * 
 * @param ctx Контекст парсера.
 * @return ast_node_t* Узел AST для обращения к элементу массива.
 */
ast_node_t* parse_expression_array_access(parser_context_t* ctx);

#ifdef __cplusplus
}
#endif

#endif // PARSER_EXPRESSION_H
