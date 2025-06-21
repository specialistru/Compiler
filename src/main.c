#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"
#include "optimizer.h"

int main() {
    const char* abap_code =
    "CLASS zcl_order_processor DEFINITION.\n"
    "  PUBLIC SECTION.\n"
    "    METHODS:\n"
    "      create_order IMPORTING iv_customer_id TYPE kunnr\n"
    "                             iv_material_id TYPE matnr\n"
    "                             iv_quantity    TYPE i\n"
    "                   RETURNING VALUE(rv_order_id) TYPE vbeln,\n"
    "      check_availability IMPORTING iv_material_id TYPE matnr\n"
    "                          RETURNING VALUE(rv_available) TYPE abap_bool.\n"
    "ENDCLASS.\n";

    Token tokens[MAX_TOKENS];
    int token_count = lex(abap_code, tokens, MAX_TOKENS);
    printf("Lexical analysis done, tokens: %d\n", token_count);

    ParseResult parse_result = parse_class(tokens);
    if (!parse_result.success) {
        printf("Parsing failed.\n");
        return 1;
    }
    printf("Parsing succeeded.\n");

    if (!semantic_check("zcl_order_processor", "create_order")) {
        printf("Semantic analysis failed.\n");
        return 1;
    }
    printf("Semantic analysis succeeded.\n");

    generate_code();

    // Пример оптимизации
    Instruction code[] = {
        {0, "check_availability"},
        {0, "check_availability"},
        {1, "lv_available"},
        {2, "zcx_material_not_available"},
        {2, "zcx_material_not_available"},
    };
    int n = sizeof(code)/sizeof(code[0]);
    int new_len = optimize(code, n);

    printf("After optimization:\n");
    for (int i=0; i<new_len; i++) {
        printf("Op: %d Arg1: %s\n", code[i].op, code[i].arg1);
    }

    return 0;
}

