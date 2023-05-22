#include "shell.h"
/**
 * _del_nm - removes name
 * @environ: environement
 * @tb_rm: search
 * @size: size
 * Return: a string containing the path
 */
char *_del_nm(env_t *environ, char *tb_rm, int size)
{
	char *cur_dir;
	env_t *new;

	cur_dir = _malloc(sizeof(char) * size);
	_memset(cur_dir, '\0', size);
	new = environ;
	for (; ; new = new->next)
	{
		if (compareStrings(new->value, tb_rm))
		{
			_strcpy(cur_dir, new->value);
			break;
		}
		else if (new->next == NULL)
		{
			_free(cur_dir);
			return (NULL);
		}
	}
	while (*cur_dir != '=')
		cur_dir++;
	cur_dir++;
	return (cur_dir);
}
/**
 * _ret_val - retrives a value from the environment list
 * @environ: the env list
 * @key: key
 * Return: a pointer
 */
char *_ret_val(env_t *environ, char *key)
{
	char *new_val;

	while (1)
	{
		if (compareStrings(environ->value, key))
		{
			new_val = environ->value;
			break;
		}
		else if (environ->next == NULL)
			return (NULL);
		environ = environ->next;
	}
	while (*new_val++ != '=');

	return (new_val);
}
/**
 * _rem_pth - remove symbols from pwd
 * @environ: environement
 * @pth: pth
 * @size: size
 */
char *_rem_pth(char **arr, env_t *environ, char *pth, int size)
{
	int i, sym_num, identifyer;
	char *curdir, *new_path;

	new_path = _malloc(sizeof(char) * size);
	_memset(new_path, '\0', size);
	_strcpy(new_path, pth);
        i = 0;
        sym_num = 0;
        while (new_path[i] != '\0')
        {
                if (new_path[i] == '/')
                        sym_num++;
                i++;
        }
	// for (i = 0, sym_num = 0; new_path[i] != '\0'; i++)
	// {
	// 	if (new_path[i] == '/')
	// 		sym_num++;
	// }
	curdir = arr[1];
	if (_strcmp(curdir, ".") == 0)
		new_path = _del_nm(environ, "PWD=", size);
	else if (_strcmp(curdir, "~") == 0)
		new_path = _del_nm(environ, "HOME=", size);
	else if (_strcmp(curdir, "..") == 0)
	{
                identifyer = 0;
                i = 0;
                while (identifyer < sym_num - 1)
                {
                        if (new_path[i] == '/')
				identifyer++;
                        i++;;
                }
                
		/* check for if things behind it + append*/
		// for (identifyer = 0, i = 0; identifyer < sym_num - 1; i++)
		// {
		// 	if (new_path[i] == '/')
		// 		identifyer++;
		// }
		new_path[i - 1] = '\0';
	}
	else if (_strcmp(curdir, "-") == 0)
		new_path = _del_nm(environ, "OLDPWD=", size);
	return (new_path);
}
/**
 * new_pth - new pth for tghe bfile
 * @pth: pth to create
 * @file: file
 * @character: character
 * @environment: environement
 * Return: the pth str
 */
char *new_pth(char **pth, char *file, char *character, env_t *environ)
{
	char *value;

	if (_strstr(character, "/"))
	{
		*pth = file;
		return (file);
	}

	value = _ret_val(environ, character);
	*pth = _malloc(sizeof(char) * (_strlen(value) + _strlen(file) + 2));
	_memcpy(*pth, value, _strlen(value) + 1);
	strcat(*pth, "/");
	strcat(*pth, file);
	return (*pth);
}
/**
 * env_shell - environment builtin
 * @arr: args
 * @environ: environment
 * Return: 0 if success.
 */
int env_shell(char **arr, env_t *environ)
{
	int count;

	if (arr[1] == NULL)
	{
		env_shw(environ);
		return (EXIT_SUCCESS);
	}
	
        count = 1;
        while (arr[count] != NULL)
        {
		arr[count - 1] = arr[count];
                count++;
        }
	// for (count = 1; arr[count] != NULL; count++)
	// 	arr[count - 1] = arr[count];
	arr[count - 1] = arr[count];
	return (EXIT_FAILURE);
}