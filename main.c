#include "shell.h"

/**
 * signal_handler - it will handles ^C  interruption
 * @uv: unused variable required 4 signal function prototype
 */
static void signal_handler(int uv)
{
	(void)uv;
	_puts("\n$ ");
}

/**
 * main - main shell function
 * @argc: argument count
 * @argv: arguments (vector)
 * @env: environment variables array
 *
 * Return: returns 0 or exit status
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	size_t buffer_length = 0;
	unsigned int term = 0;
	inputs_s vars = {NULL, NULL, NULL, 0, NULL, 0, NULL, NULL, NULL, NULL};

	vars.argv = argv;
	vars.env = copyEnvironment(env);

	signal(SIGINT, signal_handler);

	term = isatty(STDIN_FILENO);

	if (term)
		printsPrompt();

	while (getline(&(vars.buffer), &buffer_length, stdin) != -1)
	{
		processInput(vars.buffer, &vars);

		free(vars.buffer);
		vars.buffer = NULL;
		if (term)
			printsPrompt();
	}

	if (term)
		_puts("\n");

	freeAvandAlias((&vars)->aliases);
	freeEnvironment(vars.env);
	free(vars.buffer);
	exit(vars.status);
}

/**
 * freesCommands - frees alias commands/inputs
 * @vars: contains struct members
 */

void freesCommands(inputs_s *vars)
{
	free(vars->buffer);
	free(vars->commands);
	free(vars->str_cmd);
	free(vars->ops_cmd);
	freeAvandAlias(vars->av);
	freeEnvironment(vars->env);
	freeAvandAlias(vars->aliases);

}

