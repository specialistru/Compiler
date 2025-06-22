#include <stdio.h>
#include <string.h>
#include "parameters.h"

int main() {
    char val[64];

    set_parameter("AAT", "TA");
    if (get_parameter("AAT", val)) {
        printf("Parameter AAT = %s\n", val);
    } else {
        printf("Parameter AAT not found\n");
    }

    set_parameter("WRK", "1000");
    if (get_parameter("WRK", val)) {
        printf("Parameter WRK = %s\n", val);
    } else {
        printf("Parameter WRK not found\n");
    }

    clear_parameters();
    if (!get_parameter("AAT", val)) {
        printf("Parameters cleared successfully\n");
    }

    return 0;
}
