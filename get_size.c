#include "main.h"

/**
 * get_size - CALCULATES THE SIZE to cast the argument..
 * @format: FORMATTED STRING in which to print the arguments..
 * @j: LIST OF ARGUMENTS to be printed..
 *
 * RETURN: PRECISION.
 */

int get_size(const char *format, int *X)
{
	int curr_X = *X + 1;
	int size = 0;

	if (format[curr_X] == 'l')
		size = S_LONG;
	else if (format[curr_X] == 'h')
		size = S_SHORT;

	if (size == 0)
		*X = curr_X - 1;
	else
		*X = curr_X;

	return (size);
}
