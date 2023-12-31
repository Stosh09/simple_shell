#include "shell.h"

/**
 * getCommand - extracts commands from buffer
 * @input: buffer to tokenize
 * @delim: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */

char **getCommand(char *input, char *delim)
{
	char **token = NULL;
	size_t i = 0, buffersize = 1024;

	if (input == NULL)
		return (NULL);
	token = malloc(sizeof(char *) * buffersize);
	if (token == NULL)
	{
		perror("Error");
		return (NULL);
	}
	token[i] = _strtok(input, delim);
	while (token[i])
	{
		i++;
		if (i == buffersize)
		{
			token = _realloc(token, buffersize, 2 * buffersize);
			if (token == NULL)
			{
				perror("Error");
				return (NULL);
			}
		}
		token[i] = _strtok(NULL, delim);
	}
	return (token);
}

/**
 * getAlias- extracts new aliases from buffer
 * @input: content in buffer that is tokenized
 * @delim: delimiter used to tokenize input
 *
 * Return: pointer to an array of pointers to the tokens
 */

char **getAlias(char *input, char *delim)
{
	char **token = NULL;
	size_t i = 0, buffersize = 1024;

	if (input == NULL)
		return (NULL);
	token = malloc(sizeof(char *) * buffersize);
	if (token == NULL)
	{
		perror("Error");
		return (NULL);
	}
	token[i] = aliasStrtok(input, delim);
	while (token[i])
	{
		i++;
		if (i == buffersize)
		{
			token = _realloc(token, buffersize, 2 * buffersize);
			if (token == NULL)
			{
				perror("Error");
				return (NULL);
			}
		}
		token[i] = aliasStrtok(NULL, delim);
	}
	return (token);
}

/**
 * aliasStrtok - my custom use of strtok function
 * @str: the string to be parsed
 * @del: end of word delimeters
 * Return: pointer to start of word, or NULL
 */
char *aliasStrtok(char *str, const char *del)
{
	char *token = NULL;
	static size_t start_index, len;
	size_t comma = 0;
	static char *s;

	if (del == NULL || del[0] == '\0')
		return (str);
	start_index = (str != NULL) ? 0 : start_index;
	s = (str != NULL) ? str : s;
	len = (str != NULL) ? strlen(str) : len;
	/*get the start of the word being tokenized*/
	while (s[start_index])
	{
		if (charFound(s[start_index], del) == -1)
		{
			token = &s[start_index];
			if (charFound('\'', &s[start_index]) != -1)
				comma = start_index + charFound('\'', &s[start_index]);
			break;
		}
		start_index++;
	}
	if (s[start_index] == '\0' || s[start_index] == '#')
		return (NULL);
	if (s[start_index] == '\'' || s[start_index] == '\'')
		token = &s[++start_index];
	/*get the end of the word being tokenized*/
	while (s[start_index])
	{
		if (charFound(s[start_index], del) != -1)
			break;
		start_index++;
	}
	if (comma && start_index > comma)
		start_index = comma + charFound('\'', &s[comma + 1]) + 2;
	s[start_index] = '\0';
	start_index += (start_index < len) ? 1 : 0;
	return (token);
}

/**
 * charFound - returns index of 1st instance of a char in a string
 * @c: char to to search
 * @del: string of characters to search c in
 * Return: index of 1st instance, -1 otherwise
 */

int charFound(char c, const char *del)
{
	int x = 0;

	for (x = 0; del[x]; x++)
	{
		if (c == del[x])
			return (x);
	}
	return (-1);
}
