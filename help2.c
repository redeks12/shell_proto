#include "shell.h"

void sh_unsetenv(void)
{
	char *h_uenv = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	print_hlps(h_uenv);
	h_uenv = "environmental variable.\n\n\tUpon failure, prints a ";
	print_hlps(h_uenv);
	h_uenv = "message to stderr.\n";
	print_hlps(h_uenv);
}

void sh_env(void)
{
	char *h_env = "env: env\n\tPrints the current environment.\n";

	print_hlps(h_env);
}
void print_hlps(char *hlp)
{
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}