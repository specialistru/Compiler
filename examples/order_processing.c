#include <stdio.h>
#include <string.h>
#include "parameters.h"
#include "perform.h"
#include "error_handling.h"

int main() {
    char auart[64] = "";
    char description[64] = "";

    perform_init();

    if (!get_parameter("AAT", auart)) {
        log_info("Parameter AAT not set, defaulting to empty");
    }

    if (strlen(auart) == 0) {
        log_info("No AUART parameter found. Setting default to TA.");
        set_parameter("AAT", "TA");
        strcpy(auart, "TA");
    }

    perform_get_t003p(auart, description);
    printf("Order type '%s' description: %s\n", auart, description);

    return 0;
}
