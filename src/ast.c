#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Создание нового AST-узла
ast_node_t* ast_node_create(ast_node_type_t type, token_t token) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    node->type = type;
    node->token = token;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

// Добавление дочернего узла
void ast_node_add_child(ast_node_t* parent, ast_node_t* child) {
    if (!parent || !child) return;
    parent->children = realloc(parent->children, sizeof(ast_node_t*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

// Освобождение AST
void ast_node_free(ast_node_t* node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; ++i)
        ast_node_free(node->children[i]);

    free(node->children);
    lexer_free_token(&node->token);
    free(node);
}

// Человеко-читаемые имена узлов
static const char* ast_node_type_name(ast_node_type_t type) {
    switch (type) {
        // Основной корень дерева
        case AST_PROGRAM: return "PROGRAM";                  // Главный узел программы

        // Объявления
        case AST_DATA: return "DATA";                        // Объявление переменной
        case AST_CONSTANTS: return "CONSTANTS";              // Объявление константы
        case AST_PARAMETERS: return "PARAMETERS";            // Объявление параметра ввода
        case AST_SELECT_OPTIONS: return "SELECT_OPTIONS";    // Диапазон выбора
        case AST_TABLES: return "TABLES";                    // Табличная переменная
        case AST_TYPES: return "TYPES";                      // Пользовательский тип
        case AST_RANGES: return "RANGES";                    // Диапазон значений (как SELECT-OPTIONS)

        // Управляющие конструкции
        case AST_IF: return "IF";                            // Начало условия
        case AST_ELSEIF: return "ELSEIF";                    // Альтернативное условие
        case AST_ELSE: return "ELSE";                        // Блок иначе
        case AST_ENDIF: return "ENDIF";                      // Конец условия
        case AST_DO: return "DO";                            // Начало цикла DO
        case AST_ENDDO: return "ENDDO";                      // Конец DO
        case AST_WHILE: return "WHILE";                      // Цикл WHILE
        case AST_ENDWHILE: return "ENDWHILE";                // Завершение WHILE
        case AST_LOOP: return "LOOP";                        // LOOP AT
        case AST_ENDLOOP: return "ENDLOOP";                  // Завершение LOOP
        case AST_CASE: return "CASE";                        // Условный CASE
        case AST_WHEN: return "WHEN";                        // Ветка WHEN
        case AST_ENDCASE: return "ENDCASE";                  // Завершение CASE
        case AST_EXIT: return "EXIT";                        // Преждевременный выход
        case AST_CONTINUE: return "CONTINUE";                // Пропуск итерации
        case AST_CHECK: return "CHECK";                      // Проверка условия
        case AST_RETURN: return "RETURN";                    // Возврат из метода / функции

        // Вызовы
        case AST_PERFORM: return "PERFORM";                  // Вызов FORM
        case AST_CALL_FUNCTION: return "CALL_FUNCTION";      // Вызов внешней функции
        case AST_CALL_METHOD: return "CALL_METHOD";          // Вызов метода
        case AST_SUBMIT: return "SUBMIT";                    // Запуск внешнего отчета
        case AST_WAIT: return "WAIT";                        // Ожидание (временное)
        case AST_FORM: return "FORM";                        // Начало подпрограммы
        case AST_ENDFORM: return "ENDFORM";                  // Завершение FORM
        case AST_FUNCTION: return "FUNCTION";                // Начало функции
        case AST_ENDFUNCTION: return "ENDFUNCTION";          // Завершение функции
        case AST_MODULE: return "MODULE";                    // Модуль экрана
        case AST_ENDMODULE: return "ENDMODULE";              // Завершение модуля

        // Объектно-ориентированное программирование
        case AST_CLASS_DEF: return "CLASS_DEF";              // Определение класса
        case AST_ENDCLASS: return "ENDCLASS";                // Завершение класса
        case AST_METHOD_DEF: return "METHOD_DEF";            // Определение метода
        case AST_ENDMETHOD: return "ENDMETHOD";              // Завершение метода
        case AST_INTERFACE_DEF: return "INTERFACE_DEF";      // Интерфейс
        case AST_ENDINTERFACE: return "ENDINTERFACE";        // Завершение интерфейса

        // Исключения
        case AST_TRY: return "TRY";                          // Начало блока TRY
        case AST_CATCH: return "CATCH";                      // Обработка исключения
        case AST_CLEANUP: return "CLEANUP";                  // Очистка (после TRY/CATCH)
        case AST_ENDTRY: return "ENDTRY";                    // Завершение TRY
        case AST_RAISE: return "RAISE";                      // Генерация исключения
        case AST_RAISE_EXCEPTION: return "RAISE_EXCEPTION";  // Поднятие исключения

        // Выражения и операции
        case AST_ASSIGNMENT: return "ASSIGNMENT";            // Присваивание (=)
        case AST_EXPR_BINARY_OP: return "EXPR_BINARY_OP";    // Бинарная операция (a + b)
        case AST_EXPR_UNARY_OP: return "EXPR_UNARY_OP";      // Унарная операция (-a)
        case AST_EXPR_LITERAL: return "LITERAL";             // Число, строка, логическое значение
        case AST_EXPR_IDENTIFIER: return "IDENTIFIER";       // Имя переменной/метода
        case AST_EXPR_FUNCTION_CALL: return "FUNCTION_CALL"; // Вызов функции в выражении
        case AST_EXPR_METHOD_CALL: return "METHOD_CALL";     // Вызов метода в выражении

        // Работа с таблицами
        case AST_SELECT: return "SELECT";                    // Запрос SELECT
        case AST_SELECT_SINGLE: return "SELECT_SINGLE";      // SELECT SINGLE
        case AST_ENDSELECT: return "ENDSELECT";              // Конец SELECT
        case AST_READ_TABLE: return "READ_TABLE";            // Чтение строки таблицы
        case AST_LOOP_AT: return "LOOP_AT";                  // LOOP AT itab
        case AST_MODIFY_TABLE: return "MODIFY_TABLE";        // Изменение таблицы
        case AST_DELETE_TABLE: return "DELETE_TABLE";        // Удаление строки
        case AST_INSERT_TABLE: return "INSERT_TABLE";        // Вставка строки

        // Специальные инструкции
        case AST_EXPORT: return "EXPORT";                    // Выгрузка в память
        case AST_IMPORT: return "IMPORT";                    // Загрузка из памяти
        case AST_MEMORY_ID: return "MEMORY_ID";              // Идентификатор памяти
        case AST_SET_PARAMETER: return "SET_PARAMETER";      // Сохранение параметра
        case AST_GET_PARAMETER: return "GET_PARAMETER";      // Загрузка параметра
        case AST_AUTHORITY_CHECK: return "AUTHORITY_CHECK";  // Проверка прав
        case AST_CREATE_OBJECT: return "CREATE_OBJECT";      // Создание экземпляра
        case AST_FREE_OBJECT: return "FREE_OBJECT";          // Освобождение объекта

        case AST_UNKNOWN: return "UNKNOWN";                  // Неопознанный узел
        default: return "UNDEFINED";                         // Защита от ошибок
    }
}

// Отладочная печать AST (для тестов)
void ast_node_print(ast_node_t* node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");
    printf("(%s", ast_node_type_name(node->type));
    if (node->token.lexeme && strlen(node->token.lexeme) > 0) {
        printf(" \"%s\"", node->token.lexeme);
    }
    printf(")\n");

    for (int i = 0; i < node->child_count; ++i) {
        ast_node_print(node->children[i], indent + 1);
    }
}
