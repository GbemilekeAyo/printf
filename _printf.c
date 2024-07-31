#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int _printf(const char *format, ...) {
    va_list args;
    int printed_chars = 0;
    const char *traverse;

    va_start(args, format);

    for (traverse = format; *traverse != '\0'; traverse++) {
        if (*traverse == '%') {
            traverse++;
            if (*traverse == 'c') {
                char c = (char)va_arg(args, int);
                write(1, &c, 1);
                printed_chars++;
            } else if (*traverse == 's') {
                char *s = va_arg(args, char *);
                while (*s) {
                    write(1, s++, 1);
                    printed_chars++;
                }
            } else if (*traverse == '%') {
                char c = '%';
                write(1, &c, 1);
                printed_chars++;
            }
        } else {
            write(1, traverse, 1);
            printed_chars++;
        }
    }

    va_end(args);
    return printed_chars;
}
