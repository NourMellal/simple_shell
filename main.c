#include "main.h"

/**
 * main - Entry point for the shell program
 * Return: The status code of the last command executed
 */
int main(void)
{
	shell sh = {NULL};

	init_shell(&sh);

	while (sh.run)
	{
		if (isatty(STDIN_FILENO))
			_printf("myshell> ");

		execute_command(&sh);
	}

	free_shell(&sh);
	return (sh.status);
}

/**
 * init_shell - Initialize the shell struct
 * @sh: Pointer to the shell structure
 */
void init_shell(shell *sh)
{
	cmd *builtins = get_builtins();

	sh->builtins = builtins;
	sh->num_builtins = 0;
	sh->cmd_count = 0;
	sh->status = 0;
	sh->run = 1;
	copy_environ(sh);

	while (builtins[sh->num_builtins].name)
		sh->num_builtins++;
}

/**
 * free_shell - Frees the memory allocated for a shell structure
 * @sh: The shell structure to be freed
 */
void free_shell(shell *sh)
{
	if (sh->input)
		free_double(&sh->input);

	/* Free the memory allocated for the environ_copy member */
	if (sh->environ_copy)
		free_double(&sh->environ_copy);
}
