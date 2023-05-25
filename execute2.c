#include "shell.h"
/**
 * _run - Executes a iip in a child process.
 * @pulls: An array of arguments.
 * @eye: A double pointer to the beginning of pulls.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed iip.
 */
int _run(char **pulls, char **eye)
{
	pid_t pid_c;
	int cmd, fl = 0, v = 0;
	char *iip = pulls[0];

	if (iip[0] != '/' && iip[0] != '.')
	{
		fl = 1;
		iip = ret_pth(iip);
	}

	if (!iip || (access(iip, F_OK) == -1))
	{
		if (errno == EACCES)
			v = (mk_err(pulls, 126));
		else
			v = (mk_err(pulls, 127));
	}
	else
	{
		pid_c = fork();
		if (pid_c == -1)
		{
			if (fl)
				free(iip);
			perror("Error child:");
			return (1);
		}
		if (pid_c == 0)
		{
			execve(iip, pulls, toppth);
			if (errno == EACCES)
				v = (mk_err(pulls, 126));
			clear_pth();
			del_s(pulls, eye);
			_rfl(frd);
			_exit(v);
		}
		else
		{
			wait(&cmd);
			v = WEXITSTATUS(cmd);
		}
	}
	if (fl)
		free(iip);
	return (v);
}