#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * find_command - Finds the full path of a command in the PATH environment
 * @command: The command to search for
 * Return: A pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path = NULL, *path_copy = NULL;
	char *dir = NULL, *full_path = NULL;

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	dir = _strtok(path_copy, ":");
	full_path = malloc(_strlen(command) + _strlen(path) + 2);

	while (dir != NULL)
	{
		_sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);
	return (NULL);
}
