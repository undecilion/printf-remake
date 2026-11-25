#include <stdlib.h>

#include "IEEE 754.h"

#include "print_string.h"
#include "print_long_long.h"

void get_power_of_2_to_the_negative_i(int exponent, unsigned long long* result, int* offset) {
    if (exponent <= 0) {
        return;
    }

    *result = 1;
    *offset = 0;
    bool offset_plus = 0;
    for (int i = 0; i < exponent; i++) {
        if (offset_plus) {
            *offset = *offset + 1;
            offset_plus = 0;
        }

        *result = *result * 5;

        unsigned long long preresult = *result;
        char* int_ptr = ulltos(preresult);
        if (int_ptr[0] == '1') {
            offset_plus = 1;
        }
        free(int_ptr);
    }
}

char* get_floating_point_decimal(bool* bits, ieee_754_sizes sizes, int exponent) {
    bool* mantissa = &bits[sizes.sign_bit + sizes.exponent + sizes.intercept];

    int reserve = sizes.mantissa - exponent;
    if (reserve <= 0) {
        char* decimal_str = malloc(1);
        decimal_str[0] = 0;
        return decimal_str;
    }

    int decimal_start_index = exponent;
    if (decimal_start_index < 0) {
        decimal_start_index = 0;
    }

    int decimal_start_exponent = exponent - 1;
    if (exponent > 0) {
        decimal_start_exponent = -1;
    }

    char* decimal_str = malloc(reserve + 1);
    for (int i = 0; i < reserve; i++) {
        decimal_str[i] = '0';
    }
    decimal_str[reserve] = '\0';

    int index = 0;
    for (int i = decimal_start_index; i < sizes.mantissa; i++) {
        if (!mantissa[i]) {
            index += 1;
            continue;
        }
        unsigned long long result;
        int offset;
        get_power_of_2_to_the_negative_i(-(decimal_start_exponent - index), &result, &offset);

        char* int_ptr = ulltos(result);

        int length = 0;
        while (int_ptr[length] != '\0') {
            length++;
        }

        int two_digit_num[2] = {0,0};
        for (int k = 0; k < length; k++) {
            int num = (decimal_str[offset + length - k - 1] - ASCII_0_OFFSET) + (int_ptr[length - k - 1] - ASCII_0_OFFSET) + two_digit_num[0];

            two_digit_num[0] = num / 10;
            two_digit_num[1] = num - (num / 10) * 10;

            decimal_str[offset + length - k - 1] = two_digit_num[1] + ASCII_0_OFFSET;
        }
        int k = 0;
        while (offset - k - 1 >= 0 && two_digit_num[0] != 0) {
            int num = (decimal_str[offset - k - 1] - ASCII_0_OFFSET) + two_digit_num[0];

            two_digit_num[0] = num / 10;
            two_digit_num[1] = num - (num / 10) * 10;

            decimal_str[offset - k - 1] = two_digit_num[1] + ASCII_0_OFFSET;
            k++;
        }

        free(int_ptr);
        index += 1;
    }

    if (exponent < 0) {
        unsigned long long result;
        int offset;
        get_power_of_2_to_the_negative_i(-exponent, &result, &offset);

        char* int_ptr = ulltos(result);

        int length = 0;
        while (int_ptr[length] != '\0') {
            length++;
        }

        int two_digit_num[2] = {0,0};
        for (int k = 0; k < length; k++) {
            int num = (decimal_str[offset + length - k - 1] - ASCII_0_OFFSET) + (int_ptr[length - k - 1] - ASCII_0_OFFSET) + two_digit_num[0];

            two_digit_num[0] = num / 10;
            two_digit_num[1] = num - (num / 10) * 10;

            decimal_str[offset + length - k - 1] = two_digit_num[1] + ASCII_0_OFFSET;
        }
        int k = 0;
        while (offset - k - 1 >= 0 && two_digit_num[0] != 0) {
            int num = (decimal_str[offset - k - 1] - ASCII_0_OFFSET) + two_digit_num[0];

            two_digit_num[0] = num / 10;
            two_digit_num[1] = num - (num / 10) * 10;

            decimal_str[offset - k - 1] = two_digit_num[1] + ASCII_0_OFFSET;
            k++;
        }
    }

    return decimal_str;
}