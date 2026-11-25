#ifndef MY_PRINT_H
#define MY_PRINT_H

#include "print_int.h"
#include "print_float.h"
#include "print_string.h"
#include "print_char.h"
#include "print_long_long.h"
#include "print_double.h"
#include "print_long_double.h"
#include "print_hex.h"
#include "print_pointer.h"

int my_printf(char* str, ...);

/*

----------INSTRUCTIONS----------

    - integers:
        %i: int
        %ll: long long

    - ascii:
        %c: char
        %s: string

        a number after % will be the length of the string

    - floating point:
        %f: float
        %d: double
        %ld: long double

        'o' right after % makes it optimized:
            %d -> 0.600000
            %od -> 0.6
        
        a number after % or 'o' will be the length of the floating point string

    - other:
        %p: pointer
        %x: hex

*/

#endif