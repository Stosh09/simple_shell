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
#include <string.h>

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
 * struct builtin_functions - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtin_functions
{
	char *name;
	void (*f)(inputs_s *vars);
} builtin_s;

/* m_shell.c files */
void freesCommands(inputs_s *vars);

/* m_environment.c files */
char **copyEnvironment(char **env);
void freeEnvironment(char **env);
void addKey(inputs_s *vars);
char **findKey(char **env, char *key);
char *addValue(char *key, char *val);

/* m_helper.c files */
char *_strdup(char *strtodup);
int _strcmp(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);
void print_vars(char **str);

/* m_strtok.c files */
char *_strtok(char *string, const char *delim);
unsigned int checkMatch(char c, const char *string);
char *_strcpy(char *dest, char *src);

/* m_get_commands.c files */
char **getCommand(char *buffer, char *delim);
char **getAlias(char *buffer, char *delim);
int charFound(char c, const char *del);
char *aliasStrtok(char *str, const char *del);

/* m_echo.c files */
void subEnv(inputs_s *vars);
void freeAvandAlias(char **s);

/* m_realloc.c files*/
char **_realloc(char **ptr, size_t init_size, size_t current_size);
char *_malloc(size_t size);

/* m_process.c file */
void processInput(char *input, inputs_s *vars);
int runCommand(inputs_s *vars, char *cmd_str);
char getOperator(char *command, unsigned int *index);
void checkLogicalOperator(inputs_s *vars, char *cmd_str);

/* m_builtins.c files */
int exeBuiltin(inputs_s *vars);
void myExit(inputs_s *vars);
void _env(inputs_s *vars);
void _setenv(inputs_s *vars);
void _unsetenv(inputs_s *vars);

/* m_path.c files */
void getPath(inputs_s *vars);
int executeCommand(char *cmd, inputs_s *args);

/* m_print.c files */
void printError(inputs_s *vars, char *message);
ssize_t _puts(char *str);
void _puts2(char *str);
void printError2(inputs_s *vars, char *message);
void printsPrompt(void);

/* m_char_conversion.c*/
char *_uitoa(unsigned int count);
int _atoi(char *str);
int _chrcmp(char a, char b);

/* m_cd.c files */
void cd_command(inputs_s *vars);
void changeofDirectory(inputs_s *args, char *path_name);
int _setenv2(inputs_s *args, const char *name, const char *val, int o_write);
char *_getenv(inputs_s *vars, const	char *name);

/* m_alias.c file */
int check_name_similarity(char *an_alias, char *input);
void updateAlias(inputs_s *vars, unsigned int k);
void alias(inputs_s *vars);
char *storeAlias(char *str);
void subAlias(inputs_s *vars);

#endif /*SHELL_H*/
