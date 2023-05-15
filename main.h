#ifndef MAIN_H
#define MAIN_H

/* including files for shell project */
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define B_SIZE 1024

typedef struct cname
{
	char *name;
	void (*fnc)(char **);
} cmd;

char *read_line(void);

int len(char *s);
void str_rev(char s[]);


#endif /* MIAN_H */