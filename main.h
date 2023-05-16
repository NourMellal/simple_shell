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
typedef struct shell
{
	char *input;
	char **args;
	cmd *builtins;
	int num_builtins;
	int status;
} shell;

extern char **environ;

/* string_tools */
int _strlen(char *s);
void str_rev(char s[]);
int _stoa(char *s, char *buf);
int _strcmp(const char *s1, const char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);
char *_strtok(char *str, char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);


/* main */
void init_builtins(shell *sh);


/* Sprintf */
void _printf(const char *fmt, ...);
void _fprintf(int fd, const char *fmt, ...);
void _sprintf(char *str, const char *fmt, ...);

/* Execution */
void execute_command(shell *sh);
char *find_command(char *command);
int builtin_command(shell *sh);
void external_command(shell *sh);


/* num_tools */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* input*/
char **read_input(char **input);
char *read_line(void);


/* builtins functions*/
cmd *get_built(void);
int num_built(void);
static void cmd_exit(shell *sh);
static void cmd_env(shell *sh);
static void cmd_cd(shell *sh);
cmd *get_builtins(void);

/* system tools*/
char *_getenv(const char *name);
ssize_t _getline(char **lineptr, size_t *n, int fd);

#endif