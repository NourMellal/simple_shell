#include "main.h"
#include <stdio.h>

/**
 * cmd_exit - exits the program
 * @sh: Pointer to the shell structure
 */
static void cmd_exit(shell *sh)
{
	int status = 0;

	if (sh->args[1])
		status = _atoi(sh->args[1]);

	free(sh->input);
	exit(status);
}

/**
 * cmd_env - prints the current environment
 * @sh: Pointer to the shell structure
 */
static void cmd_env(shell *sh)
{
	unsigned int i;
	(void)(sh);

	if (!environ)
	{
		_fprintf(STDERR_FILENO, "Error: environ is NULL\n");
		return;
	}
	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

/**
 * cmd_cd - Change the current working directory
 * @sh: Pointer to the shell structure
 */
static void cmd_cd(shell *sh)
{
	char buf[BUFFER_SIZE];
	char *new_dir, *old_dir;

	old_dir = getcwd(buf, BUFFER_SIZE);

	if (!sh->args[1])
		new_dir = _getenv("HOME");
	else if (_strcmp(sh->args[1], "-", -1) == 0)
	{
		new_dir = getenv("OLDPWD");
		_printf("%s\n", new_dir);
	}
	else
		new_dir = sh->args[1];

	if (chdir(new_dir) != 0)
		perror("cd");

	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", getcwd(buf, BUFFER_SIZE), 1);
}

cmd *get_builtins(void)
{
	static cmd builtins[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"cd", cmd_cd},
		{NULL, NULL},
	};
	return (builtins);
}

