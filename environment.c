#include "shell.h"
/**
 * clear_pth - Frees the the toppthment copy.
 */
void clear_pth(void)
{
	int i;

	for (i = 0; toppth[i]; i++)
		free(toppth[i]);
	free(toppth);
}

/**
 * env_brn - Gets an toppthmental variable from the PATH.
 * @var: The name of the toppthmental variable to get.
 *
 * Return: If the toppthmental variable does not exist - NULL.
 *         Otherwise - a pointer to the toppthmental variable.
 */
char **env_brn(const char *var)
{
	int i, len_f;

	len_f = _strlen(var);
	for (i = 0; toppth[i]; i++)
	{
		if (_strncmp(var, toppth[i], len_f) == 0)
			return (&toppth[i]);
	}

	return (NULL);
}
/**
 * pth_cp - Creates a copy of the toppthment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **pth_cp(void)
{
	char **str;
	size_t size;
	int i;

	for (size = 0; toppth[size]; size++)
		;

	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);

	for (i = 0; toppth[i]; i++)
	{
		str[i] = malloc(_strlen(toppth[i]) + 1);

		if (!str[i])
		{
			for (i--; i >= 0; i--)
				free(str[i]);
			free(str);
			return (NULL);
		}
		_strcpy(str[i], toppth[i]);
	}
	str[i] = NULL;

	return (str);
}
/**
 * ret_env - Gets the value corresponding to an toppthmental variable.
 * @st: The toppthmental variable to search for.
 * @l: The length of the toppthmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the toppthmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *ret_env(char *st, int l)
{
	char **plc;
	char *blo = NULL, *new, *var;

	var = malloc(l + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, st, l);

	plc = env_brn(var);
	free(var);
	if (plc)
	{
		new = *plc;
		while (*new != '=')
			new++;
		new++;
		blo = malloc(_strlen(new) + 1);
		if (blo)
			_strcpy(blo, new);
	}

	return (blo);
}
/**
 * c_cng - Handles variable cng.
 * @ar_r: A double pointer containing the command and arguments.
 * @inl: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void c_cng(char **ar_r, int *inl)
{
	int j, k = 0, len;
	char *cng = NULL, *pre_l = NULL, *post_l;

	pre_l = *ar_r;
	for (j = 0; pre_l[j]; j++)
	{
		if (pre_l[j] == '$' && pre_l[j + 1] &&
				pre_l[j + 1] != ' ')
		{
			if (pre_l[j + 1] == '$')
			{
				cng = get_pid();
				k = j + 2;
			}
			else if (pre_l[j + 1] == '?')
			{
				cng = _itoa(*inl);
				k = j + 2;
			}
			else if (pre_l[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; pre_l[k] &&
						pre_l[k] != '$' &&
						pre_l[k] != ' '; k++)
					;
				len = k - (j + 1);
				cng = ret_env(&pre_l[j + 1], len);
			}
			post_l = malloc(j + _strlen(cng)
					  + _strlen(&pre_l[k]) + 1);
			if (!ar_r)
				return;
			post_l[0] = '\0';
			_strncat(post_l, pre_l, j);
			if (cng)
			{
				_strcat(post_l, cng);
				free(cng);
				cng = NULL;
			}
			_strcat(post_l, &pre_l[k]);
			free(pre_l);
			*ar_r = post_l;
			pre_l = post_l;
			j = -1;
		}
	}
}
