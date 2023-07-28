#include "main.h"

/**
 * get_flags - Calculates the ACTIVE FLAGS..
 * @fmat: formatted string in which to print the arguments
 * @j: takes a PARAMETER..
 * RETURN: flags:
 */

int get_flags(const char *fmat, int *j)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int p, curr_j;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_j = *j + 1; fmat[curr_j] != '\0'; curr_j++)
	{
		for (p = 0; FLAGS_CH[p] != '\0'; p++)
			if (fmat[curr_j] == FLAGS_CH[p])
			{
				flags |= FLAGS_ARR[p];
				break;
			}

		if (FLAGS_CH[p] == 0)
			break;
	}

	*j = curr_j - 1;

	return (flags);
}
