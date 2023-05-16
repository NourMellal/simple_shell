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
 * _getline - reads a line from a file descriptor
 * @lineptr: pointer to the buffer where the line is stored
 * @n: size of the buffer
 * @fd: file descriptor
 * Return: number of bytes read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	size_t size = 0;
	char *line = *lineptr;
	size_t start = 0, end = 0;
	static char buffer[BUFFER_SIZE];

	for (;;)
	{
		if (start >= end)
		{
			ssize_t bytes = read(fd, buffer, BUFFER_SIZE);

			if (bytes <= 0)
				return (-1);
			start = 0;
			end = bytes;
		}
		while (start < end)
		{
			char c = buffer[start++];
			char *tmp = _realloc(line, size, size + 2);

			if (tmp == NULL)
			{
				free(line);
				return (-1);
			}
			line = tmp;
			line[size++] = c;
			if (c == '\n')
			{
				line[size] = '\0';
				*lineptr = line;
				*n = size;
				return (size);
			}
		}
	}
}

/**
 * _strtok - Tokenizes a string by a given delimiter.
 * @str: The string to be tokenized.
 * @delim: The delimiter used for tokenizing.
 * Return: A pointer to the next token in the string
 * or NULL if no more tokens are found.
 *
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
