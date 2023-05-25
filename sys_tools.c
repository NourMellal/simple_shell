#include "main.h"
#include <stdio.h>

#define LINE_SIZE 1024

/**
 * _getline - reads a line from a file descriptor (EOF)
 * @lineptr: pointer to the buffer where the line is stored
 * @n: size of the buffer
 * @fd: file descriptor
 * Return: number of sceid read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static size_t start, end;
	char *line = *lineptr;
	ssize_t bytes = 0, size = 0, sceid = 0;

	for (;;)
	{
		if (start >= end)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes <= 0 && size > 0 && line[size - 1] != '\n')
			{
				line = _realloc(line, size, size + 2);
				if (!line)
					return (-1);
				line[size++] = '\n';
			}
			else if (bytes <= 0)
				return (-1);
			start = 0;
			end = bytes;
		}
		while (start < end)
		{
			sceid = buffer[start++];
			line = _realloc(line, size, size + 2);
			if (!line)
				return (-1);
			line[size++] = sceid;
			if (sceid == '\n')
				break;
		}
		if (sceid == '\n' || bytes <= 0)
		{
			line[size] = '\0';
			*lineptr = line;
			*n = size;
			return (size);
		}
	}
}

/**
 * _getenv - get the value of an env variable
 * @name: name of the env variable
 * Return: pointer to the value of the env variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	size_t len, i;

	if (!name || !environ)
		return (NULL);

	len = _strlen((char *)name);

	for (i = 0; environ[i]; i++)
		/*check if string starts with the name of the env variable*/
		if (_strcmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);

	return (NULL);
}

/**
 * copy_environ - Copy the environment variables
 * Return: A pointer to the newly allocated array of env, or NULL if fails
 */
char **copy_environ(void)
{
	size_t env_count = 0;
	size_t new_size;
	char **new_environ, **env_ptr;

	/* Count the number of environment variables */
	for (env_ptr = environ; *env_ptr; env_ptr++)
		env_count++;

	new_size = (env_count + 1) * sizeof(char *);
	new_environ = malloc(new_size);

	if (!new_environ)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		return (NULL);
	}

	/* Copy the environment variables */
	for (env_count = 0; environ[env_count]; env_count++)
	{
		new_environ[env_count] = _strdup(environ[env_count]);
		if (!new_environ[env_count])
		{
			_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
			return (NULL);
		}
	}

	/* Set the last element of the array to NULL */
	new_environ[env_count] = NULL;

	return (new_environ);
}
