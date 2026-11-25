#include "IEEE 754.H"

unsigned long long get_floating_point_integer(bool* bits, ieee_754_sizes sizes, int exponent) {
    unsigned long long integer = 0;
    bool* mantissa = &bits[sizes.sign_bit + sizes.exponent + sizes.intercept];
    for (int i = 0; i < sizes.mantissa; i++) {
        if (exponent - i <= 0) {
            break;
        }
        if (mantissa[i]) {
            integer = integer + get_power_of_2(exponent - 1 - i);
        }
    }
    if (exponent >= 0) {
        integer = integer + get_power_of_2(exponent);
    }

    return integer;
}