#include <stdio.h>
#include "parameters.h"
#include "perform.h"
#include "error_handling.h"

int main() {
    perform_init();

    char auart[64];
    if (!get_parameter("AAT", auart)) {
        log_info("No order type set, defaulting to 'TA'");
        set_parameter("AAT", "TA");
        strcpy(auart, "TA");
    }

    char description[64];
    perform_get_t003p(auart, description);
    printf("Order type '%s': %s\n", auart, description);

    return 0;
}

