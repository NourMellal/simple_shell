#include "main.h"

void _vsprintf(char *str, const char *fmt, va_list ap)
{
	char c;
	int i, state = 0;

	for (i = 0; fmt[i]; i++)
	{
		c = fmt[i];

		if (state == 0)
		{
			if (c == '%')
				state = '%';
			else
				*str++ = c;
		}
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
				*str++ = '0';
				*str++ = 'x';
				str += _itoa(va_arg(ap, size_t), str, 16, 0);
			}
			else if (c == 's')
				str += _stb(va_arg(ap, char *), str);
			else if (c == 'c')
				*str++ = va_arg(ap, int);
			else if (c == '%')
				*str++ = c;
			else
			{
				*str++ = '%';
				*str++ = c;
			}
			state = 0;
		}
	}
	*str = '\0';
}
