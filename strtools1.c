#include "main.h"

/**
 * _strlen - length of a given string
 * @s: the string
 * Return: the length of given string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * reverse_str - reverses a given string
 * @s: the string to be reversed
 */
void reverse_str(char s[])
{
	char temp;
	unsigned int i = 0, len = 0;

	len = _strlen(s);

	for (; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}
}

/**
 * _stoa - copies a string to a buffer
 * @s: the string to copy
 * @buf: the buffer to copy to
 * Return: the length of the copied string
 */
int _stoa(char *s, char *buf)
{
	int i = 0;
	char *p = (!s) ? "(null)" : s;

	while (*p)
		buf[i++] = *p++;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 * @n: index of characters to compare
 * Return: difference between the two strings
 */
int _strcmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);

	while (n && *s1 && (*s1 == *s2))
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
 * _memcpy - Copies memory from one location to another
 * @dest: A pointer to the destination memory
 * @src: A pointer to the source memory
 * @n: The number of bytes to copy
 * Return: A pointer to the destination memory
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}
