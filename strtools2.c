#include "main.h"

/**
 * write_fd - Writes a string to a file descriptor
 * @fd: The file descriptor to write to
 * @s: The string to write
 */
void write_fd(int fd, char *s)
{
	int length = 0;

	if (!s)
		s = "(null)";

	length = _strlen(s);

	write(fd, s, length);
}

/**
 * _strdup - Duplicates a string
 * @s: The string to duplicate
 * Return: Pointer to the duplicated string, or NULL if fails
 */
char *_strdup(const char *s)
{
	int i;
	char *result;

	result = malloc(sizeof(char) * (_strlen((char *)s) + 1));
	if (result == NULL)
		return (NULL);

	for (i = 0; s[i]; i++)
		result[i] = s[i];

	result[i] = '\0';

	return (result);
}

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
