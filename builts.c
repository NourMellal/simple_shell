#include "main.h"

/**
 * exit_cmd - Function to handle the 'exit' command.
 * @args: Array of command arguments.
 *
 * Description: This function is responsible for handling the 'exit' command.
 * It performs necessary cleanup or actions before exiting the program with a
 * status code of 0.
 */
static void exit_cmd(char **args)
{
	(void)(args);
	exit(0);
}

/**
 * cmd_env - prints the current environment
 * @args: command line arguments
 */
static void cmd_env(char **args)
{
	unsigned int i;
	(void)(args);

	if (!environ)
	{
		_fprintf(STDERR_FILENO, "Error: environ is NULL\n");
		return;
	}
	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

static cmd builtins[] = {
	{"exit", exit_cmd},
};

/**
 * num_built - Get the number of built-in commands.
 *
 * Return: The number of built-in commands in the 'builtins' array.
 */
int num_built(void)
{
	return (sizeof(builtins) / sizeof(cmd));
}

/**
 * get_built - Get the array of built-in commands.
 *
 * Return: Pointer to the 'builtins' array.
 */
cmd *get_built(void)

{
	return (builtins);
}
