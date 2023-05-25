#include "shell.h"

/**
 * al_rep - function
 * @arr: function
 *
 * Return: function
 */
char **al_rep(char **arr)
{
	list_al *new;
	int i;
	char *vl;

	if (_strcmp(arr[0], "alias") == 0)
		return (arr);
	for (i = 0; arr[i]; i++)
	{
		new = frd;
		while (new)
		{
			if (_strcmp(arr[i], new->char_iden) == 0)
			{
				vl = malloc(sizeof(char) * (_strlen(new->str_att) + 1));
				if (!vl)
				{
					del_s(arr, arr);
					return (NULL);
				}
				_strcpy(vl, new->str_att);
				free(arr[i]);
				arr[i] = vl;
				i--;
				break;
			}
			new = new->next;
		}
	}

	return (arr);
}
/**
 * shw_al - function
 * @list: function.
 */
void shw_al(list_al *list)
{
	char *str;
	int hin = _strlen(list->char_iden) + _strlen(list->str_att) + 4;

	str = malloc(sizeof(char) * (hin + 1));
	if (!str)
		return;
	_strcpy(str, list->char_iden);
	_strcat(str, "='");
	_strcat(str, list->str_att);
	_strcat(str, "'\n");

	write(STDOUT_FILENO, str, hin);
	free(str);
}
/**
 * prep_al - function
 * @av: function
 * @vl: function
 */
void prep_al(char *av, char *vl)
{
	list_al *new = frd;
	int hin, j, k;
	char *str;

	*vl = '\0';
	vl++;
	hin = _strlen(vl) - _strspn(vl, "'\"");
	str = malloc(sizeof(char) * (hin + 1));
	if (!str)
		return;
	for (j = 0, k = 0; vl[j]; j++)
	{
		if (vl[j] != '\'' && vl[j] != '"')
			str[k++] = vl[j];
	}
	str[k] = '\0';
	while (new)
	{
		if (_strcmp(av, new->char_iden) == 0)
		{
			free(new->str_att);
			new->str_att = str;
			break;
		}
		new = new->next;
	}
	if (!new)
		_atl(&frd, av, str);
}
/**
 * alias_sh - function
 * @arr: function
 * @ace: function
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alias_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	list_al *new = frd;
	int i, tr = 0;
	char *str;

	if (!arr[0])
	{
		while (new)
		{
			shw_al(new);
			new = new->next;
		}
		return (tr);
	}
	for (i = 0; arr[i]; i++)
	{
		new = frd;
		str = _strchr(arr[i], '=');
		if (!str)
		{
			while (new)
			{
				if (_strcmp(arr[i], new->char_iden) == 0)
				{
					shw_al(new);
					break;
				}
				new = new->next;
			}
			if (!new)
				tr = mk_err(arr + i, 1);
		}
		else
			prep_al(arr[i], str);
	}
	return (tr);
}