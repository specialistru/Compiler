#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAM,
    AST_STATEMENT,
    AST_EXPR,
    AST_VAR_DECL,
    AST_FUNC_DECL,
    AST_CALL,
    AST_IF,
    AST_WHILE,
    AST_FOR,
    AST_RETURN,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_LITERAL,
    AST_VARIABLE
} ast_node_type_t;

typedef struct ast_node_t {
    ast_node_type_t type;
    char* text; // имя переменной, функция, литерал и т.д.
    struct ast_node_t** children;
    int child_count;
} ast_node_t;

ast_node_t* ast_node_create(ast_node_type_t type, const char* text);
void ast_node_add_child(ast_node_t* parent, ast_node_t* child);
void ast_node_free(ast_node_t* node);

#endif // AST_H
