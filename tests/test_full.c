#include <stdio.h>
#include "parser.h"
#include "semantic.h"
#include "ir_generator.h"
#include "optimizer.h"
#include "interpreter.h"
#include "error_handling.h"

int main() {
    const char* source_code = "var1 var2 var3";

    parser_t parser;
    parser_init(&parser, source_code);

    ast_node_t* ast = parser_parse_program(&parser);
    if (!ast) {
        log_error("Parsing failed");
        return 1;
    }

    if (semantic_analyze(ast) != SEMANTIC_OK) {
        log_error("Semantic analysis failed");
        ast_node_free(ast);
        return 1;
    }

    ir_generate(ast);
    optimizer_optimize();
    interpreter_run();

    ast_node_free(ast);
    return 0;
}
