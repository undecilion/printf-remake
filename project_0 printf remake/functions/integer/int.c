#include <stdlib.h>
#include <unistd.h>

#include "print_int.h"
#include "print_string.h"

char* itos(int value) {
    char itos_array[10] = "0123456789";

    int size = 0;
    char* string = malloc(2);

    if (value == 0) {
        string[0] = '0';
        string[1] = '\0';
        return string;
    }

    while (value > 0) {
        size++;
        string = realloc(string, size);
        int old_value = value;
        value = value / 10;

        int diffrence = old_value - value * 10;
        string[size - 1] = itos_array[diffrence];
    }
    string = realloc(string, size + 1);

    reverse_string(string, size);

    string[size] = '\0';
    return string;
}

int my_printf_int(int value) {
    char* intstr = itos(value);

    int nullIndex = 0;
    while (true) {
        if (intstr[nullIndex] == '\0') {
            break;
        }
        nullIndex++;
    }
    write(1, intstr, nullIndex);

    free(intstr);
    return nullIndex;
}