#include "optimizer.h"
#include <string.h>
#include <stdio.h>

int optimize(Instruction* code, int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && code[i].op == code[i-1].op && strcmp(code[i].arg1, code[i-1].arg1) == 0) {
            // Пропускаем дубликат
            continue;
        }
        code[j++] = code[i];
    }
    return j;
}

