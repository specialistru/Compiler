#include "codegen.h"
#include <stdio.h>

typedef enum {
    OP_CALL,
    OP_ASSIGN,
    OP_RAISE,
    OP_RETURN
} OpCode;

typedef struct {
    OpCode op;
    const char* arg1;
    const char* arg2;
} Instruction;

static Instruction program[10];
static int program_size = 0;

void generate_code() {
    // Пример генерации "байткода" из ABAP create_order логики
    program[0] = (Instruction){OP_CALL, "check_availability", "iv_material_id"};
    program[1] = (Instruction){OP_ASSIGN, "lv_available", "result"};
    program[2] = (Instruction){OP_RAISE, "zcx_material_not_available", NULL};
    program[3] = (Instruction){OP_ASSIGN, "rv_order_id", "'5000123456'"};
    program[4] = (Instruction){OP_RETURN, NULL, NULL};
    program_size = 5;

    for (int i=0; i<program_size; i++) {
        printf("Instr %d: op=%d arg1=%s arg2=%s\n", i,
               program[i].op,
               program[i].arg1 ? program[i].arg1 : "NULL",
               program[i].arg2 ? program[i].arg2 : "NULL");
    }
}

