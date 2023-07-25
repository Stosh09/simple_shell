#include "shell.h"

/**
 * _strcmp - does the comparison of two strings
 * @string_master: 1st string
 * @string_slave: 2nd string
 * Return: 0 on success, anything else is a failure
 */
int _strcmp(char *string_master, char *string_slave)
{
	int k;

	k = 0;

	while (string_master[k] == string_slave[k])
	{
		if (string_master[k] == '\0')
			return (0);
		k++;
	}

	return (string_master[k] - string_slave[k]);
}
