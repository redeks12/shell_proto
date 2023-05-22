#include "shell.h"
/**
 * execute2 - execute builtin functions
 * @arr: array
 * @environ: enviorn list
 * @size_s: size
 * Return: 0 on found builtin, 1 on found nothing, 2 on builtin error
 */
int execute2(char **arr, env_t *environ, int size_s)
{
	int i, sz, pow;
	builtin table[] = {
	{"exit", exit_shell},     {"env", env_shell},
	{"setenv", setenv_shell}, {"unsetenv", unsetenv_shell},
	{"cd", cd_shell},         {"history", hist_shell},
	{"help", help_shell},     {"alias", _a_shell}
	};

	sz = ARRAY_SIZE(table);
        i = 0;
	// for (i = 0; i < sz; i++)
        while(i < sz)
	{
		if (strictStringMatch(arr[0], table[i].name))
		{
			pow = table[i].func(arr, environ, size_s);
			return (pow);
		}
                i++;
	}
	return (EXIT_FAILURE);
}
/**
 * main_execute - function that runs the execve system call.
 * @input: input
 * @array: array
 * @environ: environement
 * Return: 0 on success and 2 on failure
 */

int execute_func(char *cmd, char **args, env_t *envp)
{
	pid_t pid;
	int status, i;
	char **array;


	pid = fork();
	if (pid == 0)
	{
		array = list_to_array(envp);
		i = execve(cmd, args, array);
		if (i < 0)
		{
			_puts("Error: command not found\n");
			return (2);
			_exit(1);
		}
	}
	else
	{

		pid = wait(&status);
		if (WIFEXITED(status))
			return (status);
	}
	return (2);
}

/**
 * exec_part - execute
 * @arr: array
 * @environ: environment
 * @input_s: size
 * Return: st if success or 127 if failure.
 */
int run_execute(char **arg_list, env_t *env_p, int cmd_size)
{
	char *cmd, *path;
	char **search_path;
	int status, n, m;

	search_path = NULL;
	n = 0;
	cmd = _malloc(sizeof(char) * cmd_size);
	path = _malloc(sizeof(char) * cmd_size);
	_strcpy(cmd, arg_list[0]);
	if (_strchr(cmd, '/') != NULL)
		status = execute_func(cmd, arg_list, env_p);
	else
	{
		m = _pth(path, env_p);
		if (m != 0)
		{
			_puts("Error: Cannot find PATH variable\n");
			return (127);
		}
		search_path = break_pth(search_path, path, cmd_size);
		n = mk_pth(cmd, search_path);
		if (n == 0)
			status = execute_func(cmd, arg_list, env_p);
	}
	if (n == 0)
		return (status);
	else
		return (127);
}
/**
 * _sig - handles the ctrl-c signal
 * @s: signal received
 */

void _sig(int s)
{
	(void) s;
	_puts("\n");
	_puts("$ ");
}