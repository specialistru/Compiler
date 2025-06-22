#include "semantic.h"
#include "error_handling.h"
#include <stdio.h>
#include <string.h>

int semantic_check(const char* class_name, const char* method_name) {
    if (strcmp(class_name, "zcl_order_processor") != 0) {
        printf("Semantic error: unknown class '%s'\n", class_name);
        return 0;
    }
    if (strcmp(method_name, "create_order") != 0 && strcmp(method_name, "check_availability") != 0) {
        printf("Semantic error: unknown method '%s'\n", method_name);
        return 0;
    }
    return 1;
}

semantic_result_t semantic_analyze(ast_node_t* root) {
    // Простая проверка: если корень пуст — ошибка
    if (!root || root->type != AST_PROGRAM) {
        log_error("Semantic error: root node invalid");
        return SEMANTIC_ERROR;
    }
    // В реале тут проверка типов, объявлений, область видимости
    return SEMANTIC_OK;
}
