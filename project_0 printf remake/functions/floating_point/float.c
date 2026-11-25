#include <stdlib.h>

#include "IEEE 754.h"
#include "print_float.h"

#include "print_long_long.h"

char* ftos(float value) {
    ieee_754_sizes flt = IEEE_754_FLOAT;
    bool* float_bits = get_float_bits(value);
    
    bool float_sign = get_floating_point_sign(float_bits);
    int float_exponent = get_floating_point_exponent(float_bits, flt.exponent);
    unsigned long long float_integer = get_floating_point_integer(float_bits, flt, float_exponent);
    char* float_decimal = get_floating_point_decimal(float_bits, flt, float_exponent);
    int decimallength = 0;
    while (float_decimal[decimallength] != '\0') {
        decimallength++;
    }

    char* ull = ulltos(float_integer);
    int ulllength = 0;
    while (ull[ulllength] != '\0') {
        ulllength++;
    }

    char* str = malloc((int)float_sign + ulllength + 1 + decimallength + 1);
    if (float_sign) {
        str[0] = '-';
    }
    for (int i = 0; i < ulllength; i++) {
        str[(int)float_sign + i] = ull[i];
    }
    str[(int)float_sign + ulllength] = '.';
    for (int i = 0; i < decimallength; i++) {
        str[(int)float_sign + ulllength + 1 + i] = float_decimal[i];
    }
    str[(int)float_sign + ulllength + 1 + decimallength] = '\0';

    free(ull);
    free(float_decimal);
    free(float_bits);
    
    return str;
}

int my_printf_float(float value, int precision, bool is_optimized) {
    char* flt_str = ftos(value);
    return my_printf_floating_point(flt_str, precision, is_optimized);
}