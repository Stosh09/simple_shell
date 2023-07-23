#include "shell.h"

/**
 * printError - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @message: message to print
 *
 * Return: void
 */

void printError(inputs_s *vars, char *message)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (message)
		_puts2(message);
	else
	{
		perror("");
	}
}

/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */

ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Error");
		return (-1);
	}
	return (len);
}

/**
 * _puts2 - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */

void _puts2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Error");
		exit(1);
	}
}

/**
 * printError2 - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @message: message to print
 *
 * Return: void
 */

void printError2(inputs_s *vars, char *message)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts(": ");
	_puts2(vars->av[0]);
	if (message)
	{
		_puts2(": ");
		_puts2(message);
		if (vars->av[1])
			_puts2(vars->av[1]);
		_puts2("\n");
	}
	else
	{
		perror("");
	}
}

/**
 * printsPrompt - prints the shell prompt
 */

void printsPrompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}
