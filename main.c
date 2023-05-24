#include "shell.h"
/**
 * c_extra - checks if there are exta commands
 * @space: space
 * @rt: Return
 * Return: 1 if we have more commands to execute, 0 if we don't
 */
int c_extra(buffer *space, int rt)
{
	if (space->bp == 0)
		return (0);

	while (space->buf[space->bp] != '\0')
	{
		if (space->buf[space->bp] == ';')
		{
			c_short(space);
			return (1);
		}
		if (space->buf[space->bp] == '&' && rt == 0)
		{
			c_short(space);
			return (1);
		}
		if (space->buf[space->bp] == '|' && rt != 0)
		{
			c_short(space);
			return (1);
		}
		space->bp++;
	}
	space->bp = 0;
	return (0);
}
/**
 * c_short - short
 * @space: space
 */
void c_short(buffer *space)
{
	int chk;

	chk = 0;
	while (space->buf[space->bp] == ';')
		space->bp++, chk = 1;
	if (chk)
		return;

	while (space->buf[space->bp] == '|')
		space->bp++, chk = 1;
	if (chk)
		return;

	while (space->buf[space->bp] == '&')
		space->bp++;
}
/**
 * main - hsh
 * @ac: argument count
 * @av: a list of all arguments
 * @environ: environmental variable list from the parent
 * Return: 0 on success.
 */
int main(int ac, char **av, char **environ)
{
	char **array;
	env_t *ev_n;
	int rt;
	buffer b = {NULL, BUFSIZE, 0};
	(void)ac, (void)av, (void)environ;

	b.buf = _malloc(sizeof(char) * b.size);
	array = NULL;
	rt = 0;

	ev_n = mk_env();
	_checker("", ev_n, 'c');
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, _sig);
	while (1)
	{
		if (!c_extra(&b, rt))
		{
			_puts("$ ");
			get_line(&b, STDIN_FILENO, ev_n);
			_checker(b.buf, ev_n, 'a');
		}
		while (aliase(&b, ev_n))
			;
		_to_buff(&b, ev_n, rt);
		read_file(&b, ev_n);
		break_buffer(&b, &array);
		if (array[0] == NULL)
			continue;
		rt = execute2(array, ev_n, b.size);
		if (rt != 0 && rt != 2)
		{
			rt = exec_part(array, ev_n, b.size);
		}
			
	}
	return (EXIT_SUCCESS);
}
