#include "main.h"

/**
 * find_environment - finds the index of an env variable in the environ
 * @name: the name of the environment variable to search for
 * Return: the index of the environment variable, or -1 if not found.
 */
int find_environment(char *name)
{
	char **env;
	int index = 0;
	size_t name_len = _strlen(name);

	for (env = environ; *env != NULL; env++, index++)
		/* Compare the environment variable name with the given name */
		if (_strcmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (index);

	return (-1);
}

/**
 * update_environment - updates the environment variables
 * @sh: pointer to the shell structure
 * @env_var: the new environment variable to add
 */
void update_environment(shell *sh, char *env_var)
{
	size_t env_count = 0;
	size_t old_size, new_size;
	char **new_environ, **env_ptr;

	/* Count the number of environment variables */
	for (env_ptr = sh->environ_copy; *env_ptr; env_ptr++)
		env_count++;

	old_size = env_count * sizeof(char *);
	new_size = (env_count + 2) * sizeof(char *);
	new_environ = _realloc(sh->environ_copy, old_size, new_size);

	if (new_environ == NULL)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		free(env_var);
		return;
	}

	/* Set the environ_copy variable to point to the newly allocated memory */
	sh->environ_copy = new_environ;
	/* Add the new environment variable to the end of the array */
	sh->environ_copy[env_count] = env_var;
	/* Set the last element of the array to NULL */
	sh->environ_copy[env_count + 1] = NULL;

	/* Update the global environ variable */
	environ = sh->environ_copy;
}

/**
 * remove_environment - removes an environment variable from the system
 * @sh: pointer to the shell structure
 */
void remove_environment(shell *sh)
{
	int index = find_environment(sh->args[1]);

	/* If the environment variable is not found, return */
	if (index == -1)
		return;

	free(sh->environ_copy[index]);

	/* Shift the remaining environment variables up by one */
	for (; sh->environ_copy[index] != NULL; index++)
		sh->environ_copy[index] = sh->environ_copy[index + 1];

	/* Update the global environ variable */
	environ = sh->environ_copy;
}

/**
 * cmd_unsetenv - unsets an environment variable
 * @sh: pointer to the shell structure
 */
void cmd_unsetenv(shell *sh)
{
	if (sh->args[1] == NULL)
	{
		_fprintf(STDERR_FILENO, "Usage: unsetenv VARIABLE\n");
		return;
	}

	remove_environment(sh);
}

/**
 * cmd_setenv - sets an environment variable
 * @sh: pointer to the shell structure
 */
void cmd_setenv(shell *sh)
{
	char *env_var;
	size_t name_len, value_len, env_var_len;

	if (!sh->args[1] || !sh->args[2])
	{
		_fprintf(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	name_len = _strlen(sh->args[1]);
	value_len = _strlen(sh->args[2]);

	/* +2 for '=' and '\0' */
	env_var_len = name_len + value_len + 2;
	env_var = malloc(env_var_len);

	if (!env_var)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		return;
	}
	_sprintf(env_var, "%s=%s", sh->args[1], sh->args[2]);

	if (find_environment(sh->args[1]) == -1)
	{
		/* If environ_copy has not been initialized yet */
		if (sh->environ_copy == NULL)
			copy_environ(sh);

		update_environment(sh, env_var);
	}
}
