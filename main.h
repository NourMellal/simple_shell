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

/* string tools */
int str_len(char *s);
void str_rev(char s[]);
int _stb(char *s, char *buf);
int _strcmp(const char *s1, const char *s2);
void write_fd(int fd, char *s)
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);

/* num tools */
int _itoa(long x, char s[], int base, int sign);
int _atoi(const char *str);


#endif /* MIAN_H */