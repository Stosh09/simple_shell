#include <stdio.h>

/**
 * main -simple program passing betty checks
 * @argc: argument count
 * @argv: arguments
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
	int i = 0;
	(void)argc;

	for (; argv[i]; i++)
	{
		printf("Argv[%d] = %s\n", i, argv[i]);
	}
	return (0);
}
