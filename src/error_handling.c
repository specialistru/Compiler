#include <stdio.h>
#include "error_handling.h"

void log_error(const char* message) {
    fprintf(stderr, "ERROR: %s\n", message);
}

void log_info(const char* message) {
    fprintf(stdout, "INFO: %s\n", message);
}
