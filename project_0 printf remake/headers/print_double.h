#ifndef DOUBLE_PRINT_H
#define DOUBLE_PRINT_H

#include "IEEE 754.h"

char* dtos(double value);
int my_printf_double(double value, int precision, bool is_optimized);

#endif