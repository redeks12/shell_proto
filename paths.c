#include "shell.h"
/**
 * ret_pth - Locates a inp in the PATH.
 * @inp: The inp to locate.
 *
 * Return: If an error occurs or the inp cannot be located - NULL.
 *         Otherwise - the full pathname of the inp.
 */
char *ret_pth(char *inp)
{
	char **pth, *n;
	def_t *locs, *fst;
	struct stat a;

	pth = env_brn("PATH");
	if (!pth || !(*pth))
		return (NULL);

	locs = cur_loc(*pth + 5);
	fst = locs;

	while (locs)
	{
		n = malloc(_strlen(locs->pth_ct) + _strlen(inp) + 2);
		if (!n)
			return (NULL);

		_strcpy(n, locs->pth_ct);
		_strcat(n, "/");
		_strcat(n, inp);

		if (stat(n, &a) == 0)
		{
			rl(fst);
			return (n);
		}

		locs = locs->next;
		free(n);
	}

	rl(fst);

	return (NULL);
}

/**
 * cur_loc - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @loc: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
def_t *cur_loc(char *loc)
{
	int st;
	char **pth, *chars;
	def_t *first = NULL;

	chars = add_to_loc(loc);
	if (!chars)
		return (NULL);
	pth = tok_brk(chars, ":");
	free(chars);
	if (!pth)
		return (NULL);

	for (st = 0; pth[st]; st++)
	{
		if (_ate(&first, pth[st]) == NULL)
		{
			rl(first);
			free(pth);
			return (NULL);
		}
	}

	free(pth);

	return (first);
}
/**
 * num_strs - Counts the number of delimited
 *                words contained within a string.
 * @chars: The string to be searched.
 * @sym: The delimiter character.
 *
 * Return: The number of words contained within chars.
 */
int num_strs(char *chars, char *sym)
{
	int i, brks = 0, ln = 0;

	for (i = 0; *(chars + i); i++)
		ln++;

	for (i = 0; i < ln; i++)
	{
		if (*(chars + i) != *sym)
		{
			brks++;
			i += sz_strs(chars + i, sym);
		}
	}

	return (brks);
}
/**
 * sz_strs - Locates the delimiter i marking the end
 *             of the first token contained within a string.
 * @characters: The string to be searched.
 * @sig: The delimiter character.
 *
 * Return: The delimiter i marking the end of
 *         the intitial token pointed to be characters.
 */
int sz_strs(char *characters, char *sig)
{
	int i = 0, j = 0;

	while (*(characters + i) && *(characters + i) != *sig)
	{
		j++;
		i++;
	}

	return (j);
}