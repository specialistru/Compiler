#include "semantic.h"
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

