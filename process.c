#include "shell.h"

/**
 * process_input - process the user input
 * @input: user input to process
 * @vars: shell variables
 */

void processInput(char *input, inputs_s *vars)
{
	unsigned int i = 0;

	vars->count++;

	vars->commands = getCommand(input, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->str_cmd = _strdup(vars->commands[i]);
		vars->ops_cmd = getCommand(vars->str_cmd, "&|");
		checkLogicalOperator(vars, vars->commands[i]);
		free(vars->str_cmd);
		free(vars->ops_cmd);
	}
	free(vars->commands);
}

/**
 * check_logical_ops - executes according to logical operators
 * @vars: input variables struct
 * @cmd_str: current command
 */

void checkLogicalOperator(inputs_s *vars, char *cmd_str)
{
	unsigned int b = 0, index = 0;
	char op = '\0';
	int result = 0;

	while (vars->ops_cmd[b])
	{
		if (b == 0)
			result = runCommand(vars, vars->ops_cmd[b]);
		op = getOperator(cmd_str, &index);
		if (op)
		{
			if (result == 0)
			{
				if (op == '&')
				{
					b++;
					result = runCommand(vars, vars->ops_cmd[b]);
				}
				else
					b++;
			}
			else
			{
				if (op == '&')
					b++;
				else
				{
					b++;
					result = runCommand(vars, vars->ops_cmd[b]);
				}
			}
		}
		else
			b++;
	}
}

/**
 * run_command - gets command with arguments and calls executing function
 * @vars: input variables struct
 * @cmd_str: current command
 * Return: status after execution
 */

int runCommand(inputs_s *vars, char *cmd_str)
{
	size_t len = _strlen("alias");

	if ((strncmp(cmd_str, "alias", len) == 0) && (cmd_str[len] == ' '))
		vars->av = getAlias(cmd_str, "\n \t\r");
	else
		vars->av = getCommand(cmd_str, "\n \t\r");
	if (vars->av && vars->av[0])
	{
		subEnv(vars);
		subAlias(vars);

		if (exeBuiltin(vars))
			getPath(vars);
	}
	freeAvandAlias(vars->av);
	return (vars->status);
}

/**
 * get_operator - check for logical operators in a line of command
 * @command: current command
 * @index: pointer to the logical operator index in command string
 * Return: the type of logical operator
 */

char getOperator(char *command, unsigned int *index)
{
	unsigned int i = *index;

	for (; command[i]; i++)
	{
		if (command[i] == '&' || command[i] == '|')
		{
			++i;
			if (command[i] == '&' || command[i] == '|')
				*index = i + 1;
			else
				return ('\0');

			return (command[i]);
		}
	}
	return ('\0');
}