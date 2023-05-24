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
 * @curr_line: Pointer to the current line number
 */
void external_command(shell *sh, int *curr_line)
{
	pid_t pid;
	int ret, wstatus;
	char *full_path = NULL;

	/* Check if the command is an absolute or relative path */
	if (sh->args[0][0] == '/' || sh->args[0][0] == '.')
		full_path = sh->args[0];
	/* OR find the full path of the command */
	else
		full_path = find_command(sh->args[0]);

	if (full_path)
	{
		pid = fork();
		if (pid == 0)
		{
			ret = execve(full_path, sh->args, environ);
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
		if (full_path != sh->args[0])
			free(full_path);
	}
	else
	{
		if (sh->interactive)
			_fprintf(STDERR_FILENO, "%s: command not found\n", sh->args[0]);
		else
			_fprintf(STDERR_FILENO, "%s: line %d: %s: command not found\n",
					 "shs", *curr_line, sh->args[0]);
		sh->status = 127;
	}
}

/**
 * execute_command - Executes a command
 * @sh: Pointer to the shell structure
 * @curr_line: Pointer to the current line number
 */
void execute_command(shell *sh, int *curr_line)
{
	int j;
	char *alias_value;

	j = builtin_command(sh);
	if (j == sh->num_builtins)
	{
		/* TODO: add aliases contain also args */
		alias_value = get_alias_value(sh, sh->args[0]);
		if (alias_value)
			sh->args[0] = alias_value;

		external_command(sh, curr_line);
	}
	(*curr_line)++;

	free(sh->args);
	sh->args = NULL;
}

/**
 * process_command - Reads input, parses it, and executes the cmd
 * @sh: Pointer to the shell structure
 * NOTE: '&&' still doesn't handle failed cmd
 */
void process_command(shell *sh)
{
	int i, curr_line = 1;
	char *oprs = ";|&", *saveptr, *cmd;

	read_input(sh);
	if (!sh->input)
		return;

	for (i = 0; i < sh->cmd_count; i++)
	{
		cmd = _strtok_r(sh->input[i], oprs, &saveptr);
		while (cmd != NULL)
		{
			/* Parse the command and its arguments */
			parse_command(sh, cmd);
			/* Check if sh->args[0] is NULL or an empty string */
			if (sh->args[0] && sh->args[0][0])
				execute_command(sh, &curr_line);
			cmd = _strtok_r(NULL, oprs, &saveptr);
		}
	}

	sh->cmd_count = 0;
	if (sh->input)
		free_double(&sh->input);
}
