#include <stdlib.h>

#include "IEEE 754.h"
#include "print_long_double.h"

#include "print_long_long.h"

char* ldtos(long double value) {
    ieee_754_sizes ldbl = IEEE_754_LONG_DOUBLE;
    bool* long_double_bits_temp = get_long_double_bits(value);
    bool* long_double_bits = &long_double_bits_temp[16];

    bool long_double_sign = get_floating_point_sign(long_double_bits);
    int long_double_exponent = get_floating_point_exponent(long_double_bits, ldbl.exponent);
    unsigned long long long_double_integer = get_floating_point_integer(long_double_bits, ldbl, long_double_exponent);
    char* long_double_decimal = get_floating_point_decimal(long_double_bits, ldbl, long_double_exponent);
    int decimallength = 0;
    while (long_double_decimal[decimallength] != '\0') {
        decimallength++;
    }

    char* ull = ulltos(long_double_integer);
    int ulllength = 0;
    while (ull[ulllength] != '\0') {
        ulllength++;
    }

    char* str = malloc((int)long_double_sign + ulllength + 1 + decimallength + 1);
    if (long_double_sign) {
        str[0] = '-';
    }
    for (int i = 0; i < ulllength; i++) {
        str[(int)long_double_sign + i] = ull[i];
    }
    str[(int)long_double_sign + ulllength] = '.';
    for (int i = 0; i < decimallength; i++) {
        str[(int)long_double_sign + ulllength + 1 + i] = long_double_decimal[i];
    }
    str[(int)long_double_sign + ulllength + 1 + decimallength] = '\0';

    free(ull);
    free(long_double_decimal);
    free(long_double_bits_temp);
    
    return str;
}

int my_printf_long_double(long double value, int precision, bool is_optimized) {
    char* ldbl_str = ldtos(value);
    return my_printf_floating_point(ldbl_str, precision, is_optimized);
}