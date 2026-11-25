#ifndef LONG_DOUBLE_PRINT_H
#define LONG_DOUBLE_PRINT_H

#include "IEEE 754.h"

char* ldtos(long double value);
int my_printf_long_double(long double value, int precision, bool is_optimized);

#endif