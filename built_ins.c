#include "shell.h"

/**
 * exeBuiltin - checks whether command is built in
 * @vars: variables being cheked
 * Return: it returns pointer to function otherwise NULL
 */
/*void (*check_for_builtins(inputs_s *vars))(inputs_s *vars)*/
int exeBuiltin(inputs_s *vars)
{
	unsigned int k = 0;
	builtin_s built_in[] = {
		{"exit", myExit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", alias},
		{NULL, NULL}
	};

	while (built_in[k].f)
	{
		if (_strcmp(vars->av[0], built_in[k].name) == 0)
		{
			built_in[k].f(vars);
			return (0);
		}
		k++;
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
			print_error(vars, ": Incorrect number: ");
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
	print_vars(vars->env);
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
		print_error(vars, ": Wrong count of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
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

	unsigned int k, j;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Wrong count of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset\n");
		return;
	}
	for (k = 0; vars->env[k] != NULL; k++)
		;
	newenv = malloc(sizeof(char *) * k);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		myExit(vars);
	}
	for (k = 0; vars->env[k] != *key; k++)
		newenv[k] = vars->env[k];
	for (j = k + 1; vars->env[j] != NULL; j++, k++)
		newenv[k] = vars->env[j];
	newenv[k] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}


