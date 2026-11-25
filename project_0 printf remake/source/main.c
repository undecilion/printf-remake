#include <print.h>

int main() {
    int i = 2026;
    float f = 6.6f;
    char s[4];  s[0] = 'n';  s[1] = 'a';  s[2] = 'm';  s[3] = 'e';
    char c = 1;
    long long ll = 6324;
    double d = 6.7f;
    long double ld = 0.00032L;
    int chars = my_printf("int: %i\nfloat: %o20f\nstring: %4s\nchar: %c\nlong long: %ll\ndouble: %100d\nlong double: %-1ld\n", i, f, s, c, ll, d, ld);
    my_printf("amount of characters: %i\n\n", chars);

    int a = 255;
    my_printf("hex: %4x\n", a);
    my_printf("ptr: %p\n", &a);

    return 0;
}