#include <unistd.h>

#include "print_string.h"

void reverse_string(char* string, int size) {
    for (int i = 0; i < size/2; i++) {
        int front = string[i];
        int end = string[size - 1 - i];
        string[i] = end;
        string[size - 1 - i] = front;
    }
}

int my_printf_string(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    write(1, str, length);

    return length;
}