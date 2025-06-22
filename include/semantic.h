#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

typedef enum {
    SEMANTIC_OK,
    SEMANTIC_ERROR
} semantic_result_t;

semantic_result_t semantic_analyze(ast_node_t* root);

#endif // SEMANTIC_H
