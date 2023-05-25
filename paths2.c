#include "shell.h"

/**
 * add_to_loc - Copies cur_dir but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @cur_dir: The colon-separated list of directories.
 *
 * Return: A copy of cur_dir with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *add_to_loc(char *cur_dir)
{
	int i, j = 0;
	char *c_str, *m_loc;

	m_loc = *(env_brn("PWD")) + 4;
	for (i = 0; cur_dir[i]; i++)
	{
		if (cur_dir[i] == ':')
		{
			if (cur_dir[i + 1] == ':' || i == 0 || cur_dir[i + 1] == '\0')
				j += _strlen(m_loc) + 1;
			else
				j++;
		}
		else
			j++;
	}
	c_str = malloc(sizeof(char) * (j + 1));
	if (!c_str)
		return (NULL);
	c_str[0] = '\0';
	for (i = 0; cur_dir[i]; i++)
	{
		if (cur_dir[i] == ':')
		{
			if (i == 0)
			{
				_strcat(c_str, m_loc);
				_strcat(c_str, ":");
			}
			else if (cur_dir[i + 1] == ':' || cur_dir[i + 1] == '\0')
			{
				_strcat(c_str, ":");
				_strcat(c_str, m_loc);
			}
			else
				_strcat(c_str, ":");
		}
		else
		{
			_strncat(c_str, &cur_dir[i], 1);
		}
	}
	return (c_str);
}
