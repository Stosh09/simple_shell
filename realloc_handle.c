#include "shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @init_size: number of elements count in initial array
 * @current_size: the alloc_size of the current array
 * Return: returns pointer to the current array
 */
char **_realloc(char **ptr, size_t init_size, size_t current_size)
{
	char **curr_ptr;
	size_t i;

	curr_ptr = malloc(sizeof(char *) * current_size);
	if (curr_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < init_size; i++)
	{
		curr_ptr[i] = ptr[i];
	}
	free(ptr);
	return (curr_ptr);
}

/**
  * _malloc - allocates memory
  * @alloc_size: memory size being created
  * Return: it returns pointer to allocated memory
  */
char *_malloc(size_t alloc_size)
{
	char *buffer = NULL;

	buffer = malloc(sizeof(char) * alloc_size);
	if (buffer == NULL)
	{
		perror("Fatal error");
		exit(1);
	}
	return (buffer);
}
