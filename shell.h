#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define CMD_AND         2
#define CMD_CHAIN       3
#define CMD_NORM        0
#define CMD_OR          1
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONVERT_UNSIGNED        2
#define CONVERT_LOWERCASE       1
#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;

/**
 *struct liststr -A singly linked list structure.
 *@num: An integer field.
 *@str: A string field.
 *@next: A pointer to the next node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 */
typedef struct passinfo
{
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;

	char *fname

	char *arg;
	char **argv;
	char *path;
	int readfd;
	int histcount;

	int cmd_buf_type;

	char **cmd_buf

} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - holds a builtin string and related function pointer
 * @type: The flag indicating the builtin command.
 * @func: The associated function for the builtin command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);

int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);

int bfree(void **);

#endif
