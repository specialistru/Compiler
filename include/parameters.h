#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdbool.h>

bool get_parameter(const char* id, char* out_value);
void set_parameter(const char* id, const char* value);
void clear_parameters();

#endif // PARAMETERS_H

