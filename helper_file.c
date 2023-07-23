#include "shell.h"


/**
 * _strdup - duplucates string
 * @str_dup: string to be duplicated
 * Return: returns a pointer to the duplicated string
 */
char *_strdup(char *str_dup)
{
	char *str_copy;
	int length, k;

	if (str_dup == 0)
		return (NULL);

	for (length = 0; str_dup[length]; length++)
		;
	str_copy = malloc((length + 1) * sizeof(char));

	for (k = 0; k <= length; k++)
		str_copy[k] = str_dup[k];

	return (str_copy);
}

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

/**
 * _strcat - does concatenation
 * @string1: first string
 * @string2: second string
 * Return: pointer
 */
char *_strcat(char *string1, char *string2)
{
	char *new_string;
	unsigned int length_1, length_2, new_lenth, i, k;

	length_1 = 0;
	length_2 = 0;
	if (string1 == NULL)
		length_1 = 0;
	else
	{
		for (length_1 = 0; string1[length_1]; length_1++)
			;
	}
	if (string2 == NULL)
		length_2 = 0;
	else
	{
		for (length_2 = 0; string2[length_2]; length_2++)
			;
	}
	new_lenth = length_1 + length_2 + 2;
	new_string = malloc(new_lenth * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	for (i = 0; i < length_1; i++)
		new_string[i] = string1[i];
	new_string[i] = '/';
	for (k = 0; k < length_2; k++)
		new_string[i + 1 + k] = string2[k];
	new_string[length_1 + length_2 + 1] = '\0';
	return (new_string);
}

/**
 * _strlen - calclates string length.
 * @string: string whose length is being calculated
 * Return: string length
 */
unsigned int _strlen(char *string)
{
	unsigned int length = 0;

	for (length = 0; string[length]; length++)
	{
		;
	}

	return (length);
}

/**
 * print_vars - does the printing of variables
 * @variable: variable being printed
 */
void print_vars(char **variable)
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

