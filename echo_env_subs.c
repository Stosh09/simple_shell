#include "shell.h"
/**
 * subEnv - does the substitution of environment variables
 * @vars: variables
 */

void subEnv(inputs_s *vars)
{

	size_t k = 0;
	char **copy_av = copyEnvironment(vars->av);
	pid_t pid = getpid();
	char *path = NULL, *env = NULL;


	while (copy_av != NULL && copy_av[k] != NULL)
	{
		if (_strcmp(copy_av[k], "$?") == 0)
		{
			vars->av[k] = _malloc(32);
			sprintf(vars->av[k], "%d", vars->status);
		}
		else if (_strcmp(copy_av[k], "$$") == 0)
		{
			vars->av[k] = _malloc(32);
			sprintf(vars->av[k], "%d", pid);
		}
		else if (copy_av[k][0] == '$' && copy_av[k][1] != '\0')
		{
			path = &(copy_av[k][1]);
			env = getEnv(vars, path);
			if (env)
				vars->av[k] = _strdup(env);
			else
				vars->av[k] = _strdup("");
		}
		else
			vars->av[k] = _strdup(copy_av[k]);
		k++;
	}
	freeAvandAlias(copy_av);
}


/**
  * freeAvandAlias - does the freeing of av commands
  * @s: inputs of either var->alias/av
  */
void freeAvandAlias(char **s)
{
	size_t k = 0;

	if (s == NULL)
		return;

	while (s[k])
	{
		free(s[k]);
		k++;
	}

	free(s);
}

