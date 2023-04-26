#include "shellHeader.h"
#define UNUSED(x) (void)(x)
/**
 * main - Entry point for hsh
 * @argc: attribute unused
 * @argv: attribute unused
 * @env: used to pass enviroment conf to functions
 * Return: Success or Failure
 */
int main(int argc, char **argv, char **env)
{
	char **tokens, *buffer = NULL, *home;
	size_t bufsize = 0;
	int check, isCmd, count = 1, interactive = 0;
	struct stat sb;

	UNUSED(argc);
	signal(SIGINT, signal_handler);
	if (fstat(STDIN_FILENO, &sb) == -1)
		perror("Fstat error"), _exit(EXIT_FAILURE);
	if ((sb.st_mode & S_IFMT) == S_IFIFO)
		interactive = 1;
	if (!interactive)
		_printf("$ ");
	home = gethome(env);
	while (getline(&buffer, &bufsize, stdin) != -1)
	{
		if (buffer[0] != '\n')
		{
			ptofree(NULL, 0), history_file(buffer, home);
			tokens = tokenize(buffer, " ");/*TOKENIZE & COMMAND CHECK*/
			if (tokens == NULL)
				perror("tokenize() Failed");
			if (!_strcmp(tokens[0], "exit"))
			{
				ptofree(NULL, -1), free(tokens), free(buffer), free(home);
				_exit(EXIT_SUCCESS);
			}
			isCmd = cmdchk(tokens, env);/*Check if cmd and if special cmd*/
			if (isCmd == 0)/*COMMAND EXECUTION*/
				check = cmdExec(tokens, env);
			else if (isCmd >= 1)/*SPECIAL CMD EXECUTION*/
				check = specialExec(tokens, env, isCmd, home);
			else/*NO COMMAND FOUND*/
				_printf("%s: %d: %s: not found\n", argv[0], count, tokens[0]);
			if (check == EXIT_FAILURE)
				perror("Execution Failed");
			count++;
			ptofree(NULL, -1), free(tokens);
		}
		if (!interactive)
			_printf("$ ");
	}
	free(buffer), free(home);
	return (EXIT_SUCCESS);
}
