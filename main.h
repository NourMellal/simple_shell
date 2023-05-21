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
#include <signal.h>

#define BUFFER_SIZE 2048

typedef struct shell shell;


/**
 * struct cmd - Struct to store a command name and function pointer
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
 * @input: An array of strings containing commands from the user input
 * @args: An array of strings containing arguments from the user input
 * @environ_copy: An array of strings containing a copy of the environ
 * @builtins: A pointer to an array of containing about the builtin commands
 * @num_builtins: The count of builtin commands
 * @cmd_count: The count of commands in the user input
 * @status: The exit status of the last command executed
 * @run: A boolean whether or not the shell should continue running
 */
struct shell
{
	char **input;
	char **args;
	char **environ_copy;
	cmd *builtins;
	int num_builtins;
	int cmd_count;
	int status;
	int run;
};


extern char **environ;

/* string_tools */
int _strlen(char *s);
void reverse_str(char s[]);
int _stoa(char *s, char *buf);
int _strcmp(const char *s1, const char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);
char *_strtok(char *str, char *delim);


/* main */
void init_shell(shell *sh);
void free_shell(shell *sh);


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
void *_realloc(void *ptr, ssize_t old_size, ssize_t new_size);
void free_double(char ***ptr);


/* input*/
void read_input(shell *sh);
void parse_command(shell *sh, char *cmd);


/* builtins functions*/
cmd *get_built(void);
int num_built(void);
static void cmd_exit(shell *sh);
static void cmd_env(shell *sh);
static void cmd_cd(shell *sh);
cmd *get_builtins(void);

/* system tools*/
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_getenv(const char *name);
void copy_environ(shell *sh);

/* builtins */

void cmd_setenv(shell *sh);
void cmd_unsetenv(shell *sh);
cmd *get_builtins(void);

#endif
