#include "shell.h"
/**
 * alias - displays and alias commands
 * @vars: contains struct members
 */

void alias(inputs_s *vars)
{
	unsigned int a = 0, b = 0;

	if (vars->av[1] == NULL)
		print_vars(vars->aliases);
	else
	{
		while (vars->av[b])
		{
			if (strchr(vars->av[b], '=') != NULL)
				updateAlias(vars, b);
			else
			{
				while (vars->aliases[a])
				{
					if (check_name_similarity(vars->aliases[a], vars->av[b]))
					{
						_puts(vars->aliases[a]);
						_puts("\n");
						break;
					}
					a++;
				}
			}
			b++;
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
	unsigned int len = 0, a = 0;

	for (a = 0; input[a]; a++)
	{
		if (input[a] == '=')
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
 * @b: vars->av at the position
 */
void updateAlias(inputs_s *vars, unsigned int b)
{
	unsigned int a = 0;

	if (vars->aliases == NULL)
		vars->aliases = malloc(sizeof(char *) * 2);
	else
	{
		while (vars->aliases[a])
		{
			if (check_name_similarity(vars->aliases[a], vars->aliases[b]))
			{
				free(vars->aliases[a]);
				vars->aliases[a] = storeAlias(vars->av[b]);
				return;
			}
			a++;
		}
		vars->aliases = _realloc(vars->aliases, a, a + 2);
	}
	if (vars->aliases == NULL)
	{
		perror("Error");
		exit(1);
	}
	vars->aliases[a] = storeAlias(vars->av[b]);
	a++;
	vars->aliases[a] = NULL;
}

/**
 * *storeAlias - stores an alias with quotes in
 * @str: string to be stored
 * Return: a copy of the string with quotes embeded
 */

char *storeAlias(char *str)
{
	unsigned int a = 0, c = 0;
	char copy[1024];

	if (str != NULL)
	{
		for (a = 0, c = 0; str[a]; a++)
		{
			if (str[a] != '\'' && str[a] != '\"')
			{
				copy[c] = str[a];
				c++;
			}
			if (str[a] == '=')
			{
				copy[c] = '\'';
				c++;
			}
		}
		copy[c++] = '\'';
		copy[c] = '\0';
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
	size_t a = 0, c = 0, b = 0, len = 0;
	char alias_copy[1024];

	len = _strlen(vars->av[0]);
	while (vars->aliases != NULL && vars->aliases[a] != NULL)
	{
		if (check_name_similarity(vars->aliases[a], vars->av[0]))
		{
			for (c = len, b = 0; vars->aliases[a][c]; c++)
			{
				if (vars->aliases[a][c] == '=' || vars->aliases[a][c] == '\'')
					continue;
				else
				{
					alias_copy[b] = vars->aliases[a][c];
					b++;
				}
			}
			alias_copy[b] = '\0';
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
		a++;
	}
}
