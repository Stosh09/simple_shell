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
char **getCommand(char *buffer, char *delim);
char **getAlias(char *buffer, char *delim);
int char_found(char c, const char *del);
char *alias_strtok(char *str, const char *del);

/* m_echo.c files */
void sub_env(inputs_s *vars);
void free_av_and_alias(char **s);

/* m_realloc.c files*/
char **_realloc(char **ptr, size_t old_size, size_t new_size);
char *_malloc(size_t size);

/* m_process.c file */
void processInput(char *input, inputs_s *vars);
int run_command(inputs_s *vars, char *cmd_str);
char get_operator(char *command, unsigned int *index);
void check_logical_ops(inputs_s *vars, char *cmd_str);

/* m_builtins.c files */
int exe_builtin(inputs_s *vars);
void my_exit(inputs_s *vars);
void _env(inputs_s *vars);
void _setenv(inputs_s *vars);
void _unsetenv(inputs_s *vars);

/* m_path.c files */
void get_path(inputs_s *vars);
int execute_cmd(char *command, inputs_s *args);

/* m_print.c files */
void print_error(inputs_s *vars, char *msg);
ssize_t _puts(char *str);
void _puts2(char *str);
void print_error2(inputs_s *vars, char *msg);
void printsPrompt(void);

/* m_char_conversion.c*/
char *_uitoa(unsigned int count);
int _atoi(char *str);
int _chrcmp(char a, char b);

/* m_cd.c files */
void _cd(inputs_s *vars);
void change_dir(inputs_s *args, char *pathname);
int _setenv2(inputs_s *args, const char *name, const char *val, int o_write);
char *_getenv(inputs_s *vars, const	char *name);

/* m_alias.c file */
int check_name_match(char *an_alias, char *input);
void update_alias(inputs_s *vars, unsigned int k);
void _alias(inputs_s *vars);
char *store_alias(char *str);
void sub_alias(inputs_s *vars);

#endif /*SHELL_H*/
