#include "shell.h"
/**
 * tok_brk - Tokenizes a string.
 * @lk: The string.
 * @emb: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **tok_brk(char *lk, char *emb)
{
	char **nt;
	int i = 0, tok, t, alph, j;

	tok = num_strs(lk, emb);
	if (tok == 0)
		return (NULL);

	nt = malloc(sizeof(char *) * (tok + 2));
	if (!nt)
		return (NULL);

	for (t = 0; t < tok; t++)
	{
		while (lk[i] == *emb)
			i++;

		alph = sz_strs(lk + i, emb);

		nt[t] = malloc(sizeof(char) * (alph + 1));
		if (!nt[t])
		{
			for (i -= 1; i >= 0; i--)
				free(nt[i]);
			free(nt);
			return (NULL);
		}

		for (j = 0; j < alph; j++)
		{
			nt[t][j] = lk[i];
			i++;
		}

		nt[t][j] = '\0';
	}
	nt[t] = NULL;
	nt[t + 1] = NULL;

	return (nt);
}
