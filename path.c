#include "shell.h"

/**
 * executeCommand - function that executes command
 * @cmd: command to execute
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */

int executeCommand(char *cmd, inputs_s *vars)
{
	struct stat buf;
	pid_t child_pid;

	if (stat(cmd, &buf) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				printError(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(cmd, vars->av, vars->env) == -1)
					printError(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			printError(vars, ": You do not have the necessary permission");
			vars->status = 126;
		}
		return (0);
	}
	printError(vars, ": Command not found");
	vars->status = 127;
	return (0);
}

/**
 * getPath - checks if the command is the PATH or current dir
 * @vars: variables struct
 *
 * Return: void
 */

void getPath(inputs_s *vars)
{
	char *path = getenv("PATH");
	char *cmd = vars->av[0];
	char *cmd_path = NULL;
	char *token;
	struct stat buf;
	char *path_copy;

	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &buf) == 0 && access(cmd, X_OK) == 0)
		{
			executeCommand(cmd, vars);
			return;
		}
	}
	else if (path != NULL)
	{
		path_copy = _strdup(path);
		token = _strtok(path_copy, ":");
		while (token != NULL)
		{
			cmd_path = malloc(strlen(token) + strlen(cmd) + 2);
			sprintf(cmd_path, "%s/%s", token, cmd);
			if (stat(cmd_path, &buf) == 0 && access(cmd_path, X_OK) == 0)
			{
				executeCommand(cmd_path, vars);
				free(cmd_path);
				free(path_copy);
				return;
			}
			free(cmd_path);
			token = _strtok(NULL, ":");
		}
		free(path_copy);
	}
	printError(vars, ": Command not found");
	vars->status = 127;
}
