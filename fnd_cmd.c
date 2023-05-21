#include "main.h"
/**
 * find_command - Finds the full path of a command in the PATH environment
 * @command: The command to search for
 * Return: A pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);
	char *dir = _strtok(path_copy, ":");
	char *full_path = malloc(_strlen(command) + _strlen(path) + 2);

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
