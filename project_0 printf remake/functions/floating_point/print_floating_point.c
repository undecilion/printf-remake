#include <stdlib.h>
#include <unistd.h>

#include "IEEE 754.h"

int my_printf_floating_point(char* flt_str, int precision, bool is_optimized) {
    precision = precision - 1;

    if (precision < 0) {
        int length = 0;
        while (flt_str[length] != '\0') {
            length++;
        }
        write(1, flt_str, length);
        free(flt_str);
        return length;
    }

    int decimal_start_index = 0;
    while (flt_str[decimal_start_index] != '.') {
        decimal_start_index++;
    }
 
    int length = 0;
    while (flt_str[length] != '\0') {
        length++;
    }

    if (decimal_start_index + precision + 2 < length) {
        flt_str[decimal_start_index + precision + 2] = '\0';
    }
    flt_str = round_float_str(flt_str);

    if (is_optimized) {
        int last_non_0_index = -1;
        for (int i = decimal_start_index; i < decimal_start_index + precision + 2; i++) {
            if (flt_str[i] != '0') {
                last_non_0_index = i;
            }
        }
        flt_str[last_non_0_index + 1] = '\0';
        //write(1, flt_str, last_non_0_index + 1);
        //if (decimal_start_index == last_non_0_index) {
        //    char zero = '0';
        //    write(1, &zero, sizeof(char));
        //}
    }
        
    length = 0;
    while (flt_str[length] != '\0') {
        length++;
    }

    write(1, flt_str, length);
    free(flt_str);
    return length;
}