#include "main.h"

/**
 * _atoi - convert a string of digits into an integer
 * @str: the string to be converted
 * Return: the converted integer
 */
int _atoi(const char *str)
{
	unsigned int i = 0, result = 0, sign = 1;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	for (; str[i] >= '0' && str[i] <= '9'; i++)
		result = result * 10 + (str[i] - '0');

	return (sign * result);
}

/**
 * _itoa - convert a integer to a string in the given base (n)
 * @x: the integer to convert
 * @s: the output string
 * @base: the base of the number
 * @sign: whether or not to include a sign character
 * Return: the length of the string.
 */
int _itoa(long x, char s[], int base, int sign)
{
	unsigned int n, i = 0, neg = 0;

	if (sign && x < 0)
	{
		neg = 1;
		n = -x;
	}
	else
		n = x;

	do
		s[i++] = n % base + '0';
	while ((n /= base) > 0);

	if (neg)
		s[i++] = '-';

	s[i] = '\0';
	reverse_str(s);
	return (i);
}

/**
 * _realloc - reallocate a block of memory
 * @ptr: pointer to the memory previously allocated
 * @old_size: size of the memory block pointed by ptr
 * @new_size: new size of the memory block to be allocated
 * Return: pointer to the newly allocated memory, or NULL if it fails
 */
void *_realloc(void *ptr, ssize_t old_size, ssize_t new_size)
{
	void *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
	free(ptr);

	return (new_ptr);
}

/**
 * free_double - Frees a double pointer
 * @ptr: The double pointer to be freed
 */
void free_double(char ***ptr)
{
	int i;

	for (i = 0; (*ptr)[i]; i++)
		free((*ptr)[i]);
	free(*ptr);
	*ptr = NULL;
}
