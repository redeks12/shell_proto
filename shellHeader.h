#ifndef _SHELLHEADER_H
#define _SHELLHEADER_H

/*lIBRARY*/
#include <stdio.h>/*getline,perror*/
#include <string.h>/*strtok*/
#include <stdlib.h>/*malloc,exit,getline,NULL*/
#include <stdarg.h>/*va_list*/
#include <sys/types.h>/*wait,closedir,opendir,stat*/
#include <sys/wait.h>/*wait*/
#include <sys/stat.h>/*stat*/
#include <limits.h>/*INT_MIN*/
#include <dirent.h>/*closedir,opendir,readdir*/
/*execve,fork,wait,close,access,getcwd,chdir,read,write,exit,stat*/
#include <unistd.h>/*execve*/
#include <signal.h>/*signal*/
#include <fcntl.h> /*read mode*/

/**
* struct printf_functions - struct to match type with printer funcitons
* @type: input to determine type of printf function
* @printer: specific printf function
* Description: the the correct copy function to use
**/
typedef struct printf_functions
{
	char type;
	int (*printer)();
} pstruct;

/*COSTUMFUNC*/
char *_strtok(char *str, const char *delim);
int cmdExec(char **tokens, char **env);
int specialExec(char **tokens, char **env, int controller, char *home);

/*SPECIALFUNC*/
int _echo(char **tokens, char **env);
int _cd(char **tokens, char **env, char *home);
int _env(char **env);
int _cp(char **tokens);

/*HISTORY*/
int history(char *dir);
int history_file(char *text_content, char *dir);

/*PRINTFFUNC*/
int _putchar(char c);
int print_percent(void);
int print_char(va_list arg);
int print_string(va_list arg);
int print_number(va_list arg);

/*STRINGFUNC*/
int _printf(const char *format, ...);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strstr(char *haystack, char *needle);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int i, int n);

/*HELPERFUNC*/
char **tokenize(char *string, const char *delimiter);
char *_getenv(char *name, char **environ);
int cmdchk(char **token, char **environ);
char *cutspecial(char *string);
char *gethome(char **env);

/*MEMORYFUNC*/
char *_strdup(char *str);
char *_addpath(char *first, char *second);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **ptofree(char *p, int n);

/*SIGNAL*/
void signal_handler(int s);

#endif /*_SHELLHEADER_H*/
