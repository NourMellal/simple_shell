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
	size_t env_count = 0, name_len;
	size_t old_size, new_size;
	char **new_environ, **env_ptr;
	int index;
	char *name_end = _strchr(env_var, '=');
	char name[BUFFER_SIZE];

	if (!name_end)
		return;
	if (!sh->environ_copy)
		sh->environ_copy = copy_environ();

	name_len = name_end - env_var;
	_memcpy(name, env_var, name_len);
	name[name_len] = '\0';
	index = find_environment(name);

	if (index >= 0)
	{
		free(sh->environ_copy[index]);
		sh->environ_copy[index] = env_var;
		return;
	}
	for (env_ptr = sh->environ_copy; *env_ptr; env_ptr++)
		env_count++;

	old_size = env_count * sizeof(char *);
	new_size = (env_count + 2) * sizeof(char *);
	new_environ = _realloc(sh->environ_copy, old_size, new_size);

	if (!new_environ)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		free(env_var);
		return;
	}
	sh->environ_copy = new_environ;
	sh->environ_copy[env_count] = env_var;
	sh->environ_copy[env_count + 1] = NULL;
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

	if (!sh->environ_copy)
		sh->environ_copy = copy_environ();

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
		sh->status = 2;
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
		sh->status = 2;
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
		sh->status = 1;
		return;
	}
	_sprintf(env_var, "%s=%s", sh->args[1], sh->args[2]);

	if (find_environment(sh->args[1]) == -1)
		update_environment(sh, env_var);
}
