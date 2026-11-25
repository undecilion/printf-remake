#include <unistd.h>

#include <print_char.h>

int my_printf_char(char chr) {
    write(1, &chr, sizeof(char));
    return 1;
}