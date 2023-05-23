#include "shell.h"
/**
 * break_pth - tokenizes to path
 * @find: array
 * @locate: current location
 * @size: size of space
 * Return: a 2D array of tokens
 */

char **break_pth(char **search_path, char *path, int size)
{
	int i, count, s_index;
	char *temp, *buffer;

	buffer = _malloc(sizeof(char) * size);
	buffer[0] = '\0';
	for (i = 0, count = 1; path[i] != '\0'; i++)
	{
		if (path[i] == ':')
			count++;
	}
	count++;
	search_path = _malloc(sizeof(char *) * count);
	/* skip the PATH= */
	for (temp = path; *temp != '='; temp++)
		;
	temp++, s_index = 0;
	do {
		if (*temp == ':' || *temp == '\0')
		{
			_strncat(buffer, "/", 1);
			search_path[s_index] = _malloc(sizeof(char) * size);
			search_path[s_index][0] = NULL;
			_strncat(search_path[s_index], buffer, _strlen(buffer));
			s_index++;
			buffer[0] = NULL;
		}
		else
			_strncat(buffer, temp, 1);
	} while (*temp++);
	search_path[s_index] = _malloc(sizeof(char *));
	search_path[s_index] = NULL;
	return (search_path);
}
/**
 * break_buffer - tokenize buffer by inputting NULLs and filling **av
 * @cont: The buffer with the command string
 * @array: Pointer to the command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void break_buffer(buffer *cont, char ***array)
{
	int i, j, ident, w_s;
	char dir;

	size_x(cont->buf + cont->bp, array);

	/* Build the argument vector from the given buffer */
	// for (i = cont->bp, j = 0, ident = 1; !input_finish(cont->buf[i]); i++)
	i = cont->bp;
	j = 0;
	ident = 1;
	while (!input_finish(cont->buf[i]))
	{
		w_s = is_w(cont->buf[i]);
		if (ident && !w_s)
		{
			(*array)[j++] = cont->buf + i;
			ident = 0;
		}
		if (w_s)
		{
			cont->buf[i] = '\0';
			ident = 1;
		}
		i++;
	}
	(*array)[j] = NULL;
	/* If we end because of comments */
	if (cont->buf[i] == '#')
		while (cont->buf[i] != '\n' && cont->buf[i] != '\0')
			i++;
	/* If we ended because of newline, we MAY have more content */
	if (cont->buf[i] == '\n' && cont->buf[i + 1] != '\0')
		cont->buf[i] = ';';
	else if (cont->buf[i] == '\n')
		cont->buf[i] = '\0';
	/* If we ended because of flow control commands, */
	/* increment the buffer point and add a null before the character */
	if (cont->buf[i] == ';' || cont->buf[i] == '|' || cont->buf[i] == '&')
	{
		cont->bp += i - cont->bp;
		end_inp(cont->buf + cont->bp);
		cont->bp++;
	}
	else
		cont->bp = 0;

}