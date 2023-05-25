#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **top_pth;
/* Global progrident*/
char *ident;
/* Global history counter */
int previous;

/**
 * struct def_t - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct def_t.
 */
typedef struct def_t
{
	char *pth_ct;
	struct def_t *next;
} def_t;

/**
 * struct built - A new struct type defining builtin commands.
 ident Tidentof the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct built_t
{
	char *name;
	int (*f)(char **argv, char **front);
} built_t;

/**
 * struct list_al - A new struct defining aliases.
 ident Tidentof the alias.
 * @str_att: The str_att of the alias.
 * @next: A pointer to another struct list_al.
 */
typedef struct list_al
{
	char *str_att;
	char *char_iden;
	struct list_al *next;
} list_al;

/* Global aliases linked list */
list_al *frd;
char **al_rep(char **arr);
void shw_al(list_al *list);
void prep_al(char *av, char *vl);
int alias_sh(char **arr, char __attribute__((__unused__)) **ace);

int (*built_main(char *command))(char **args, char **front);
int cd_sh(char **arr, char __attribute__((__unused__)) **ace);
int sh_sh(char **arr, char __attribute__((__unused__)) **ace);
int exit_sh(char **arr, char **ace);
int env_sh(char **arr, char __attribute__((__unused__)) **ace);
int un(char **arr, char __attribute__((__unused__)) **ace);
int setenv_sh(char **arr, char __attribute__((__unused__)) **ace);
int unsetenv_sh(char **arr, char __attribute__((__unused__)) **ace);

void clear_pth(void);
char **env_brn(const char *var);
char **pth_cp(void);

char *pth_err(char **arr);
char *exit_err(char **arr);
char *main_err(char **arr);
char *cd_err(char **strs);
char *type_err(char **arr);
char *unq_err(char **mss);
char *unq2_err(char **dsa);

int dig_ct(int dig);
int mk_err(char **conts, int trash);
char *_itoa(int num);


void *_realloc(void *pt, unsigned int pre_sp, unsigned int post_cp);
void buf_hand(char **pt, size_t *n, char *space, size_t b);

ssize_t _getline(char **llp, size_t *n, FILE *inr);
void del_s(char **s_ts, char **in);
char *ret_env(char *st, int l);
char *get_pid(void);

void c_cng(char **ar_r, int *inl);
void rework(char *lnt, ssize_t *wl);
void p_input(char **ms, ssize_t see);
ssize_t new_sz(char *writ_e);
int exec_p(char **arr, char **face, int *tr);
char *new_inp(char *ll, int *et);
int exec_cl(char **chars, char **ffc, int *pen);
int work_cmd(int *ht);
int see_cmd(char **stf);

list_al *_atl(list_al **main, char *chars, char *al);

int fc_p(char *locs, int *rt_v);
void sig_handler(int sig);
char *add_to_loc(char *cur_dir);
def_t *cur_loc(char *loc);
char *ret_pth(char *inp);


void rl(def_t *st);
void _rfl(list_al *beg);
def_t *_ate(def_t **start, char *cur_pth);
list_al *_atl(list_al **main, char *chars, char *al);

int _run(char **pulls, char **eye);
int _stp(char *pth_loc);

int num_strs(char *chars, char *sym);
int sz_strs(char *characters, char *sig);


int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


void sh_all(void);
void sh_alias(void);
void sh_cd(void);
void sh_exit(void);
void sh_help(void);
void sh_env(void);
void sh_setenv(void);
void sh_unsetenv(void);
void print_hlps(char *hlp);
char **tok_brk(char *lk, char *emb);

#endif 
