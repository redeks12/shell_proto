#include "shell.h"
/**
 * aliase - wrapper function for checking and replacing aliases
 * @b: buff_t structure
 * @env_p: enviornment struct to pass along
 * Return: 1 on alias replacement, 0 if no replacement
 */
int aliase(buff_t *b, env_t *env_p)
{
	static int stop = 2;
	int i, size;
	char *str, *strcpy;

	size = 0, i = 0;
	while (b->b_s[b->bl_s] == ' ' || b->b_s[b->bl_s] == '\t')
		b->bl_s++;
	while (!is_w(b->b_s[b->bl_s + size]))
		size++;

	str = _malloc(sizeof(char) * (size + 1));
	strcpy = str;

	while (i < size)
		str[i] = b->b_s[b->bl_s + i], i++;
	str[i] = '\0';

	_a_shell(&str, env_p, 0);

	if (str)
	{
		rem_str(b, b->bl_s);
		add_str(b, str, b->bl_s);
		_free(strcpy);
		if (stop++ == 10)
		{
			stop = 0;
			return (0);
		}
		return (1);
	}
	else
		_free(str);
	stop = 0;
	return (0);
}
/**
 * a_operations - operates and configure for the alias
 * @list: alias
 * @arr: args
 *
 * Return: Always 0;
 */
int a_operations(alias *list, char **arr)
{
	alias *item;
	char *character, *val;
	int i, j;

	val = _strstr(arr[1], "=");
	if (val != NULL)
		val++;

	val = duplicate(val);

	// for (i = 0; arr[1][i] != '='; i++);
	i = 0;
	j = 0;
	while (arr[1][i] != '=')
		i++;
	character = _malloc(sizeof(char) * (i + 1));
	// for (j = 0; j < i; j++)
	while (j < i)
	{
		character[j] = arr[1][j];
		j++;
	}
	character[j] = '\0';

	while (list->next != NULL && !strictStringMatch(character, list->key))
		list = list->next;
	if (list->key == NULL || strictStringMatch(character, list->key))
	{
		list->key = character;
		list->value = val;
	}
	else if (list->next == NULL)
	{
		item = _malloc(sizeof(alias));
		item->next = NULL;
		item->value = val;
		item->key = character;
		list->next = item;
	}
	else
		list->value = val;
	return (0);
}
/**
 * a_print - print aliase
 * @list: linked list
 * @arr: args
 *
 * Return: 1 if no match needed, 2 on alias not found, 0 on success
 */
int a_print(alias *list, char **arr)
{
	char *string;

	string = _strstr(arr[1], "=");
	if (string != NULL)
		return (EXIT_FAILURE);

	string = a_find(list, arr[1]);
	if (string == NULL)
	{
		_puts("alias not found\n");
		return (2);
	}
	else
	{
		_puts("alias ");
		_puts(arr[1]);
		_puts("='");
		_puts(string);
		_puts("'\n");
	}
	return (EXIT_SUCCESS);
}
/**
 * a_complete - show all aliases
 * @prop: alias linked list
 *
 * Return: Always 0
 */
int a_complete(alias *prop)
{
	for ( ;prop != NULL && prop->key != NULL; prop = prop->next)
	// while (prop != NULL && prop->key != NULL)
	{
		_puts("alias ");
		_puts(prop->key);
		_puts("='");
		_puts(prop->value);
		_puts("'\n");
		// prop = prop->next;
	}
	return (EXIT_SUCCESS);
}
/**
 * a_find - find alias values matching their key
 * @prop: alias linked list
 * @arr: alias to search for
 *
 * Return: matching alias value, or NULL
 */
char *a_find(alias *prop, char *arr)
{
	for (; prop != NULL && prop->key != NULL; prop = prop->next)
	// while (prop != NULL && prop->key != NULL)
	{
		if (strictStringMatch(arr, prop->key))
			return (prop->value);
		// prop = prop->next;
	}
	return (NULL);
}