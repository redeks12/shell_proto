#include "shell.h"
/**
 * _pth - copies the $PATH into the string locate
 * @locate: string to copy the $PATH into
 * @environ: environemental variable environ
 * Return: 0 if successly found PATH variable and 1 if PATH
 * not found
 */
int _pth(char *locate, list_e *environ)
{
	list_e *new;

	new = environ;

        while (new->next != NULL)
	{
		if (matchStrings(new->hold, "PATH=") != 0)
		{
			_strcpy(locate, new->hold);
			return (EXIT_SUCCESS);
		}
                new = new->next;
	}
	return (EXIT_FAILURE);
}
/**
 * mk_pth - checks th input
 * @input: input by user
 * @find: array
 * Return: 0 if found and -1 if not;
 */
int mk_pth(char *input, char **find)
{
	int i, file, bl;

        i = 0;
	bl = ARRAY_SIZE(find);

        while (find[i] != NULL)
	{
		_strncat(find[i], input, _strlen(input));
		file = open(find[i], O_RDONLY);
		if (file > 0)
		{
			close(file);
			_strcpy(input, find[i]);
			return (0);
		}
                i++;
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}