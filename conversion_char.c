#include "shell.h"
#include "limits.h"

/**
 * _atoi - does the conversion of a string to integer
 * @string: string being converted
 * Return: integer value and -1 in error cases
 */
int _atoi(char *string)
{
	unsigned int i;
	unsigned int digits;
	int number = 0;
	int number_tested;

	number_tested = INT_MAX;

	for (digits = 0; number_tested != 0; digits++)
	{
		number_tested /= 10;
	}
	for (i = 0; string[i] != '\0' && i < digits; i++)
	{
		number *= 10;
		if (string[i] < '0' || string[i] > '9')
		{
			return (-1);
		}

		if ((i == digits - 1) && (string[i] - '0' > INT_MAX % 10))
		{
			return (-1);
		}

		number += string[i] - '0';

		if ((i == digits - 2) && (string[i + 1] != '\0') && (number > INT_MAX / 10))
		{
			return (-1);
		}
	}
	if (i > digits)
	{
		return (-1);
	}

	return (number);
}

/**
 * _uitoa - does the conversation of unsigned int to a string
 * @count: the unsigned int being converted
 * Return: it returns pointer to the converted string
 */
char *_uitoa(unsigned int count)
{
	char *num_str;
	unsigned int temp;
	unsigned int digits;

	temp = count;

	for (digits = 0; temp != 0; digits++)
	{
		temp /= 10;
	}

	num_str = malloc(sizeof(char) * (digits + 1));
	if (num_str == NULL)
	{
		perror("Error");
		exit(127);
	}

	num_str[digits] = '\0';
	for (--digits; count; --digits)
	{
		num_str[digits] = (count % 10) + '0';
		count /= 10;
	}

	return (num_str);
}
/**
 * _chrcmp - does the comparison of characters
 * @j: the 1st character
 * @k: the 2nd character
 * Return: it returns 0 if there is match,
 * and difference if does not match
 */

int _chrcmp(char j, char k)
{
	return (j - k);
}
