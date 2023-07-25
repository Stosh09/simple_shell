#include "shell.h"
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
