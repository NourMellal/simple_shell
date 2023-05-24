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
#define ALIASES_SIZE 100

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
 * struct alias - Struct for storing an alias name and value
 * @name: Pointer to the alias name
 * @value: Pointer to the alias value
 */
typedef struct alias
{
	char *name;
	char *value;
} alias;


/**
 * struct shell - Struct contains information about the shell environment
 * @input: An array of strings containing commands from the user input
 * @args: An array of strings containing arguments from the user input
 * @environ_copy: An array of strings containing a copy of the environ
 * @builtins: A pointer to an array of containing about the builtin commands
 * @num_builtins: The count of builtin commands
 * @cmd_count: The count of commands in the user input
 * @status: The exit status of the last command executed
 * @interactive: A boolean whether the program is running interactively or not
 * @builtins: A pointer to an array of containing about the builtin commands
 * @run: A boolean whether or not the shell should continue running
 * @aliases: An array of alias structures containing user-defined aliases
 * @argc: args count
 * @argv: arguments
 */

struct shell
{
	char **input;
	char **args;
	char **environ_copy;
	int num_builtins;
	int cmd_count;
	int status;
	int run;
	int argc;
	char **argv;
	int interactive;
	cmd *builtins;
	alias aliases[ALIASES_SIZE];
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
char *_strtok_r(char *str, const char *delim, char **saveptr);
char *_strchr(char *s, int c);

/* main */
void init_shell(shell *sh, int argc, char **argv);
void free_shell(shell *sh);


/* Sprintf */
void _printf(const char *fmt, ...);
void _fprintf(int fd, const char *fmt, ...);
void _sprintf(char *str, const char *fmt, ...);

/* Execution */
char *find_command(char *command);
int builtin_command(shell *sh);
void process_command(shell *sh);
void execute_command(shell *sh, int *curr_line);
void external_command(shell *sh, int *curr_line);

/* num_tools */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);
void *_realloc(void *ptr, ssize_t old_size, ssize_t new_size);
void free_double(char ***ptr);
int is_num(char *str);

/* input*/
void read_input(shell *sh);
void parse_command(shell *sh, char *cmd);


/* builtins functions*/
cmd *get_built(void);
int num_built(void);
cmd *get_builtins(void);
char *get_alias_value(shell *sh, char *name);
void cmd_alias(shell *sh);
void update_environment(shell *sh, char *env_var);


/* system tools*/
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_getenv(const char *name);
char **copy_environ(void);

/* builtins */

void cmd_setenv(shell *sh);
void cmd_unsetenv(shell *sh);
cmd *get_builtins(void);

#endif
