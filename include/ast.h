#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    // Программа
    AST_PROGRAM,

    // Объявления
    AST_DATA,
    AST_CONSTANTS,
    AST_PARAMETERS,
    AST_SELECT_OPTIONS,
    AST_TABLES,
    AST_TYPES,
    AST_RANGES,

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

    // Вызовы и процедуры
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

    // Классы / интерфейсы / методы
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

    // Выражения и операции
    AST_ASSIGNMENT,
    AST_EXPR_BINARY_OP,
    AST_EXPR_UNARY_OP,
    AST_EXPR_LITERAL,
    AST_EXPR_IDENTIFIER,
    AST_EXPR_FUNCTION_CALL,
    AST_EXPR_METHOD_CALL,

    // Работа с таблицами
    AST_SELECT,
    AST_SELECT_SINGLE,
    AST_ENDSELECT,
    AST_READ_TABLE,
    AST_LOOP_AT,
    AST_MODIFY_TABLE,
    AST_DELETE_TABLE,
    AST_INSERT_TABLE,

    // Специальные
    AST_EXPORT,
    AST_IMPORT,
    AST_MEMORY_ID,
    AST_SET_PARAMETER,
    AST_GET_PARAMETER,
    AST_AUTHORITY_CHECK,
    AST_CREATE_OBJECT,
    AST_FREE_OBJECT,

    // Ошибка или нераспознанный узел
    AST_UNKNOWN

} ast_node_type_t;

// AST-узел
typedef struct ast_node {
    ast_node_type_t type;
    token_t token;                // основной токен (например, ключевое слово или имя)
    struct ast_node** children;   // массив дочерних узлов
    int child_count;
} ast_node_t;

// === Интерфейс ===

// Создание нового AST-узла
ast_node_t* ast_node_create(ast_node_type_t type, token_t token);

// Добавление дочернего узла
void        ast_node_add_child(ast_node_t* parent, ast_node_t* child);

// Освобождение AST
void        ast_node_free(ast_node_t* node);

// Отладочная печать AST (для тестов)
void        ast_node_print(ast_node_t* node, int indent); // отладочная печать

#endif // AST_H
