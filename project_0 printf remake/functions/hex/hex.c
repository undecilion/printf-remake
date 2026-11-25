#include <stdlib.h>
#include <unistd.h>

#include "print_hex.h"

char* htos(char* ptr, int bytes) {
    char itohs_array[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    
    char* hex_str = malloc(bytes * 2 + 1);
    for (int i = 0; i < bytes; i++) {
        unsigned char val = *(ptr + bytes - 1 - i);
        char hex[2];
        hex[1] = itohs_array[val % 16];
        hex[0] = itohs_array[(val - (val % 16)) / 16];
        hex_str[2 * i] = hex[0];
        hex_str[(2 * i) + 1] = hex[1];
    }

    hex_str[bytes * 2] = '\0';
    return hex_str;
}

int my_printf_hex(char* ptr, int bytes) {
    char* hex_str = htos(ptr, bytes);

    write(1, hex_str, bytes * 2);

    free(hex_str);

    return bytes * 2;
}
