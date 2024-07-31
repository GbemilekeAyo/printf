#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

/* Function prototypes for helper functions */
int print_char(char c);
int print_string(char *s);
int print_integer(int n);
int print_unsigned(unsigned int n);
int print_octal(unsigned int n);
int print_hex(unsigned int n, int uppercase);
int print_pointer(void *p);
int print_percent(void);

int _printf(const char *format, ...) {
    va_list args;
    int printed_chars = 0;
    const char *traverse;

    va_start(args, format);

    for (traverse = format; *traverse != '\0'; traverse++) {
        if (*traverse == '%') {
            traverse++;
            switch (*traverse) {
                case 'c':
                    printed_chars += print_char(va_arg(args, int));
                    break;
                case 's':
                    printed_chars += print_string(va_arg(args, char *));
                    break;
                case 'd':
                case 'i':
                    printed_chars += print_integer(va_arg(args, int));
                    break;
                case 'u':
                    printed_chars += print_unsigned(va_arg(args, unsigned int));
                    break;
                case 'o':
                    printed_chars += print_octal(va_arg(args, unsigned int));
                    break;
                case 'x':
                    printed_chars += print_hex(va_arg(args, unsigned int), 0);
                    break;
                case 'X':
                    printed_chars += print_hex(va_arg(args, unsigned int), 1);
                    break;
                case 'p':
                    printed_chars += print_pointer(va_arg(args, void *));
                    break;
                case '%':
                    printed_chars += print_percent();
                    break;
                default:
                    printed_chars += write(1, traverse, 1);
                    break;
            }
        } else {
            printed_chars += write(1, traverse, 1);
        }
    }

    va_end(args);
    return printed_chars;
}

/* Helper function implementations */
int print_char(char c) {
    return write(1, &c, 1);
}

int print_string(char *s) {
    int count = 0;
    if (!s)
        s = "(null)";
    while (*s)
        count += write(1, s++, 1);
    return count;
}

int print_integer(int n) {
    char buffer[11]; /* enough to hold INT_MIN */
    int i = 0, neg = 0, count = 0;

    if (n < 0) {
        neg = 1;
        if (n == INT_MIN) {
            return write(1, "-2147483648", 11);
        }
        n = -n;
    }

    do {
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);

    if (neg)
        buffer[i++] = '-';

    while (i--)
        count += write(1, &buffer[i], 1);

    return count;
}

int print_unsigned(unsigned int n) {
    char buffer[10];
    int i = 0, count = 0;

    do {
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);

    while (i--)
        count += write(1, &buffer[i], 1);

    return count;
}

int print_octal(unsigned int n) {
    char buffer[11];
    int i = 0, count = 0;

    do {
        buffer[i++] = (n % 8) + '0';
        n /= 8;
    } while (n > 0);

    while (i--)
        count += write(1, &buffer[i], 1);

    return count;
}

int print_hex(unsigned int n, int uppercase) {
    char buffer[8];
    int i = 0, count = 0;
    char offset = uppercase ? 'A' - 10 : 'a' - 10;

    do {
        unsigned int digit = n % 16;
        buffer[i++] = digit < 10 ? digit + '0' : digit + offset;
        n /= 16;
    } while (n > 0);

    while (i--)
        count += write(1, &buffer[i], 1);

    return count;
}

int print_pointer(void *p) {
    unsigned long addr = (unsigned long)p;
    char buffer[16];
    int i = 0, count = 0;

    count += write(1, "0x", 2);

    do {
        unsigned int digit = addr % 16;
        buffer[i++] = digit < 10 ? digit + '0' : digit + 'a' - 10;
        addr /= 16;
    } while (addr > 0);

    while (i--)
        count += write(1, &buffer[i], 1);

    return count;
}

int print_percent(void) {
    return write(1, "%", 1);
}

