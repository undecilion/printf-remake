#ifndef IEEE_754_H
#define IEEE_754_H

#define bool char
#define int8 signed char
#define ASCII_0_OFFSET 48

#define IEEE_754_FLOAT {1, 8, 0, 23}
#define IEEE_754_DOUBLE {1, 11, 0, 52}
#define IEEE_754_LONG_DOUBLE {1, 15, 1, 63}

#define IEEE_754_BITSIZEOF_FLOAT 32
#define IEEE_754_BITSIZEOF_DOUBLE 64
#define IEEE_754_BITSIZEOF_LONG_DOUBLE 80

typedef struct {
    int sign_bit;
    int exponent;
    int intercept;
    int mantissa;
} ieee_754_sizes;

// float    1,  8,  0,  23      -127    128     exp - (2^7 - 1)
// double   1,  11, 0,  52      -1023   1024    exp - (2^10 - 1)
// ld       1,  15, 1,  63      -16383  16384   exp - (2^14 - 1)

int get_power_of_2(int exponent);

bool* get_float_bits(float value);
bool* get_double_bits(double value);
bool* get_long_double_bits(long double value);

bool get_floating_point_sign(bool* bits);
int get_floating_point_exponent(bool* bits, int length);
unsigned long long get_floating_point_integer(bool* bits, ieee_754_sizes sizes, int exponent);
char* get_floating_point_decimal(bool* bits, ieee_754_sizes sizes, int exponent);

char* round_float_str(char* flt_str);

int my_printf_floating_point(char* flt_str, int precision, bool is_optimized);

#endif