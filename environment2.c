#include "shell.h"
/**
 * mk_env - creates a linked list with all environment
 * variables in the extern environ variable
 * Return: main of created list
 */
env_t *mk_env(void)
{
	env_t *main;
	int i = 0;

	main = NULL;
	// for (i = 0; environ[i] != NULL; i++)
        while (environ[i] != NULL)
        {
		env_join(&main, environ[i]);
                i++;
        }
	return (main);
}
/**
 * cng_env - swith env
 * @environ: environment
 * @type: type
 * @new_char: value
 * @size: size
 */
void cng_env(env_t *environ, char *type, char *new_char, int size)
{
	char *nan;
	env_t *new;

	nan = _malloc(sizeof(char) * size);
	_memset(nan, '\0', size);
	_strcat(nan, type);
	_strcat(nan, new_char);
	// for (new = environ; new != NULL; new = new->next)
        new = environ;
        while (new != NULL)
	{
		if (_strstr(new->value, type) != NULL && new->value[0] == type[0])
		{
			new->value = nan;
			break;
		}
                new = new->next;
	}
}
/**
 * env_shw - shows vars
 * @main: main pointer to the linked list
 */

void env_shw(env_t *main)
{
	env_t *new;

	// new = main;
	// while (new != NULL)
        for (new = main; new != NULL; new = new->next)
	{
		_puts(new->value);
		_puts("\n");
		// new = new->next;
	}
}
/**
 * env_del - deletes
 * @main: pointer to the main of the linked list
 * @num: the nth node to delete
 */

void env_del(env_t **main, int num)
{
	env_t *new;
	env_t *new_s;
	int i;
	/*DEBUG: Shouldn't this just remove env by name, why by num?*/
	i = 0;
	new = *main;
	if (num == 0)
	{
		*main = (*main)->next;
		_free(new->value);
		_free(new);
	}
	else
	{
		// while (i < num - 1)
		// {
		// 	new = new->next;
		// 	i++;
		// }
                for (i = 0; i < num - 1; i++, new = new->next);
		new_s = new->next;
		new->next = new_s->next;
		_free(new_s);
	}
}
/**
 * env_join - joins another list item
 * @main: main of the linked list
 * @characters: environment
 * Return: the address of the new element, on fail, program exits
 */

env_t *env_join(env_t **main, char *characters)
{
	env_t *new;
	env_t *new_s;

	new = _malloc(sizeof(env_t));
	new->value = duplicate(characters);
	new->next = NULL;
	if (*main == NULL)
		*main = new;
	else
	{
                for (new_s = *main; new_s->next != NULL; new_s = new_s->next);
		// new_s = *main;
		// while (new_s->next != NULL)
		// 	new_s = new_s->next;
		new_s->next = new;
	}
	return (new);
}