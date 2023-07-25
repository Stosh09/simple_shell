#include "shell.h"

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
