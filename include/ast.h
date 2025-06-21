#ifndef AST_H
#define AST_H

#include <stddef.h>
#include "lexer.h"

/**
 * AST-узел
 */
typedef struct ast_node_t {
    ast_node_type_t type;           // Тип узла
    token_t token;                  // Токен, связанный с узлом
    struct ast_node_t** children;   // Массив дочерних узлов
    int child_count;                // Количество дочерних узлов
} ast_node_t;

typedef enum {
    // Корневой узел программы
    AST_PROGRAM,

    // Объявления данных
    AST_DATA,
    AST_CONSTANTS,
    AST_PARAMETERS,
    AST_SELECT_OPTIONS,
    AST_TABLES,
    AST_TYPES,
    AST_RANGES,
    AST_FIELD_SYMBOLS,       // Добавлено: поддержка FIELD-SYMBOLS
    AST_FIELD_GROUPS,        // Добавлено: для FIELD-GROUPS

    // Управляющие конструкции
    AST_IF,
    AST_ELSEIF,
    AST_ELSE,
    AST_ENDIF,
    AST_DO,
    AST_ENDDO,
    AST_WHILE,
    AST_ENDWHILE,
    AST_LOOP,
    AST_ENDLOOP,
    AST_CASE,
    AST_WHEN,
    AST_ENDCASE,
    AST_EXIT,
    AST_CONTINUE,
    AST_CHECK,
    AST_RETURN,

    // Вызовы
    AST_PERFORM,
    AST_CALL_FUNCTION,
    AST_CALL_METHOD,
    AST_SUBMIT,
    AST_WAIT,
    AST_FORM,
    AST_ENDFORM,
    AST_FUNCTION,
    AST_ENDFUNCTION,
    AST_MODULE,
    AST_ENDMODULE,

    // ООП
    AST_CLASS_DEF,
    AST_ENDCLASS,
    AST_METHOD_DEF,
    AST_ENDMETHOD,
    AST_INTERFACE_DEF,
    AST_ENDINTERFACE,

    // Исключения
    AST_TRY,
    AST_CATCH,
    AST_CLEANUP,
    AST_ENDTRY,
    AST_RAISE,
    AST_RAISE_EXCEPTION,

    // Работа с таблицами и SELECT
    AST_SELECT,
    AST_SELECT_SINGLE,
    AST_ENDSELECT,
    AST_READ_TABLE,
    AST_LOOP_AT,
    AST_MODIFY_TABLE,
    AST_DELETE_TABLE,
    AST_INSERT_TABLE,

    // WHERE-условия (добавлено)
    AST_WHERE,

    // Специальные инструкции
    AST_EXPORT,
    AST_IMPORT,
    AST_MEMORY_ID,
    AST_SET_PARAMETER,
    AST_GET_PARAMETER,
    AST_AUTHORITY_CHECK,
    AST_CREATE_OBJECT,
    AST_FREE_OBJECT,

    // Выражения
    AST_ASSIGNMENT,
    AST_EXPR_BINARY_OP,
    AST_EXPR_UNARY_OP,
    AST_EXPR_LITERAL,
    AST_EXPR_IDENTIFIER,
    AST_EXPR_FUNCTION_CALL,
    AST_EXPR_METHOD_CALL,

    AST_UNKNOWN
} ast_node_type_t;

/**
 * Создаёт новый AST-узел с заданным типом и токеном.
 * Выделяет память и инициализирует поля.
 *
 * @param type Тип AST-узла
 * @param token Лексема, связанная с узлом
 * @return Указатель на созданный AST-узел
 */
ast_node_t* ast_node_create(ast_node_type_t type, token_t token);


/**
 * Добавляет дочерний узел к родительскому
 *
 * @param parent Родительский узел
 * @param child Дочерний узел
 */
void ast_node_add_child(ast_node_t* parent, ast_node_t* child);

/**
 * Освобождает память, занятую AST-узлом и всеми его дочерними узлами
 *
 * @param node Узел для освобождения
 */
void ast_node_free(ast_node_t* node);

/**
 * Возвращает человеко-читаемое имя для типа AST-узла
 *
 * @param type Тип AST-узла
 * @return Строка с именем узла
 */
const char* ast_node_type_name(ast_node_type_t type);

/**
 * Рекурсивно печатает AST для отладки
 *
 * @param node Узел для печати
 * @param indent Отступ для форматирования
 */
void ast_node_print(ast_node_t* node, int indent);

// Сериализация AST в строку (для тестов)
char* ast_node_serialize(const ast_node_t* node);

#endif // AST_H
