#include <stdlib.h>

#include "IEEE 754.h"
#include "print_double.h"

#include "print_long_long.h"

char* dtos(double value) {
    ieee_754_sizes dbl = IEEE_754_DOUBLE;
    bool* double_bits = get_double_bits(value);

    bool double_sign = get_floating_point_sign(double_bits);
    int double_exponent = get_floating_point_exponent(double_bits, dbl.exponent);
    unsigned long long double_integer = get_floating_point_integer(double_bits, dbl, double_exponent);
    char* double_decimal = get_floating_point_decimal(double_bits, dbl, double_exponent);
    int decimallength = 0;
    while (double_decimal[decimallength] != '\0') {
        decimallength++;
    }

    char* ull = ulltos(double_integer);
    int ulllength = 0;
    while (ull[ulllength] != '\0') {
        ulllength++;
    }

    char* str = malloc((int)double_sign + ulllength + 1 + decimallength + 1);
    if (double_sign) {
        str[0] = '-';
    }
    for (int i = 0; i < ulllength; i++) {
        str[(int)double_sign + i] = ull[i];
    }
    str[(int)double_sign + ulllength] = '.';
    for (int i = 0; i < decimallength; i++) {
        str[(int)double_sign + ulllength + 1 + i] = double_decimal[i];
    }
    str[(int)double_sign + ulllength + 1 + decimallength] = '\0';

    free(ull);
    free(double_decimal);
    free(double_bits);
    
    return str;
}

int my_printf_double(double value, int precision, bool is_optimized) {
    char* dbl_str = dtos(value);
    return my_printf_floating_point(dbl_str, precision, is_optimized);
}