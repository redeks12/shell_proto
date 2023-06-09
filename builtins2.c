#include "shell.h"
/**
 * unsetenv_sh - Deletes an environmental variable from the PATH.
 * @arr: An array of arguments passed to the shell.
 * @ace: A double pointer to the beginning of arr.
 * Description: arr[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unsetenv_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	char **vr, **loc_n;
	size_t sz;
	int i, in;

	if (!arr[0])
		return (mk_err(arr, -1));
	vr = env_brn(arr[0]);
	if (!vr)
		return (0);

	for (sz = 0; toppth[sz]; sz++);

	loc_n = malloc(sizeof(char *) * sz);
	if (!loc_n)
		return (mk_err(arr, -1));

	for (i = 0, in = 0; toppth[i]; i++)
	{
		if (*vr == toppth[i])
		{
			free(*vr);
			continue;
		}
		loc_n[in] = toppth[i];
		in++;
	}
	free(toppth);
	toppth = loc_n;
	toppth[sz - 1] = NULL;

	return (0);
}
/**
 * env_sh - Prints the current environment.
 * @arr: An array of arguments passed to the shell.
 * @ace: A double pointer to the beginning of arr.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int env_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	int idx;
	char st = '\n';

	if (!toppth)
		return (-1);

	for (idx = 0; toppth[idx]; idx++)
	{
		print_hlps(toppth[idx]);
		write(STDOUT_FILENO, &st, 1);
	}

	(void)arr;
	return (0);
}
/**
 * setenv_sh - Changes or adds an environmental variable to the PATH.
 * @arr: An array of arguments passed to the shell.
 * @ace: A double pointer to the beginning of arr.
 * Description: arr[1] is the name of the new or existing PATH variable.
 *              arr[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int setenv_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	char **vr = NULL, **loc_n, *vl_n;
	size_t size;
	int i;

	if (!arr[0] || !arr[1])
		return (mk_err(arr, -1));

	vl_n = malloc(_strlen(arr[0]) + 1 + _strlen(arr[1]) + 1);
	if (!vl_n)
		return (mk_err(arr, -1));
	_strcpy(vl_n, arr[0]);
	_strcat(vl_n, "=");
	_strcat(vl_n, arr[1]);

	vr = env_brn(arr[0]);
	if (vr)
	{
		free(*vr);
		*vr = vl_n;
		return (0);
	}
	for (size = 0; toppth[size]; size++)
		;

	loc_n = malloc(sizeof(char *) * (size + 2));
	if (!loc_n)
	{
		free(vl_n);
		return (mk_err(arr, -1));
	}

	for (i = 0; toppth[i]; i++)
		loc_n[i] = toppth[i];

	free(toppth);
	toppth = loc_n;
	toppth[i] = vl_n;
	toppth[i + 1] = NULL;

	return (0);
}