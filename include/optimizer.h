#ifndef OPTIMIZER_H
#define OPTIMIZER_H

typedef struct {
    int op;
    char arg1[64];
} Instruction;

int optimize(Instruction* code, int n);

#endif

