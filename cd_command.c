#include "shell.h"

/**
 * cd_command - the builtin command for changing directory
 * @vars: variables for command
 */
void cd_command(inputs_s *vars)
{
	char *home_directory = _getenv(vars, "HOME"), *path_name = NULL, *pwd = NULL;
	struct stat sb_var;

	if (vars->av[1] == NULL || vars->av[1][0] == '\0')
		path_name = home_directory ? _strdup(home_directory) : getcwd(path_name, 0);
	else if (_strcmp(vars->av[1], "-") == 0)
	{
		path_name = (_getenv(vars, "OLDPWD")) ? _strdup(_getenv(vars, "OLDPWD")) :
					getcwd(path_name, 0);
		_puts(path_name);
		_puts("\n");
	}
	else
	{
		if (vars->av[1][0] == '/')
			path_name = _strdup(vars->av[1]);
		else
		{
			pwd = getcwd(pwd, 0);
			path_name = _strcat(pwd, vars->av[1]);
			free(pwd);
		}
	}
	if (stat(path_name, &sb_var) == 0)
	{
		if (S_ISDIR(sb_var.st_mode))
			changeofDirectory(vars, path_name);
		else
		{
			printError2(vars, "cannot cd to ");
			vars->status = 2;
		}
	}
	else
	{
		printError2(vars, "cannot cd to ");
		vars->status = 2;
	}
	free(path_name);
}


/**
 * changeofDirectory - does the change of process working dir
 * & updates env elements
 * @vars: input variables
 * @path_name: new path to switch new
 */
void changeofDirectory(inputs_s *vars, char *path_name)
{
	char *init_pwd = NULL;

	init_pwd = getcwd(init_pwd, 0);

	if (access(path_name, R_OK) == -1)
	{
		printError2(vars, "cannot cd to ");
		vars->status = 2;
		return;
	}

	if (chdir(path_name) == -1)
	{
		printError(vars, NULL);
		return;
	}
	_setenv2(vars, "OLD_PWD", init_pwd, 1);
	_setenv2(vars, "PWD", path_name, 1);
	free(init_pwd);
	init_pwd = NULL;
	vars->status = 0;
}

/**
 * _setenv2 - adds and changes environment variable
 * @name: variable
 * @val: variable value
 * @o_write: flag determining value change of existing varable
 * @vars: variables being keyed in
 * Return: returns 0 on success and -1 on failure
 */
int _setenv2(inputs_s *vars, const char *name, const char *val, int o_write)
{
	size_t i = 0;
	char *new_envr = NULL;
	size_t len = 0, name_len = 0, val_len  = 0;

	name_len = strlen(name);
	val_len = strlen(val);
	len = 2 + name_len + val_len;
	new_envr = malloc(sizeof(char) * len);
	if (new_envr == NULL)
		return (-1);
	if ((snprintf(new_envr, len, "%.*s=%s", (int)name_len, name, val)) == -1)
		return (-1);
	while (vars->env[i])
	{
		if (strncmp(new_envr, vars->env[i], name_len) == 0)
		{
			if (o_write)
			{
				free(vars->env[i]);
				vars->env[i] = new_envr;
			}
			new_envr = NULL;
			vars->status = 0;
			return (0);
		}
		i++;
	}
	vars->env = _realloc(vars->env, i, i + 2);
	if (vars->env == NULL)
	{
		perror("Error");
		exit(1);
	}
	vars->env[i] = new_envr;
	new_envr = NULL;
	vars->status = 0;
	i++;
	vars->env[i] = NULL;
	return (0);
}


/**
  * _getenv - it gets the value of environment variable
  * @vars: variables
  * @name: the environment variable being searched
  * Return: value of success and null on failure
  */
char *_getenv(inputs_s *vars, const char *name)
{
	int i = 0;
	char *the_value = NULL;
	size_t len = strlen(name);


	while (vars->env[i])
	{
		if (strncmp(vars->env[i], name, len) == 0)
		{
			the_value = &(vars->env[i][len + 1]);
			return (the_value);
		}
		i++;
	}
	return (NULL);
}
