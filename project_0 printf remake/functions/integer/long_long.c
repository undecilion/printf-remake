#include <stdlib.h>
#include <unistd.h>

#include "print_int.h"
#include "print_long_long.h"
#include "print_string.h"

char* ulltos(unsigned long long value) {
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
        long long old_value = value;
        value = value / 10;

        int diffrence = old_value - value * 10;
        string[size - 1] = itos_array[diffrence];
    }
    string = realloc(string, size + 1);

    reverse_string(string, size);

    string[size] = '\0';
    return string;
}

int my_printf_long_long(long long value) {
    char* llstr = ulltos((unsigned long long)value);

    int nullIndex = 0;
    while (true) {
        if (llstr[nullIndex] == '\0') {
            break;
        }
        nullIndex++;
    }
    write(1, llstr, nullIndex);

    free(llstr);
    return nullIndex;
}