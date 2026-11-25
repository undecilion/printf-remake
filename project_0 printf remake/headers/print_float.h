#ifndef FLOAT_PRINT_H
#define FLOAT_PRINT_H

#include "IEEE 754.h"

char* ftos(float value);
int my_printf_float(float value, int precision, bool is_optimized);

#endif