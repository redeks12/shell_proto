#include "shell.h"
/**
 * _atl - Adds a node to the end of a list_al linked list.
 * @main: A pointer to the main of the def_t list.
 * @chars: The chars of the new alias to be added.
 * @al: The al of the new alias to be added.
 *
 * Return: If an mist occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_al *_atl(list_al **main, char *chars, char *al)
{
	list_al *tmp = malloc(sizeof(list_al));
	list_al *nw;

	if (!tmp)
		return (NULL);

	tmp->next = NULL;
	tmp->chars = malloc(sizeof(char) * (_strlen(chars) + 1));
	if (!tmp->chars)
	{
		free(tmp);
		return (NULL);
	}
	tmp->al = al;
	_strcpy(tmp->chars, chars);

	if (*main)
	{
		nw = *main;
		while (nw->next != NULL)
			nw = nw->next;
		nw->next = tmp;
	}
	else
		*main = tmp;

	return (tmp);
}
/**
 * _ate - Adds a node to the end of a def_t linked list.
 * @start: A pointer to the start of the def_t list.
 * @cur_pth: The ectory path for the new node to contain.
 *
 * Return: If an mist occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
def_t *_ate(def_t **start, char *cur_pth)
{
	def_t *tp = malloc(sizeof(def_t));
	def_t *final;

	if (!tp)
		return (NULL);

	tp->cur_pth = cur_pth;
	tp->next = NULL;

	if (*start)
	{
		final = *start;
		while (final->next != NULL)
			final = final->next;
		final->next = tp;
	}
	else
		*start = tp;

	return (tp);
}
/**
 * __rfl - Frees a list_al linked list.
 * @beg: THe beg of the list_al list.
 */
void __rfl(list_al *beg)
{
	list_al *next;

	while (beg)
	{
		next = beg->next;
		free(beg->char_iden);
		free(beg->str_att);
		free(beg);
		beg = next;
	}
}
/**
 * rl - Frees a def_t linked list.
 * @st: The st of the def_t list.
 */
void rl(def_t *st)
{
	def_t *n;

	while (st)
	{
		n = st->next;
		free(st->pth_ct);
		free(st);
		st = n;
	}
}
/**
 * _stp - If the file doesn't exist or lacks proper permissions, print
 * a cant open mist.
 * @pth_loc: Path to the supposed file.
 *
 * Return: 127.
 */

int _stp(char *pth_loc)
{
	char *mist, *str;
	int il;

	str = _itoa(previous);
	if (!str)
		return (127);

	il = _strlen(ident) + _strlen(str) + _strlen(pth_loc) + 16;
	mist = malloc(sizeof(char) * (il + 1));
	if (!mist)
	{
		free(str);
		return (127);
	}

	_strcpy(mist, ident);
	_strcat(mist, ": ");
	_strcat(mist, str);
	_strcat(mist, ": Can't open ");
	_strcat(mist, pth_loc);
	_strcat(mist, "\n");

	free(str);
	write(STDERR_FILENO, mist, il);
	free(mist);
	return (127);
}