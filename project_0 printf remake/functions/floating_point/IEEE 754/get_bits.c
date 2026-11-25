#include <stdlib.h>

#include "IEEE 754.h"

union floatConverter {
    float f;
    unsigned int i;
};

union doubleConverter {
    double d;
    unsigned long long l;
};

union longDoubleConverter {
    long double ld;
    unsigned char c[12];
};

bool get_bit(unsigned long long val, int index) {
    return (val >> index) & 1;
}

bool* get_float_bits(float value) {
    union floatConverter data;
    data.f = value;

    bool* bits = malloc(32 * sizeof(bool));
    for (int i = 0; i < 32; i++) {
        bits[i] = get_bit(data.i, 32 - i - 1);
    }

    return bits;
}

bool* get_double_bits(double value) {
    union doubleConverter data;
    data.d = value;

    bool* bits = malloc(64 * sizeof(bool));
    for (int i = 0; i < 64; i++) {
        bits[i] = get_bit(data.l, 64 - i - 1);
    }

    return bits;
}

bool* get_long_double_bits(long double value) {
    union longDoubleConverter data;
    data.ld = value;

    bool* bits = malloc(96 * sizeof(bool));
    for (int i = 0; i < 96; i++) {
        int byte_index = 12 - (i/8) - 1;
        int bit_index = 8 - (i % 8) - 1;
        bits[i] = get_bit(data.c[byte_index], bit_index);
    }

    return bits;
}

bool addition_str(char* flt_str, int current_index) {
    if (flt_str[current_index] == '9') {
        flt_str[current_index] = '0';
        if (flt_str[current_index - 1] == '.' || current_index - 1 < 0) {
            return 1;
        }
        int ret = addition_str(flt_str, current_index - 1);

        if (ret) {
            return 1;
        }
        return 0;
    } else {
        flt_str[current_index] = flt_str[current_index] + 1;

        return 0;
    }
}

char* round_float_str(char* flt_str) {
    int length = 0;
    while (flt_str[length] != '\0') {
        length++;
    }

    char reverse = flt_str[length - 1];
    int ret = addition_str(flt_str, length - 1);
    if (reverse != '9') {
        flt_str[length - 1] = reverse;
    }

    if (ret) {
        int dot_index = 0;
        while (flt_str[dot_index] != '.') {
            dot_index++;
        }

        //"9.99" l = 4;
            
        int ret2 = addition_str(flt_str, dot_index - 1);
        if (ret2) {
            flt_str = realloc(flt_str, length * sizeof(char) + 1 + 1);
            for (int i = length + 1; i > 0; i--) {
                flt_str[i] = flt_str[i - 1];
            }
            flt_str[0] = '1';
            return flt_str;
        }
    }
    return flt_str;
}
