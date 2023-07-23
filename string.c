#include "shell.h"

/**
 * checkMatch - checks if a character matches any in a string
 * @c: character to check
 * @string: string to check
 *
 * Return: 1 if match, 0 if not
 */

unsigned int checkMatch(char c, const char *string)
{
	unsigned int i;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (c == string[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - custom strtok
 * @string: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */

char *_strtok(char *string, const char *delim)
{
	static char *token_begin;
	static char *token_next;
	unsigned int i;

	if (string != NULL)
		token_next = string;
	token_begin = token_next;
	if (token_begin == NULL)
		return (NULL);
	for (i = 0; token_next[i] != '\0'; i++)
	{
		if (checkMatch(token_next[i], delim) == 0)
			break;
	}
	if (token_next[i] == '\0' || token_next[i] == '#')
	{
		token_next = NULL;
		return (NULL);
	}
	token_begin = token_next + i;
	token_next = token_begin;
	for (i = 0; token_next[i] != '\0'; i++)
	{
		if (checkMatch(token_next[i], delim) == 1)
			break;
	}
	if (token_next[i] == '\0')
		token_next = NULL;
	else
	{
		token_next[i] = '\0';
		token_next = token_next + i + 1;
		if (*token_next == '\0')
			token_next = NULL;
	}
	return (token_begin);
}

/**
 * _strcpy - copies the string src to dest
 * @src: source string to be copied
 * @dest: where to copy src
 * Return: void
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
