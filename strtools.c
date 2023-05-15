#include "main.h"

int str_len(char *s)
{
	int len = 0;
	while(*s++)
		len++;
	return (len);
}

void str_rev(char s[])
{
	char temp;
	int i = 0, len = 0;

	len = str_len(s);

	for (; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}
}

int _stb(char *s, char *buf)
{
	int i = 0;
	char *p;

	if (s == NULL)
		p = "(null)";

	else
		p = s;

	while (*p)
	{
		buf[i] = *p;
		i++;
		p++;
	}

	return i;
}


int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (int)(unsigned char)(*s1) - (int)(unsigned char)(*s2);
}


void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}
