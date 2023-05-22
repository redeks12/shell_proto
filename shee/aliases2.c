#include "shell.h"
/**
 * _a_shell - builtin for alias function
 * @arr: argument vector
 * @environ: env new
 * @type: Execution type for the program, 0 or !0
 * Description: Complicated parent function for the alias functionality
 *				of hsh. Uses two modes to allow it being called from
 *				multiple points from within our program.
 * Return: 0 on success, 2 on failure.
 */
int _a_shell(char **arr, env_t *environ, int type)
{
	int result;
	static alias new = {NULL, NULL, NULL};

	(void) environ;
	if (type == 0)
	{
		arr[0] = a_find(&new, arr[0]);
		return (0);
	}
	else
	{
		if (arr[1] == NULL)
			result = a_complete(&new);
		else if (arr[2] != NULL)
		{
			_puts("Error. Too many arguments.");
			return (2);
		}
		else
		{
			result = a_print(&new, arr);
			if (result == 1)
				result = a_operations(&new, arr);
		}
	}
	return (result);
}