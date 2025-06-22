#include <stdio.h>
#include <stdlib.h>
#include "ir.h"

#define MAX_IR_INSTR 1024

static ir_instr_t instructions[MAX_IR_INSTR];
static int instr_count = 0;

void ir_init() {
    instr_count = 0;
}

void ir_emit(ir_opcode_t opcode, int32_t arg1, int32_t arg2, int32_t arg3) {
    if (instr_count >= MAX_IR_INSTR) {
        fprintf(stderr, "IR buffer overflow\n");
        exit(1);
    }
    instructions[instr_count].opcode = opcode;
    instructions[instr_count].arg1 = arg1;
    instructions[instr_count].arg2 = arg2;
    instructions[instr_count].arg3 = arg3;
    instr_count++;
}

void ir_print() {
    for (int i = 0; i < instr_count; i++) {
        printf("%03d: opcode=%d arg1=%d arg2=%d arg3=%d\n",
            i,
            instructions[i].opcode,
            instructions[i].arg1,
            instructions[i].arg2,
            instructions[i].arg3);
    }
}
