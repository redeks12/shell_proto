#include "shellHeader.h"

/**
 * _addpath - adds path to filname
 * @first: pointer to path
 * @second: pointer to filename
 * Return: pointer to merged string or NULL if fails
 */
char *_addpath(char *first, char *second)
{
	int i, j, k;
	char *new;

	k = (_strlen(first)) + (_strlen(second)) + 2;
	new = malloc(k * sizeof(char));
	if (!new)
		return (NULL);
	for (i = 0; first[i]; i++)
		new[i] = first[i];
	new[i] = '/';
	i++;
	for (j = 0; second[j]; j++)
	{
		new[i] = second[j];
		i++;
	}
	new[i] = '\0';
	ptofree(new, 1);
	return (new);
}
/**
 * _strdup - allocates and copies string
 * @str: string thats being duplicated
 * Return: duplicated string
 */
char *_strdup(char *str)
{
	char *a;
	int i, j;

	if (str == NULL)
		return (NULL);
	/* length of str */
	for (i = 0; str[i]; i++)
		;
	i++; /*include null character*/
	/*allocating memory for a*/
	a = malloc(i * sizeof(char));
	/*checks if memory is allocated and if str is null*/
	if (a == NULL)
		return (NULL);
	/*coping string*/
	for (j = 0; j < i; j++)
		a[j] = str[j];
	ptofree(a, 1);
	return (a);
}
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: a pointer to the memory previously allocated with a call to
 * malloc: malloc(old_size)
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 * Return: ptr | NULL if malloc faile or newsize is 0 or ptr null|
 * newpointer with more space
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	/*casting the void ptr to become char * so i can do pointer arithmetic*/
	char *oldptr = ptr;
	char *newptr;
	size_t i, size;

	if (old_size == 0)
		old_size = _strlen((char *) ptr);

	size = old_size;

	if (old_size > new_size)
		size = new_size;

	/*dont new to reallocate space cause size is same*/
	if (new_size == size)
		return (ptr);
	/*creating new memory*/
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	/* freeing ptr*/
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/*expanding memory*/
	if (new_size > size)
	{
		newptr = malloc(new_size);
		if (newptr == NULL)
			return (NULL);
		/*transfer old content into new*/
		for (i = 0; i < size; i++)
			newptr[i] = oldptr[i];
		free(ptr);
	}
	return (newptr);
}
/**
 * ptofree - saves malloced pointers
 * @p: pointer to save
 * @n: stage
 * Return: double pointer holding malloced pointers
 */
char **ptofree(char *p, int n)
{
	static char *pp[20];
	int i = 0;

	if (!n & !p)
	{
		while (i < 10)
		{
			pp[i] = NULL;
			i++;
		}
	}
	else if (!p && n == -1)
	{
		i = 0;
		while (pp[i])
			free(pp[i]), i++;
		return (NULL);
	}
	else
	{
		i = 0;
		while (pp[i])
			i++;
		pp[i] = p;
	}
	return (pp);
}
/**
 * gethome - finds the home path
 * @env: double pointer with env
 * Return: pointer with home path
 */
char *gethome(char **env)
{
	int i = 0;
	char *home;

	while (env[i])
	{
		if (_strncmp(env[i], "HOME", 4))
		{
			home = malloc(sizeof(char) * (_strlen(env[i]) - 4));
			home = _strncpy(home, env[i], 0, 5);
			return (home);
		}
		i++;
	}
	return (NULL);
}
