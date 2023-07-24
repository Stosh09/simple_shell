#include "shell.h"

/**
 * exeBuiltin - checks whether command is built in
 * @vars: variables being cheked
 * Return: it returns pointer to function otherwise NULL
 */
/*void (*check_for_builtins(inputs_s *vars))(inputs_s *vars)*/
int exeBuiltin(inputs_s *vars)
{
	unsigned int a = 0;
	builtin_s built_in[] = {
		{"exit", myExit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_command},
		{"alias", alias},
		{NULL, NULL}
	};

	while (built_in[a].f)
	{
		if (_strcmp(vars->av[0], built_in[a].name) == 0)
		{
			built_in[a].f(vars);
			return (0);
		}
		a++;
	}
	return (1);
}

/**
 * myExit - exit program
 * @vars: variables
 * Return: void
 */
void myExit(inputs_s *vars)
{
	int status = 0;

	if (vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			printError(vars, ": Incorrect number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	freesCommands(vars);
	exit(vars->status);
}

/**
 * _env - it prints current environment
 * @vars: variables
 */
void _env(inputs_s *vars)
{
	printVars(vars->env);
	vars->status = 0;
}

/**
 * _setenv - it either creates/edits an environment variable
 * @vars: variables
 */
void _setenv(inputs_s *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		printError(vars, ": Wrong count of arguments\n");
		vars->status = 2;
		return;
	}
	key = findKey(vars->env, vars->av[1]);
	if (key == NULL)
		addKey(vars);
	else
	{
		var = addValue(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			printError(vars, NULL);
			freesCommands(vars);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * _unsetenv - it removes environment variable
 * @vars: variables
 */
void _unsetenv(inputs_s *vars)
{
	char **key, **newenv;

	unsigned int a, b;

	if (vars->av[1] == NULL)
	{
		printError(vars, ": Wrong count of arguments\n");
		vars->status = 2;
		return;
	}
	key = findKey(vars->env, vars->av[1]);
	if (key == NULL)
	{
		printError(vars, ": No variable to unset\n");
		return;
	}
	for (a = 0; vars->env[a] != NULL; a++)
		;
	newenv = malloc(sizeof(char *) * a);
	if (newenv == NULL)
	{
		printError(vars, NULL);
		vars->status = 127;
		myExit(vars);
	}
	for (a = 0; vars->env[a] != *key; a++)
		newenv[a] = vars->env[a];
	for (b = a + 1; vars->env[b] != NULL; b++, a++)
		newenv[a] = vars->env[b];
	newenv[a] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}


