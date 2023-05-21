#include "main.h"

/**
 * write_str - Writes a string to a file descriptor
 * @fd: The file descriptor to write to
 * @s: The string to write
 */
void write_str(int fd, char *s)
{
	(!s) && (s = "(null)");
	write(fd, s, _strlen(s));
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
 * _strtok - Tokenizes a string by a given delimiter
 * @str: The string to be tokenized
 * @delim: The delimiter used for tokenization
 * Return: A pointer to the next token in the string
 */
char *_strtok(char *str, char *delim)
{
	int i;
	char *curr;
	static char *next;

	(str) ? (curr = str) : (curr = next);

	if (!curr)
		return (NULL);
	/* Skip leading delimiters */
	while (*curr)
	{
		for (i = 0; delim[i]; i++)
			if (*curr == delim[i])
				break;

		if (!delim[i])
			break;
		curr++;
	}
	if (!*curr)
		return (NULL);
	/* Find the end of the token */
	next = curr;
	while (*next)
	{
		for (i = 0; delim[i]; i++)
			if (*next == delim[i])
				break;
		if (delim[i])
			break;
		next++;
	}
	if (*next)
	{
		*next = '\0';
		next++;
	}
	return (curr);
}
