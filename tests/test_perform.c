#include <stdio.h>
#include "perform.h"

int main() {
    char description[64];

    perform_init();
    perform_set_title();
    perform_init_status();

    perform_get_t003p("TA", description);
    printf("Description for TA: %s\n", description);

    perform_get_t003p("ZZ", description);
    printf("Description for ZZ: %s\n", description[0] ? description : "(empty)");

    return 0;
}
