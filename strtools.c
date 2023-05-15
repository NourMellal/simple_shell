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

