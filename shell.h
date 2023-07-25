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

/*main helper function prototypes*/
void processInput(char *input, inputs_s *vars);
char getOperator(char *command, unsigned int *index);
void checkLogicalOperator(inputs_s *vars, char *cmd_str);
void getPath(inputs_s *vars);
void myExit(inputs_s *vars);
int exeBuiltin(inputs_s *vars);

/* shell helper function prototypes*/
char **getCommand(char *buffer, char *delim);
int runCommand(inputs_s *vars, char *cmd_str);
int executeCommand(char *cmd, inputs_s *args);
void cd_command(inputs_s *vars);
void changeofDirectory(inputs_s *args, char *path_name);
void freesCommands(inputs_s *vars);

/*environment helper function prototypes*/
char **copyEnvironment(char **env);
void freeEnvironment(char **env);
void addKey(inputs_s *vars);
char **findKey(char **env, char *key);
char *addValue(char *key, char *val);
void subEnv(inputs_s *vars);
void env(inputs_s *vars);
void setEnv(inputs_s *vars);
void unSetEnv(inputs_s *vars);
int setEnv2(inputs_s *args, const char *name, const char *val, int o_write);
char *getEnv(inputs_s *vars, const	char *name);

/*string helper function prototypes*/
char *_strdup(char *strtodup);
int _strcmp(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);
void printVars(char **str);
char *_strtok(char *string, const char *delim);
char *_strcpy(char *dest, char *src);
unsigned int checkMatch(char c, const char *string);


/* memory helper function prototypes*/
char **_realloc(char **ptr, size_t init_size, size_t current_size);
char *_malloc(size_t size);

/* print helper function prototypes */
void printError(inputs_s *vars, char *message);
ssize_t _puts(char *str);
void _puts2(char *str);
void printError2(inputs_s *vars, char *message);
void printsPrompt(void);

/*character convesion helper function prototypes*/
char *_uitoa(unsigned int count);
int _atoi(char *str);
int _chrcmp(char a, char b);
int charFound(char c, const char *del);

/*Alias helper function prototypes*/
int check_name_similarity(char *an_alias, char *input);
void updateAlias(inputs_s *vars, unsigned int k);
void alias(inputs_s *vars);
char *storeAlias(char *str);
void subAlias(inputs_s *vars);
void freeAvandAlias(char **s);
char **getAlias(char *buffer, char *delim);
char *aliasStrtok(char *str, const char *del);
#endif /*SHELL_H*/
