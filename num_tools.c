#include "main.h"

/**
 * _itoa - Converts an integer to a string in the given base.
 * @x: The integer to convert.
 * @s: The output string.
 * @base: The base of the number.
 * @sign: Whether or not to include a sign character.
 * Return: The length of the string.
 */
int _itoa(long x, char s[], int base, int sign)
{
	unsigned int n;
	int i = 0, neg = 0;

	if (sign && x < 0)
	{
		neg = 1;
		n = -x;
	}
	else
		n = x;

	while (n > 0)
	{
		s[i++] = n % base + '0';
		n /= base;
	}

	if (neg)
		s[i++] = '-';

	s[i] = '\0';
	str_rev(s);
	return (i);
}

/**
 * _atoi - convert a string of digits into an integer
 * @str: the string to be converted
 * Return: the converted integer
 */
int _atoi(const char *str)
{
	unsigned int i = 0, result = 0, sgn = 1;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sgn = -1;
		i++;
	}

	for (; str[i] >= '0' && str[i] <= '9'; i++)
		result = result * 10 + (str[i] - '0');

	return (sgn * result);
}


#include "main.h"
#include <stdlib.h>
/**
* _realloc - reallocates a memory block using malloc and free
* @ptr: pointer to the memory previously allocated with malloc
* @old_size: size of the allocated space for ptr
* @new_size: size of the new memory block to be allocated
* Return: pointer to the new memory block, or NULL if allocation fails
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr1;
	char *old_ptr;
	unsigned int i;


	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	if (!ptr)
		return (malloc(new_size));

	ptr1 = malloc(new_size);
	if (!ptr1)
		return (NULL);

	old_ptr = ptr;

	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			ptr1[i] = old_ptr[i];
	}

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			ptr1[i] = old_ptr[i];
	}

	free(ptr);
	return (ptr1);
}
