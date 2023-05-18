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

	free_shell(&sh);
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

/**
 * free_shell - Frees the memory allocated for a shell structure
 * @sh: The shell structure to be freed
 */
void free_shell(shell *sh)
{
	size_t i;

	/* Free the memory allocated for the input member */
	if (sh->input != NULL)
		free(sh->input);

	/* Free the memory allocated for the environ_copy member */
	if (sh->environ_copy != NULL)
	{
		for (i = 0; sh->environ_copy[i] != NULL; i++)
			free(sh->environ_copy[i]);
		free(sh->environ_copy);
	}
}
