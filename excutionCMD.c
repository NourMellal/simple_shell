#include "main.h"
#include <stdio.h>

/**
 * builtin_command - Executes a built-in cmd if it is found
 * @sh: Pointer to the shell structure
 * Return: Index of the built-in cmd that was executed, or 0 if none was found
 */
int builtin_command(shell *sh)
{
	int i;

	for (i = 0; i < sh->num_builtins; i++)
	{
		if (sh->args[0] && _strcmp(sh->args[0], sh->builtins[i].name, -1) == 0)
		{
			sh->builtins[i].func(sh);
			break;
		}
	}
	return (i);
}

/**
 * external_command - Self explain
 * @sh: Pointer to the shell structure
 */
void external_command(shell *sh)
{
	pid_t pid;
	int ret, wstatus;
	char *full_path = NULL;

	/* Check if the command is an absolute path */
	if (sh->args[0][0] == '/')
		full_path = sh->args[0];
	/* OR find the full path of the command */
	else
		full_path = find_command(sh->args[0]);

	if (full_path)
	{
		pid = fork();
		if (pid == 0)
		{
			ret = execve(full_path, sh->args, NULL);
			if (ret == -1)
				perror(sh->args[0]);
			_exit(ret);
		}
		else
		{
			wait(&wstatus);
			/* Get the exit status of the child */
			if (WIFEXITED(wstatus))
				sh->status = WEXITSTATUS(wstatus);
		}
		/* Free full_path in both the child and parent processes */
		if (full_path != sh->args[0])
			free(full_path);
	}
	else
		_fprintf(STDERR_FILENO, "%s: command not found\n", sh->args[0]);
}

/**
 * execute_command - Executes a command
 * @sh: Pointer to the shell structure.
 */
void execute_command(shell *sh)
{
	int i;

	i = builtin_command(sh);

	/* If it's not a builtin command */
	if (i == sh->num_builtins)
		external_command(sh);
}

/**
 * find_command - Finds the full path of a command in the PATH environment
 * @command: The command to search for
 * Return: A pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = _strdup(path);
	char *dir = _strtok(path_copy, ":");
	char *full_path = malloc(_strlen(cmd) + _strlen(path) + 2);

	while (dir != NULL)
	{
		_sprintf(full_path, "%s/%s", dir, cmd);
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
