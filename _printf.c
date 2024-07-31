#include "main.h"

/**
 * _printf - produces output according to a format.
 * @format: character string with zero or more directives.
 *
 * Return: the number of characters printed (excluding null byte).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int printed_chars = 0;
    int i;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == '\0')
                return (-1);

            switch (format[i])
            {
                case 'c':
                    printed_chars += write(1, &va_arg(args, int), 1);
                    break;
                case 's':
                    printed_chars += write(1, va_arg(args, char *), strlen(va_arg(args, char *)));
                    break;
                case '%':
                    printed_chars += write(1, "%", 1);
                    break;
                default:
                    printed_chars += write(1, &format[i - 1], 1);
                    printed_chars += write(1, &format[i], 1);
                    break;
            }
        }
        else
        {
            printed_chars += write(1, &format[i], 1);
        }
    }

    va_end(args);

    return (printed_chars);
}

