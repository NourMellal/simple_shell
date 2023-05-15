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
