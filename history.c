#include "shell.h"
/**
 * get_content - reads the bfiel into a buffer
 * @environ: environement
 * @vari: buffer
 * Return: 1 if success and 0 if failed
 */

int get_content(env_t *environ, char **vari)
{
	static int size = BUFSIZE;
	char *pth, *buff;
	int num, n, file;

	pth = _del_nm(environ, "HOME", BUFSIZE);
	if (pth == NULL)
	{
		_puts("Error: Cannot find Home\n");
		_puts("Cannot find history file\n");
		return (EXIT_FAILURE);
	}
	_strcat(pth, "/.simple_shell_history");
	file = open(pth, O_RDWR | 0600);
	if (file > 0)
	{
		num = 0;
		while ((n = read(file, *vari + num, size - num)) > 0)
		{
			if (n < size - num)
			{
				(*vari)[n + num] = '\0';
			}
			size *= 2;
			buff = _malloc((size) * sizeof(char));
			num += n;
			_memcpy(buff, *vari, size / 2);
			*vari = buff;
		}
		close(file);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
/**
 * new_hist - makes new history
 * @new: history linked list to pass
 * @envp: environmental variable linked list
 * Return: a pointer to the history linked list
 */

void new_hist(hist_t *new, env_t *envp)
{
	char *string, *space;
	int i, j, n;

	/* create a space of what is in the file */
	space = _malloc(sizeof(char) * BUFSIZE);
	_memset(space, '\0', BUFSIZE);
	n = get_content(envp, &space);
	if (n > 0)
	{
		string = _malloc(sizeof(char) * _strlen(space));
		if (*space == '\0')
		{
			new_entry(new, "");
		}
		/* create linked list and fill in with what is in file*/
		// for (i = 0, j = 0; space[i] != '\0'; i++)
                i = 0;
                j = 0;
                while (space[i] != '\0')
		{
			if (space[i] == '\n')
			{
				string[j] = '\0';
				new_entry(new, string);
				j = 0;
			}
			else
				string[j++] = space[i];
                        i++;
		}
	}
}
/**
 * new_entry - adds to the linked list
 * @first: first 
 * @input: input
 * Description: add new node
 * Return: a pointer to the new node
 */

hist_t *new_entry(hist_t *first, char *input)
{
	hist_t *main_n;
	hist_t *new;

	main_n = _malloc(sizeof(hist_t));
	main_n->cmd = duplicate(input);
	main_n->next = NULL;
	if (first == NULL)
		first = main_n;
	else
	{
		new = first;
		while (new->next != NULL)
			new = new->next;
		new->next = main_n;
	}
	return (main_n);
}
/**
 * show_hist - prints the history
 * @main: main
 */

void show_hist(hist_t *main)
{
	char *hist;

        for (; main != NULL; main = main->next)
	// while (main != NULL)
	{
		hist = duplicate(main->cmd);
		_puts(hist);
		_puts("\n");
		// main = main->next;
	}
}
/**
 * add_to_list - add to end of list
 * @list: list
 * @input: command
 * Description: add to end of list
 */

void add_to_list(hist_t *list, char *input)
{
	int i, len;
	static int idx = 1;
	char *command;
	hist_t *new;

	command = _malloc(sizeof(char) * _strlen(input) + 1);
	new = list;
	if (idx == 1)
        {        
		// for (new = list; new != NULL; new = new->next)
                new = list;
                while (new != NULL)
                {
			idx++;
                        new = new->next;
                }
        }
	len = _strlen(input);
	// for (i = 0; i < len - 1; i++)
        i = 0;
        while (i < len - 1)
		command[i] = input[i], i++;
	command[i] = '\0';
	if (len > 1)
		new_entry(list, command);
	idx++;
	_free(command);
}