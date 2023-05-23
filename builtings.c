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

	free_shell(sh);
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
	char *oldpwd_var, *pwd_var;
	char *new_dir, *old_dir;

	old_dir = getcwd(buf, BUFFER_SIZE);

	if (!sh->args[1])
		new_dir = _getenv("HOME");
	else if (_strcmp(sh->args[1], "-", -1) == 0)
	{
		new_dir = _getenv("OLDPWD");
		_printf("%s\n", new_dir);
	}
	else
		new_dir = sh->args[1];

	if (chdir(new_dir) != 0)
		perror("cd");

	oldpwd_var = malloc(100);
	pwd_var = malloc(100);


	_sprintf(oldpwd_var, "OLDPWD=%s", old_dir);
	_sprintf(pwd_var, "PWD=%s", getcwd(buf, BUFFER_SIZE));

	update_environment(sh, oldpwd_var);
	update_environment(sh, pwd_var);
}

/**
 * get_builtins - Returns an array of builtin commands
 * Return: Pointer to the array of builtin commands
 */
cmd *get_builtins(void)
{
	static cmd builtins[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"cd", cmd_cd},
		{"setenv", cmd_setenv},
		{"alias", cmd_alias},
		{"unsetenv", cmd_unsetenv},
		{NULL, NULL},
	};
	return (builtins);
}
