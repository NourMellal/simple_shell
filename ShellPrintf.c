#include "main.h"

/**
 * _vsprintf - Writes a formatted string to a buffer
 * @str: The buffer to write to
 * @fmt: The format string
 * @ap: The list of arguments
 */
void _vsprintf(char *str, const char *fmt, va_list ap)
{
	char c;
	int i, state = 0;

	for (i = 0; fmt[i]; i++)
	{
		c = fmt[i];
		if (state == 0)
			(c == '%') ? (state = '%') : (*str++ = c);
		else if (state == '%')
		{
			if (c == 'd')
				str += _itoa(va_arg(ap, int), str, 10, 1);
			else if (c == 'l')
				str += _itoa(va_arg(ap, size_t), str, 10, 0);
			else if (c == 'x')
				str += _itoa(va_arg(ap, int), str, 16, 0);
			else if (c == 'p')
			{
				(*str++ = '0', *str++ = 'x');
				str += _itoa(va_arg(ap, size_t), str, 16, 0);
			}
			else if (c == 's')
				str += _stoa(va_arg(ap, char *), str);
			else if (c == 'c')
				*str++ = va_arg(ap, int);
			else if (c == '%')
				*str++ = c;
			else
				(*str++ = '%', *str++ = c);
			state = 0;
		}
	}
	*str = '\0';
}

/**
 * _sprintf - Writes a formatted string to a array of chars
 * @str: The char array to write the formatted string to
 * @fmt: The format string to use for writing
 * @...: Optional arguments used in the format string
 */
void _sprintf(char *str, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	_vsprintf(str, fmt, ap);
	va_end(ap);
}

/**
 * _fprintf - prints a formatted string to a file descriptor
 * @fd: the file descriptor to write to
 * @fmt: the format string
 * @...: Optional arguments used in the format string
 */
void _fprintf(int fd, const char *fmt, ...)
{
	char buf[BUFFER_SIZE];
	va_list ap;

	va_start(ap, fmt);
	_vsprintf(buf, fmt, ap);
	write(fd, buf, _strlen(buf));
	va_end(ap);
}

/**
 * _printf - prints a formatted string to the standard output
 * @fmt: format string containing text and format specifiers
 * @...: Optional arguments used in the format string
 */
void _printf(const char *fmt, ...)
{
	va_list ap;
	char buf[BUFFER_SIZE];

	va_start(ap, fmt);
	_vsprintf(buf, fmt, ap);
	write(1, buf, _strlen(buf));
	va_end(ap);
}