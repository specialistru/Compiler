#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PF_STATUS_100 "100"
#define PARAM_ID_AAT "AAT"
#define PARAM_ID_WRK "WRK"

// Максимальные размеры
#define MAX_PARAM_VALUE_LEN 64
#define MAX_PARAM_KEY_LEN 4

// Лексер - максимальная длина токена
#define MAX_TOKEN_LEN 128

// Опкоды IR
typedef enum {
    IR_NOP,
    IR_LOAD_CONST,
    IR_LOAD_VAR,
    IR_STORE_VAR,
    IR_ADD,
    IR_SUB,
    IR_MUL,
    IR_DIV,
    IR_JUMP,
    IR_JUMP_IF_FALSE,
    IR_CALL,
    IR_RET
} ir_opcode_t;

#endif // CONSTANTS_H
