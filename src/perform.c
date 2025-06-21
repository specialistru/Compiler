#include <string.h>
#include "perform.h"
#include "parameters.h"
#include "error_handling.h"
#include "constants.h"

void perform_init() {
    clear_parameters();
    log_info("Initialization performed.");
}

void perform_set_title() {
    log_info("Title set.");
}

void perform_init_status() {
    // Симуляция установки PF-статуса '100'
    log_info("PF-Status '100' set.");
}

void perform_get_t003p(const char* auart, char* out_text) {
    if (auart == NULL || strlen(auart) == 0) {
        out_text[0] = '\0';
        log_error("perform_get_t003p: AUART is empty");
        return;
    }
    // Простейшая заглушка для описания типа заказа
    if (strcmp(auart, "TA") == 0) {
        strncpy(out_text, "Standard Order", 64);
    } else if (strcmp(auart, "ZT") == 0) {
        strncpy(out_text, "Custom Order", 64);
    } else {
        out_text[0] = '\0';
        log_info("perform_get_t003p: Unknown AUART");
    }
}
