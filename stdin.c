#include "main.h"

#define MAX_ARGS 128

/**
 * read_line - reads a line from stdin
 * Return: pointer to the line read, or NULL if EOF is reached
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = _getline(&line, &len, STDIN_FILENO);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}


/**
 * read_input - reads input from the user and stores it in an array of strings
 * @input: pointer to a string that will be used to store the user's input
 * Return: pointer to an array of strings containing the user's input
 */

