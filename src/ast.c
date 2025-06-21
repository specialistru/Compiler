#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast_node_t* ast_node_create(ast_node_type_t type, const char* text) {
    ast_node_t* node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = type;
    node->child_count = 0;
    node->children = NULL;
    if (text) {
        node->text = strdup(text);
    } else {
        node->text = NULL;
    }
    return node;
}

void ast_node_add_child(ast_node_t* parent, ast_node_t* child) {
    parent->children = (ast_node_t**)realloc(parent->children, sizeof(ast_node_t*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

void ast_node_free(ast_node_t* node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) {
        ast_node_free(node->children[i]);
    }
    free(node->children);
    free(node->text);
    free(node);
}
