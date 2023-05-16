#ifndef MAIN_H
#define MAIN_H

/* including the files for sShell project */

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFFER_SIZE 2048

typedef struct shell shell;


/**
 * struct command - Struct to store a command name and function pointer
 * @name: Pointer to the command name string
 * @func: Pointer to the function associated with the command
 */
typedef struct cmd
{
	char *name;
	void (*func)(shell *);
} cmd;

/**
 * struct shell - Struct contains information about the shell environment
 * @input: A pointer to a string containing the user's input
 * @args: An array of strings containing the arguments from the user's input
 * @builtins: A pointer to an array of containing about the builtin commands
 * @num_builtins: The number of builtin commands
 * @status: The exit status of the last command executed
 */
struct shell
{
	char *input;
	char **args;
	cmd *builtins;
	int num_builtins;
	int status;
};
