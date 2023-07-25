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
