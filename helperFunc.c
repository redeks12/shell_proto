#include "shellHeader.h"
/**
 * tokenize -  splits string into smaller strings
 * and palces them in an array
 * @arguments: string being examined
 * @delimiter: where the sting is being split
 * Return: array of char pointers representing tokens
 */
char **tokenize(char *arguments, const char *delimiter)
{
	char **tokens, *token;
	size_t i, numtokens = 1;

	if (arguments == NULL || delimiter == NULL)
		return (NULL);
	/*go through string and count the delimiters*/
	for (i = 0; arguments[i]; i++)
		if (arguments[i] == *delimiter)
			numtokens++;
	/*allocate space in char *array  to hold tokens from string*/
	tokens = malloc(sizeof(char *) * (numtokens + 1));
	if (tokens == NULL)
		return (NULL);
	/*get each token and store it in char *array*/
	token = strtok(arguments, delimiter);
	for (i = 0; token; i++)
	{
		token = cutspecial(token);/*cuts of special endings from str*/
		tokens[i] = token;
		token = strtok(NULL, delimiter);
	}
	tokens[i] = NULL;
	return (tokens);

}
/**
 * cutspecial - cuts of special characters from string
 * @string: string thats being looked at
 * Return: cutoff version of string or NULL
 */
char *cutspecial(char *string)
{
	int i, j;
	char special[] = {'\n', '\t', 0};

	if (string == NULL)
		return (NULL);
	for (i = 0; string[i]; i++)
	{
		for (j = 0; special[j]; j++)
			if (string[i] == special[j])
				string[i] = '\0';
	}

	return (string);
}
/**
 * _getenv - gets desired enviroment variable
 * @name: KEY
 * @environ: enviroment variables
 * Return: VALUE (string)
 */
char *_getenv(char *name, char **environ)
{
	char *value;
	unsigned int i;

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)))
		{
			/*make space for the VALUE*/
			value = malloc(sizeof(char) * (_strlen(environ[i]) - _strlen(name) + 1));
			value = _strncpy(value, environ[i], 0, (_strlen(name) + 1));
			ptofree(value, 1);
			return (value);
		}
	}
	return (NULL);
}
/**
 * cmdchk - checks in PATH if the first token is an executiable.
 * @tokens: command and its arguments
 * @environ: enviroment variables
 * Return: -1 Failure | 0 no cmd | 1 cmd | 2 special cmd
 */
int cmdchk(char **tokens, char **environ)
{
	int i, controller = -1;
	char **paths, *path, *cmd, *cmdp;
	static char * const special [] = {"echo", "cd", "env", "history", "cp", 0};

	if (tokens[0][0] == '/')
	{
		controller = 0;
		return (controller);
	}
	path = _getenv("PATH", environ);
	paths = tokenize(path, ":");
	if (!paths)
		return (EXIT_FAILURE);
	cmd = _strdup(tokens[0]);
	for (i = 0; paths[i]; i++)
	{
		cmdp = _addpath(paths[i], cmd);/*add path to cmd*/
		if (!access(cmdp, F_OK))/*if exe found in path*/
		{
			tokens[0] = cmdp;
			controller = 0;
			break;
		}
	}
	for (i = 0; special[i]; i++)
	{
		if (!_strcmp(cmd, special[i]))/*if special*/
		{
			controller = i + 1;
			break;
		}
	}
	free(paths);
	return (controller);
}
