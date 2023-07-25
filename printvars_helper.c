#include "shell.h"

/**
 * printVars - does the printing of variables
 * @variable: variable being printed
 */
void printVars(char **variable)
{
	unsigned int j = 0;

	if (variable != NULL)
	{
		while (variable[j] != NULL)
		{
			_puts(variable[j]);
			_puts("\n");
			j++;
		}
	}
}
