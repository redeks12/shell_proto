#include "shell.h"
/**
 * _pth - copies the $PATH into the string locate
 * @locate: string to copy the $PATH into
 * @environ: environemental variable environ
 * Return: 0 if successly found PATH variable and 1 if PATH
 * not found
 */
int _pth(char *path, env_t *list)
{
	env_t *temp;

	temp = list;
	for (; temp->next != NULL; temp = temp->next)
	{
		if (matchStrings(temp->value, "PATH=") != 0)
		{
			_strcpy(path, temp->value);
			return (0);
		}
	}
	return (1);
}
/**
 * mk_pth - checks th input
 * @input: input by user
 * @find: array
 * Return: 0 if found and -1 if not;
 */
int mk_pth(char *cmd, char **search_path)
{
	int i, fd;

	for (i = 0; search_path[i] != NULL; i++)
	{
		_strncat(search_path[i], cmd, _strlen(cmd));
		fd = open(search_path[i], O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			_strcpy(cmd, search_path[i]);
			return (0);
		}
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}
