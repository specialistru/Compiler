#include <string.h>
#include "parameters.h"
#include "error_handling.h"
#include "constants.h"

typedef struct {
    char key[MAX_PARAM_KEY_LEN];
    char value[MAX_PARAM_VALUE_LEN];
} Parameter;

#define MAX_PARAMETERS 100
static Parameter parameters[MAX_PARAMETERS];
static int param_count = 0;

bool get_parameter(const char* id, char* out_value) {
    for (int i = 0; i < param_count; i++) {
        if (strncmp(parameters[i].key, id, MAX_PARAM_KEY_LEN) == 0) {
            strncpy(out_value, parameters[i].value, MAX_PARAM_VALUE_LEN);
            return true;
        }
    }
    out_value[0] = '\0';
    return false;
}

void set_parameter(const char* id, const char* value) {
    for (int i = 0; i < param_count; i++) {
        if (strncmp(parameters[i].key, id, MAX_PARAM_KEY_LEN) == 0) {
            strncpy(parameters[i].value, value, MAX_PARAM_VALUE_LEN);
            return;
        }
    }
    if (param_count < MAX_PARAMETERS) {
        strncpy(parameters[param_count].key, id, MAX_PARAM_KEY_LEN);
        strncpy(parameters[param_count].value, value, MAX_PARAM_VALUE_LEN);
        param_count++;
    } else {
        log_error("Parameter storage is full");
    }
}

void clear_parameters() {
    param_count = 0;
}
