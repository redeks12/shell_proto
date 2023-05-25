#include "shell.h"
/**
 * fc_p - Takes a fl and attempts to run the commands stored
 * within.
 * @locs: Path to the fl.
 * @rt_v: Return value of the last executed command.
 *
 * Return: If fl couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int fc_p(char *locs, int *rt_v)
{
	ssize_t fl, see, i;
	unsigned int s_w = 0;
	unsigned int pre_w = 120;
	char *mm, **arr, **eye;
	char space[120];
	int r;

	previous = 0;
	fl = open(locs, O_RDONLY);
	if (fl == -1)
	{
		*rt_v = _stp(locs);
		return (*rt_v);
	}
	mm = malloc(sizeof(char) * pre_w);
	if (!mm)
		return (-1);
	do {
		see = read(fl, space, 119);
		if (see == 0 && s_w == 0)
			return (*rt_v);
		space[see] = '\0';
		s_w += see;
		mm = _realloc(mm, pre_w, s_w);
		_strcat(mm, space);
		pre_w = s_w;
	} while (see);
	for (i = 0; mm[i] == '\n'; i++)
		mm[i] = ' ';
	for (; i < s_w; i++)
	{
		if (mm[i] == '\n')
		{
			mm[i] = ';';
			for (i += 1; i < s_w && mm[i] == '\n'; i++)
				mm[i] = ' ';
		}
	}
	c_cng(&mm, rt_v);
	p_input(&mm, s_w);
	arr = tok_brk(mm, " ");
	free(mm);
	if (!arr)
		return (0);
	if (see_cmd(arr) != 0)
	{
		*rt_v = 2;
		del_s(arr, arr);
		return (*rt_v);
	}
	eye = arr;

	for (i = 0; arr[i]; i++)
	{
		if (_strncmp(arr[i], ";", 1) == 0)
		{
			free(arr[i]);
			arr[i] = NULL;
			r = exec_cl(arr, eye, rt_v);
			arr = &arr[++i];
			i = 0;
		}
	}

	r = exec_cl(arr, eye, rt_v);

	free(eye);
	return (r);
}