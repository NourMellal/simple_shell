#include "main.h"

/**
 * main - Entry point for the shell program
 * Return: The status code of the last command executed
 */
int main(void)
{
	int should_run = 1;
	shell sh = {NULL};

	init_builtins(&sh);

	while (should_run)
	{
		if (isatty(STDIN_FILENO))
			_printf("myshell> ");

		sh.args = read_input(&sh.input);
		if (sh.args == NULL)
			break;

		execute_command(&sh);

		free(sh.input);
	}
	return (sh.status);
}

/**
 * init_builtins - Initialize the built-in commands for a shell
 * @sh: Pointer to the shell structure
 */
void init_builtins(shell *sh)
{
	cmd *builtins = get_builtins();

	sh->builtins = builtins;
	sh->num_builtins = 0;

	/* calculate the number of built-in commands */
	while (builtins[sh->num_builtins].name)
		sh->num_builtins++;
}
