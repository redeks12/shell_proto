#include "shell.h"

/**
 * exec_p - Calls the execution of a command.
 * @arr: An array of arguments.
 * @face: A double pointer to the beginning of arr.
 * @tr: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int exec_p(char **arr, char **face, int *tr)
{
	int rem, i;
	int (*builtin)(char **arr, char **face);

	builtin = built_main(arr[0]);

	if (builtin)
	{
		rem = builtin(arr + 1, face);
		if (rem != EXIT)
			*tr = rem;
	}
	else
	{
		*tr = _run(arr, face);
		rem = *tr;
	}

	previous++;

	for (i = 0; arr[i]; i++)
		free(arr[i]);

	return (rem);
}

/**
 * exec_cl - Partitions operators from commands and calls them.
 * @chars: An array of arguments.
 * @ffc: A double pointer to the beginning of chars.
 * @pen: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int exec_cl(char **chars, char **ffc, int *pen)
{
	int in, idx;

	if (!chars[0])
		return (*pen);
	for (idx = 0; chars[idx]; idx++)
	{
		if (_strncmp(chars[idx], "||", 2) == 0)
		{
			free(chars[idx]);
			chars[idx] = NULL;
			chars = al_rep(chars);
			in = exec_p(chars, ffc, pen);
			if (*pen != 0)
			{
				chars = &chars[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; chars[idx]; idx++)
					free(chars[idx]);
				return (in);
			}
		}
		else if (_strncmp(chars[idx], "&&", 2) == 0)
		{
			free(chars[idx]);
			chars[idx] = NULL;
			chars = al_rep(chars);
			in = exec_p(chars, ffc, pen);
			if (*pen == 0)
			{
				chars = &chars[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; chars[idx]; idx++)
					free(chars[idx]);
				return (in);
			}
		}
	}
	chars = al_rep(chars);
	in = exec_p(chars, ffc, pen);
	return (in);
}

/**
 * work_cmd - Gets, calls, and runs the execution of a command.
 * @ht: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int work_cmd(int *ht)
{
	int cr = 0, idx;
	char **fl, *le = NULL, **beg;

	le = new_inp(le, ht);
	if (!le)
		return (END_OF_FILE);

	fl = tok_brk(le, " ");
	free(le);
	if (!fl)
		return (cr);
	if (see_cmd(fl) != 0)
	{
		*ht = 2;
		del_s(fl, fl);
		return (*ht);
	}
	beg = fl;

	for (idx = 0; fl[idx]; idx++)
	{
		if (_strncmp(fl[idx], ";", 1) == 0)
		{
			free(fl[idx]);
			fl[idx] = NULL;
			cr = exec_cl(fl, beg, ht);
			fl = &fl[++idx];
			idx = 0;
		}
	}
	if (fl)
		cr = exec_cl(fl, beg, ht);

	free(beg);
	return (cr);
}

/**
 * see_cmd - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @fl: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int see_cmd(char **stf)
{
	size_t i;
	char *dr, *hin;

	for (i = 0; stf[i]; i++)
	{
		dr = stf[i];
		if (dr[0] == ';' || dr[0] == '&' || dr[0] == '|')
		{
			if (i == 0 || dr[1] == ';')
				return (mk_err(&stf[i], 2));
			hin = stf[i + 1];
			if (hin && (hin[0] == ';' || hin[0] == '&' || hin[0] == '|'))
				return (mk_err(&stf[i + 1], 2));
		}
	}
	return (0);
}
