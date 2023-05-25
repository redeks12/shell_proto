#include "shell.h"
/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *p2 = "\n<oo> ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, p2, 3);
}