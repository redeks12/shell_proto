#include "shell.h"
/**
 * main - Runs a simple UNIX command interpreter.
 * @ac: The number of arguments supplied to the program.
 * @av: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int ac, char *av[])
{
	int i = 0, vl;
	int *m_vl = &vl;
	char *pr = "<oo> ", *ne = "\n";

	ident = av[0];
	previous = 1;
	frd = NULL;
	signal(SIGINT, sig_handler);

	*m_vl = 0;
	toppth = pth_cp();
	if (!toppth)
		exit(-100);

	if (ac != 1)
	{
		i = fc_p(av[1], m_vl);
		clear_pth();
		_rfl(frd);
		return (*m_vl);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (i != END_OF_FILE && i != EXIT)
			i = work_cmd(m_vl);
		clear_pth();
		_rfl(frd);
		return (*m_vl);
	}

	while (1)
	{
		write(STDOUT_FILENO, pr, 2);
		i = work_cmd(m_vl);
		if (i == END_OF_FILE || i == EXIT)
		{
			if (i == END_OF_FILE)
				write(STDOUT_FILENO, ne, 1);
			clear_pth();
			_rfl(frd);
			exit(*m_vl);
		}
	}

	clear_pth();
	_rfl(frd);
	return (*m_vl);
}
