#include "ir_generator.h"
#include "ir.h"
#include "ast.h"
#include "error_handling.h"

void ir_generate(ast_node_t* root) {
    ir_init();

    if (root->type != AST_PROGRAM) {
        log_error("IR generation: root is not program");
        return;
    }

    // Для примера просто загружаем все переменные как константы
    for (int i = 0; i < root->child_count; i++) {
        ast_node_t* child = root->children[i];
        if (child->type == AST_VARIABLE) {
            // загружаем в IR LOAD_CONST для демонстрации
            ir_emit(IR_LOAD_CONST, i, 0, 0);
        }
    }
}
