#include <stdlib.h>
#include <unistd.h>

#include "print_hex.h"
#include "print_pointer.h"

char* ptos(char* ptr) {
    char* ptr_str = htos(ptr, sizeof(char*));

    return ptr_str;
}

int my_printf_pointer(char* ptr) {
    char* ptr_str = ptos(ptr);

    write(1, ptr_str, 2 * sizeof(char*));

    free(ptr_str);
    return 2 * sizeof(char*);
}