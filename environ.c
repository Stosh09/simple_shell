#include "shell.h"

/**
 * copyEnvironment- make the shell environment that's passed to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */

char **copyEnvironment(char **env)
{
	char **newenv = NULL;
	size_t a;

	if (env == NULL)
		return (NULL);
	for (a = 0; env[a] != NULL; a++)
		;
	newenv = malloc(sizeof(char *) * (a + 1));
	if (newenv == NULL)
	{
		perror("Error");
		exit(1);
	}
	a = 0;
	while (env[a])
	{
		newenv[a] = _strdup(env[a]);
		a++;
	}
	newenv[a] = NULL;
	return (newenv);
}

/**
 * freeEnvironment- free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */

void freeEnvironment(char **env)
{
	unsigned int a = 0;

	while (env[a])
		free(env[a++]);
	free(env);
}

/**
 * addKey - create a new environment variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */

void addKey(inputs_s *vars)
{
	unsigned int a = 0;
	char **newenv;

	for (a = 0; vars->env[a] != NULL; a++)
		;
	newenv = malloc(sizeof(char *) * (a + 2));
	if (newenv == NULL)
	{
		printError(vars, NULL);
		vars->status = 127;
		myExit(vars);
	}
	a = 0;
	while (vars->env[a])
	{
		newenv[a] = vars->env[a];
		a++;
	}
	newenv[a] = addValue(vars->av[1], vars->av[2]);
	if (newenv[a] == NULL)
	{
		printError(vars, NULL);
		freesCommands(vars);
		free(newenv);
		exit(127);
	}
	newenv[a + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * findKey- finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */

char **findKey(char **env, char *key)
{
	unsigned int a, b, len;

	len = _strlen(key);
	for (a = 0; env[a] != NULL; a++)
	{
		for (b = 0; b < len; b++)
			if (key[b] != env[a][b])
				break;
		if (b == len && env[a][b] == '=')
			return (&env[a]);
	}
	return (NULL);
}

/**
 * addValue - create a new environment variable string
 * @key: variable name
 * @val: variable value
 *
 * Return: pointer to the new string;
 */

char *addValue(char *key, char *val)
{
	unsigned int len1, len2, a = 0, b = 0;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(val);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new ==  NULL)
		return (NULL);

	while (key[a] != '\0')
	{
		new[a] = key[a];
		a++;
	}
	new[a] = '=';
	for (b = 0; val[b] != '\0'; b++)
		new[a + 1 + b] = val[b];
	new[a + 1 + b] = '\0';
	return (new);
}
