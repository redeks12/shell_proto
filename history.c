#include "shellHeader.h"
/**
 * history_file - creates the history file or appends to it
 * @text_content: text to add in file
 * @dir: path to home
 * Return: returns 1 on succesm , -1 on failure
 */
int history_file(char *text_content, char *dir)
{
	int c, fd, status = 0;
	char *filename = ".simple_shell_history";
	pid_t pid;

	if (text_content == NULL)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		chdir(dir);
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd == -1)
			exit(EXIT_FAILURE);

		c = write(fd, text_content, _strlen(text_content));
		if (c == -1)
		{
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
	return (status);
}

/**
 * history -  reads the history and prints it to stdout
 * @dir: Path to enviroment
 * Return: returns 1 if success or 0 if fail
 */
int history(char *dir)
{
	int c = 1, fd, i = 0, j = 0, status = 0, count = 0;
	char text[1024], *buf, *filename = ".simple_shell_history";
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		chdir(dir);/*history file in home dir*/
		fd = open(filename, O_RDONLY);/*open file to read*/
		do {
			c = read(fd, text, 1024);/*read from history file*/
			if (c == -1)
				exit(EXIT_FAILURE);
			for (i = 0; i < c; i++)
				if (text[i] == '\n')
					count++;
			if (c != 0)
			{
				buf = strtok(text, "\n");
				if (buf)
					while (j < count)
					{
						_printf("%d  %s\n", j, buf);
						buf = strtok(NULL, "\n\0");
						j++;
					}
			}
		} while (c);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
	return (status);
}
