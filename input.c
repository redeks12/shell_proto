#include "shell.h"
/**
 * _getline - Read input and put in buffer
 * @b: buffer 
 * @fd: file 
 * @envp: enviornment 
 * Return: Always 0. Exit on failure or EOF
 */
int get_line(buffer *b, int fd, env_t *envp)
{
	int rack, n;

	rack = 0, n = 0;
	while ((n = read(fd, b->buf + rack, b->size - rack)) > 0 &&
			b->buf[b->bp + rack + n - 1] != '\n')
	{
		_realloc(b);
		rack = rack + n;
	}
	if (n == 0)
	{
		if (fd > 2)
			close(fd);
		_checker("", envp, 'w');
		_setfree(FREE_ADDRESSES);
		_exit(0);
	}
	b->buf[n + rack] = '\0';
	return (0);
}
/**
 * read_file - reads contents of files to buffer
 * @b: buffer
 * @envp: second param
 *
 * Return: 1 on file not exist, else 0
 */
int read_file(buffer *b, env_t *envp)
{
	int fd, i;
	char *file, *fullfile;

	/* scan through buffer and pull out file to read */
	i = b->bp;
        for ( ; is_w(b->buf[i]); i++);
	// while (is_w(b->buf[i]))
	// 	i++;
	if (!matchStrings(b->buf + i, "simple_shell") || b->buf[i] == '\0')
		return (0);
        for ( ;(!is_w(b->buf[i]) && b->buf[i] != '\0'); i++);
	// while (!is_w(b->buf[i]) && b->buf[i] != '\0')
	// 	i++;
        for ( ;is_w(b->buf[i]) && b->buf[i] != '\0'; i++);
	// while (is_w(b->buf[i]) && b->buf[i] != '\0')
	// 	i++;
        if (b->buf[i])
                fd = -1;
	// if (b->buf[i] == '\0')
	// 	fd = -1;
	else
	{
		file = b->buf + i;
                for ( ;(!is_w(b->buf[i]) && b->buf[i] != '\0'); i++);
		// while (!is_w(b->buf[i]) && b->buf[i] != '\0')
		// 	i++;
		b->buf[i] = '\0';
		new_pth(&fullfile, file, "PWD", envp);
		fd = open(fullfile, O_RDONLY);
	}
	if (fd == -1)
	{
		_checker("", envp, 'w');
		_setfree(FREE_ADDRESSES);
		_exit(1);
	}
	get_line(b, fd, envp);
	close(fd);
	return (0);
}

