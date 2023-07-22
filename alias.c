#include "shell.h"
/**
 * alias - displays and alias commands
 * @vars: contains struct members
 */

void alias(inputs_s *vars)
{
	unsigned int i = 0, k = 0;

	if (vars->av[1] == NULL)
		print_vars(vars->aliases);
	else
	{
		while (vars->av[k])
		{
			if (strchr(vars->av[k], '=') != NULL)
				update_alias(vars, k);
			else
			{
				while (vars->aliases[i])
				{
					if (check_name_match(vars->aliases[i], vars->av[k]))
					{
						_puts(vars->aliases[i]);
						_puts("\n");
						break;
					}
					i++;
				}
			}
			k++;
		}
	}
	vars->status = 0;
}

/**
 * check_name_similarity - checks if av name matches aliases
 * @an_alias: an alias string in vars-aliases
 * @input: a command string in vars->av
 * Return: 1 if match, 0 if no match
 */

int check_name_similarity(char *an_alias, char *input)
{
	unsigned int len = 0, i = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '=')
			break;
		len++;
	}
	if ((strncmp(an_alias, input, len) == 0) && (an_alias[len] == '='))
		return (1);
	return (0);
}

/**
 * updateAlias-updates alias
 * @vars: contains struct members
 * @k: vars->av at the position
 */
void updateAlias(inputs_s *vars, unsigned int k)
{
	unsigned int i = 0;

	if (vars->aliases == NULL)
		vars->aliases = malloc(sizeof(char *) * 2);
	else
	{
		while (vars->aliases[i])
		{
			if (check_name_match(vars->aliases[i], vars->aliases[k]))
			{
				free(vars->aliases[i]);
				vars->aliases[i] = store_alias(vars->av[k]);
				return;
			}
			i++;
		}
		vars->aliases = _realloc(vars->aliases, i, i + 2);
	}
	if (vars->aliases == NULL)
	{
		perror("Error");
		exit(1);
	}
	vars->aliases[i] = store_alias(vars->av[k]);
	i++;
	vars->aliases[i] = NULL;
}

/**
 * *storeAlias - stores an alias with quotes in
 * @str: string to be stored
 * Return: a copy of the string with quotes embeded
 */

char *storeAlias(char *str)
{
	unsigned int i = 0, j = 0;
	char copy[1024];

	if (str != NULL)
	{
		for (i = 0, j = 0; str[i]; i++)
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				copy[j] = str[i];
				j++;
			}
			if (str[i] == '=')
			{
				copy[j] = '\'';
				j++;
			}
		}
		copy[j++] = '\'';
		copy[j] = '\0';
		return (_strdup(copy));
	}
	return (NULL);
}

/**
 * subAlias - substitutes alias for respective commands
 * @vars: contains members of the struct
 */
void subAlias(inputs_s *vars)
{
	size_t i = 0, j = 0, k = 0, len = 0;
	char alias_copy[1024];

	len = _strlen(vars->av[0]);
	while (vars->aliases != NULL && vars->aliases[i] != NULL)
	{
		if (check_name_match(vars->aliases[i], vars->av[0]))
		{
			for (j = len, k = 0; vars->aliases[i][j]; j++)
			{
				if (vars->aliases[i][j] == '=' || vars->aliases[i][j] == '\'')
					continue;
				else
				{
					alias_copy[k] = vars->aliases[i][j];
					k++;
				}
			}
			alias_copy[k] = '\0';
			free(vars->av[0]);
			vars->av[0] = malloc(sizeof(char) * _strlen(alias_copy) + 1);
			if (vars->av[0] == NULL)
			{
				perror("Error");
				exit(1);
			}
			vars->av[0] = _strcpy(vars->av[0], alias_copy);
			subAlias(vars);
			return;
		}
		i++;
	}
}
