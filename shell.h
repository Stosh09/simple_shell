#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
/**
 * struct inputs - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @commands: commands to be executed
 * @status: exit status
 * @str_cmd: copy of individual commands separated by ;
 * @ops_cmd: string of commands separated by logical operators
 * @aliases: contains the alias commands
 */

typedef struct inputs
{
    char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
	char *str_cmd;
	char **ops_cmd;
	char **aliases;
} inputs_s;
/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtin_functions
{
    char *name;
    void (*f)(inputs_s *vars);
} builtin_s;

/* m_shell.c files */
void free_commands(inputs_s *vars);

/* m_environment.c files */
char **copy_env(char **env);
void free_env(char **env);
void add_key(inputs_s *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);

/* m_helper.c files */
char *_strdup(char *strtodup);
int _strcmp(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);
void print_vars(char **str);

/* m_strtok.c files */
char *_strtok(char *str, const char *delim);
unsigned int check_match(char c, const char *str);
char *_strcpy(char *dest, char *src);

/* m_get_commands.c files */
char **get_commands(char *buffer, char *delimiter);
char **get_aliases(char *buffer, char *delimeter);
int char_found(char c, const char *del);
char *alias_strtok(char *str, const char *del);

#endif /*SHELL_H*/