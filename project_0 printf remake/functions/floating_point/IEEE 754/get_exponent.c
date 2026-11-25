#include <stdio.h>

#include "IEEE 754.H"

bool get_floating_point_sign(bool* bits) {
    return bits[0];
}

void set_bit(int* val, int index, bool sign) {
    *val = *val | (sign << index);
}

int get_power_of_2(int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result = result * 2;
    }
    return result;
}

int get_floating_point_exponent(bool* bits, int length) {
    int exponent = 0;

    for (int i = 0; i < length; i++) {
        set_bit((int*)(&exponent), i, bits[length - i]);
    }
    exponent = exponent - (get_power_of_2(length - 1) - 1);

    return exponent;
}