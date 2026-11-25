#include <print.h>

void case_int(char current, char** args, int* length, bool* state) {
    if (*state) {
        int val = *(int*)(*args += 8);
        *length = *length + my_printf_int(val);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_long_long(char current, char** args, int* length, bool* state) {
    if (*state) {
        long long ll = *(long long*)(*args += 8);
        *length = *length + my_printf_long_long(ll);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_char(char current, char** args, int* length, bool* state) {
    if (*state) {
        char chr = *(char*)(*args += 8);
        *length = *length + my_printf_char(chr);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_string(char current, char** args, int* length, bool* state, int num) {
    if (*state) {
        char* str = *(char**)(*args += 8);

        if (num) {
            str[num] = '\0';
        }

        *length = *length + my_printf_string(str);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_float(char current, char** args, int* length, bool* state, int num, bool* optimized, bool* is_negative) {
    if (*state) {
        double d = *(double*)(*args += 8);
        float val = (float)(d);

        int precision = 6;
        if (num) {
            precision = num;
            if (*is_negative) {
                precision = -1;
                *is_negative = 0;
            }
        }

        *length = *length + my_printf_float(val, precision, *optimized);
        *optimized = 0;
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_double(char current, char** args, int* length, bool* state, int num, bool* optimized, bool* is_negative) {
    if (*state) {
        double val = *(double*)(*args += 8);

        int precision = 6;
        if (num) {
            precision = num;
            if (*is_negative) {
                precision = -1;
                *is_negative = 0;
            }
        }

        *length = *length + my_printf_double(val, precision, *optimized);
        *optimized = 0;
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_long_double(char current, char** args, int* length, bool* state, int num, bool* optimized, bool* is_negative) {
    if (*state) {
        long double val = **(long double**)(*args += 8);

        int precision = 6;
        if (num) {
            precision = num;
            if (*is_negative) {
                precision = -1;
                *is_negative = 0;
            }
        }

        *length = *length + my_printf_long_double(val, precision, *optimized);
        *optimized = 0;
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_hex(char current, char** args, int* length, bool* state, int num) {
    if (*state) {
        long long val = *(long long*)(*args += 8);

        *length = *length + my_printf_hex((char*)(&val), num);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

void case_pointer(char current, char** args, int* length, bool* state) {
    if (*state) {
        char* ptr = *(char**)(*args += 8);

        *length = *length + my_printf_pointer(ptr);
        *state = 0;
    } else {
        *length = *length + my_printf_char(current);
    }
}

int my_printf(char* str, ...) {
    char *args = (char*)(&str);

    int index = 0;
    bool state = 0;
    int length = 0;

    bool is_negative = 0;
    unsigned int num = 0;

    bool optimized = 0;

    bool was_long = 0;

    while (str[index] != '\0') {
        switch (str[index]) {
            case 'i':
                case_int(str[index], &args, &length, &state);
                break;
            case 'l':
                if (was_long) {
                    case_long_long(str[index], &args, &length, &state);
                    was_long = 0;
                } else {
                    if (state) {
                        was_long = 1;
                    } else {
                        length = length + my_printf_char(str[index]);
                    }
                }
                break;
            case 'c':
                case_char(str[index], &args, &length, &state);
                break;
            case 's':
                case_string(str[index], &args, &length, &state, num);
                break;
            case 'o':
                if (state) {
                    optimized = 1;
                } else {
                    length = length + my_printf_char(str[index]);
                }
                break;
            case 'f':
                case_float(str[index], &args, &length, &state, num, &optimized, &is_negative);
                break;
            case 'd':
                if (was_long) {
                    case_long_double(str[index], &args, &length, &state, num, &optimized, &is_negative);
                    was_long = 0;
                } else {
                    case_double(str[index], &args, &length, &state, num, &optimized, &is_negative);
                }
                break;
            case 'x':
                case_hex(str[index], &args, &length, &state, num);
                break;
            case 'p':
                case_pointer(str[index], &args, &length, &state);
                break;

            case '%':
                if (!state) {
                    state = 1;
                } else {
                    state = 0;
                }
                break;
            case '-':
                if (state) {
                    is_negative = 1;
                } else {
                    length = length + my_printf_char(str[index]);
                }
                break;
            default:
                optimized = 0;
                was_long = 0;
                int ctoi = str[index] - ASCII_0_OFFSET;
                if (ctoi >= 0 && ctoi <=  + 9 && state) {
                    num = (num * 10) + ctoi;
                    break;
                } else {
                    num = 0;
                }
                length = length + my_printf_char(str[index]);
                break;
            }
        index++;
    }
    return length;
}