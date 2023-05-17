#include "main.h"

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
 * Return: Pointer to the new environ array, or NULL if fails
 */
char **copy_environ(void)
{
    int i, count;
    char **new_environ;

    /* Count the number of environment variables */
    for (count = 0; environ[count] != NULL; count++)
        ;

    /* Allocate memory for the new environ array */
    new_environ = malloc((count + 1) * sizeof(char *));
    if (!new_environ)
        return (NULL);

    /* Copy the environment variables */
    for (i = 0; i < count; i++)
    {
        new_environ[i] = _strdup(environ[i]);
        if (new_environ[i] == NULL)
        {
            /* Free any previously allocated memory in case of failure */
            while (i--)
                free(new_environ[i]);
            free(new_environ);
            return (NULL);
        }
    }

    /* Set the last element to NULL */
    new_environ[count] = NULL;

    return (new_environ);
}
