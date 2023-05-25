#include "shell.h"

/**
 * sh_all - Displays all possible builtin shellby commands.
 */
void sh_all(void)
{
	char *h_all = "Shellby\nThese shell commands are defined internally.\n";

	print_hlps(h_all);
	h_all = "Type 'help' to see this list.\nType 'help name' to find ";
	print_hlps(h_all);
	h_all = "out more about the function 'name'.\n\n  alias   \t";
	print_hlps(h_all);
	h_all = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	print_hlps(h_all);
	h_all = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	print_hlps(h_all);
	h_all = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	print_hlps(h_all);
	h_all = "unsetenv [VARIABLE]\n";
	print_hlps(h_all);
}
/**
 * sh_cd - Displays information on the shellby builtin command 'cd'.
 */
void sh_cd(void)
{
	char *h_cd = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	print_hlps(h_cd);
	h_cd = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	print_hlps(h_cd);
	h_cd = "command is interpreted as cd $HOME. If the argument '-' is";
	print_hlps(h_cd);
	h_cd = " given, the command is interpreted as cd $OLDPWD.\n\n";
	print_hlps(h_cd);
	h_cd = "\tThe environment variables PWD and OLDPWD are updated ";
	print_hlps(h_cd);
	h_cd = "after a change of directory.\n";
	print_hlps(h_cd);
}
/**
 * sh_exit - Displays information on the shellby builtin command 'exit'.
 */
void sh_exit(void)
{
	char *h_exit = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	print_hlps(h_exit);
	h_exit = "STATUS argument is the integer used to exit the shell.";
	print_hlps(h_exit);
	h_exit = " If no argument is given, the command is interpreted as";
	print_hlps(h_exit);
	h_exit = " exit 0.\n";
	print_hlps(h_exit);
}

/**
 * sh_help - Displays information on the shellby builtin command 'help'.
 */
void sh_help(void)
{
	char *h_h = "help: help\n\tSee all possible Shellby builtin commands.\n";

	print_hlps(h_h);
	h_h = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	print_hlps(h_h);
	h_h = "builtin command.\n";
	print_hlps(h_h);
}
void sh_alias(void)
{
	char *h_al = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	print_hlps(h_al);
	h_al = "\n\talias: Prints a list of all aliases, one per line, in ";
	print_hlps(h_al);
	h_al = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	print_hlps(h_al);
	h_al = " the aliases name, name2, etc. one per line, in the ";
	print_hlps(h_al);
	h_al = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	print_hlps(h_al);
	h_al = " an alias for each NAME whose VALUE is given. If NAME ";
	print_hlps(h_al);
	h_al = "is already an alias, replace its value with VALUE.\n";
	print_hlps(h_al);
}
/**
 * sh_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void sh_setenv(void)
{
	char *h_senv = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	print_hlps(h_senv);
	h_senv = "environment variable, or modifies an existing one.\n\n";
	print_hlps(h_senv);
	h_senv = "\tUpon failure, prints a message to stderr.\n";
	print_hlps(h_senv);
}

