#include "main.h"

/**
 * str_len - Calculates the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s++)
		len++;
	return (len);
}

/**
 * str_rev - Reverses a string.
 * @s: The string to be reversed.
 */
void str_rev(char s[])
{
	char temp;
	int i = 0, len = 0;

	len = _strlen(s);

	for (; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}
}

/**
 * _stb - Copies a string to a buffer.
 * @s: The string to be copied.
 * @buf: The destination buffer.
 *
 * Return: The length of the copied string.
 */
int _stoa(char *s, char *buf)
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

	return (i);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: The difference between the first differing characters
 *         (0 if the strings are equal).
 */
int _strcmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);

	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
		return (0);

	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

/**
 * _memcpy - Copies a memory block from source to destination.
 * @dest: The destination memory block.
 * @src: The source memory block.
 * @n: The number of bytes to copy.
 *
 * Return: A pointer to the destination memory block.
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}

/**
 * _strtok - Tokenizes a string by a given delimiter
 * @str: The string to be tokenized
 * @delim: The delimiter used for tokenization
 *
 * Return: A pointer to the next token in the string
 */

char *_strtok(char *str, char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
		last = str;

	if (last == NULL || *last == '\0')
		return (NULL);

	token = last;

	while (*last != '\0')
	{
		if (*last == *delim)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}
	return (token);
}
