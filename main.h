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

#define MAX_SIZE 1024


/**
 * struct command - Struct to store a command name and function pointer
 * @name: Pointer to the command name string
 * @func: Pointer to the function associated with the command
 */
typedef struct command
{
	char *name;
	void (*func)(char **);
} cmd;


/* string_tools */
int str_len(char *s);
void str_rev(char s[]);
int _stb(char *s, char *buf);
int _strcmp(const char *s1, const char *s2);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);

/* main */
void execute_command(char **args, int *status);

/* Sprintf */
void _vsprintf(char *str, const char *fmt, va_list ap);
void _printf(const char *fmt, ...);
void _fprintf(int fd, const char *fmt, ...);
void _sprintf(char *str, const char *fmt, ...);

/* num_tools */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);

#endif