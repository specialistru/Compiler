#ifndef IR_H
#define IR_H

#include <stdint.h>

typedef struct {
    ir_opcode_t opcode;
    int32_t arg1;
    int32_t arg2;
    int32_t arg3;
} ir_instr_t;

void ir_init();
void ir_emit(ir_opcode_t opcode, int32_t arg1, int32_t arg2, int32_t arg3);
void ir_print();

#endif // IR_H
