#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFSIZE 600
#define FREE_ADDRESSES ((void *)3)
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof((ARRAY)[0]))
/**
 * struct buffer - structure for controlling buffer
 * @buf: pointer the buffer
 * @size: size of the buffer
 * @bp: current point in buffer to check for multiple command passes
 */
typedef struct buffer
{
	char *buf;
	unsigned int size;
	unsigned int bp;
} buffer;
/**
 * struct builtin - lookup structure for builtin functions
 * @name: string name user types to call function
 * @func: function pointer to that function
 */
typedef struct builtin
{
	char *name;
	int (*func)();
} builtin;
/**
 * struct addr_list - List for saving addresses for freeing on exit
 * @address: an address of any type
 * @next: the next node in the list
 */
typedef struct addr_list
{
	void *address;
	struct addr_list *next;
} addr_list;

/**
 * struct hist_s - history linked list for saving commands
 * @cmd: command given as input
 * @next: pointer to next node on list
 */

typedef struct hist_s
{
	char *cmd;
	struct hist_s *next;
} hist_t;

extern char **environ;
/**
 * struct env_s - structure for each environmental variable
 * @value: value of the environmental variable
 * @next: next environmental variable
 */

typedef struct env_s
{
	char *value;
	struct env_s *next;
} env_t;
/**
 * struct alias - structure for holding aliases
 * @key: key to search for when matching
 * @value: value to replace matched keys
 * @next: next node in the list
 */
typedef struct alias
{
	char *key;
	char *value;
	struct alias *next;
} alias;
int more_cmds(buffer *b, int retrn_value);
void trim_cmd(buffer *b);
void print_int(int num);
void _puts(char *str);
int _putchar(char c);

int aliase(buffer *b, env_t *env_p);

void _realloc(buffer *str);
void *_malloc(size_t ptr_size);

void rem_str(buffer *str, int n);
void add_str(buffer *b, char *str, int position);
void _setfree(void *addr);
void _free(void *address);
void add_node(addr_list *list, void *newnode);
void free_list(addr_list *list);
int rem_node(addr_list *list, void *addr);

int read_file(buffer *b, env_t *envp);
int get_line(buffer *b, int fd, env_t *envp);

char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strstr(char *haystack, char *needle);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

char *_strchr(char *s, char c);
int _strlen(char *s);
int _atoi(char *s);
int matchStrings(const char *string1, const char *string2);
char *duplicate(char *str);

int strictStringMatch(const char *string1, const char *string2);
int findSubstringIndex(const char *text, const char *substring);
int findFirstCharacterIndex(const char *string, const char *characters);
int is_digit(int c);
int is_alpha(int c);

int matchStringsAndDelim(char *string1, char *string2, char *delimiter);
int characterMatch(char c, const char *needles);
int compareStrings(char *string1, char *string2);

void print_error(char *err);

char *_del_nm(env_t *environ, char *tb_rm, int size);
char *_rem_pth(char **arr, env_t *environ, char *pth, int size);
char *_ret_val(env_t *environ, char *key);
char *new_pth(char **pth, char *file, char *character, env_t *environ);
int get_content(env_t *environ, char **vari);

char **arr_init(env_t *environ);

void show_hist(hist_t *main);
hist_t *new_entry(hist_t *first, char *input);
void new_hist(hist_t *new, env_t *envp);
int get_content(env_t *environ, char **vari);
void add_to_list(hist_t *list, char *input);
int add_to_file(env_t *environ, hist_t *list);
void _checker(char *input, env_t *environ, char type);


int help_alias(void);
int help_cd(void);
int help_env(void);
int help_exit(void);
int help_help(void);
int help_hist(void);
int help_setenv(void);
int help_unsetenv(void);
int a_print(alias *list, char **arr);
int a_operations(alias *list, char **arr);
int a_complete(alias *prop);
char *a_find(alias *prop, char *arr);

char *func_cd(char **new_dir, env_t *environ, int size);
int cd_shell(char **arr, env_t *environ, int size);
int env_shell(char **arr, env_t *environ);
int help_shell(char **arr);
int exit_shell(char **arr, env_t *environ, int size);
int hist_shell(char **arr, env_t *environ, int type);
int setenv_shell(char **arr, env_t *environ, int size);
int unsetenv_shell(char **arr, env_t *environ);
int _a_shell(char **arr, env_t *environ, int type);


// char* intToString(int num, int mode);
char *_itoa(int num, int mode);

env_t *mk_env(void);
void cng_env(env_t *environ, char *type, char *new_char, int size);
void env_del(env_t **main, int num);
void env_shw(env_t *main);
env_t *env_join(env_t **main, char *characters);

int _pth(char *locate, env_t *environ);
int mk_pth(char *input, char **find);
char **break_pth(char **find, char *locate, int size);
int execute2(char **arr, env_t *environ, int size_s);
int exec_part(char **arr, env_t *environ, int input_s);
int main_execute(char *input, char **array, env_t *environ);
void _sig(int s);

void end_inp(char *cont);
int input_finish(char c);
int is_w(char c);

void break_buffer(buffer *cont, char ***array);
void size_x(char *cont, char ***arr);
char *find_elem(char *array, int index);
char *cur_pid(void);
void _to_buff(buffer *base, env_t *environ, int rt);



int execute_func(char *cmd, char **args, env_t *envp);
int run_execute(char **arg_list, env_t *env_p, int cmd_size);
#endif