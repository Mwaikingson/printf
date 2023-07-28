#include "main.h"

/**
 * get_width - CALCULATES THE WIDTH for PRINTING..
 * @format: FORMATTED STRING in which to print the ARGUMENTS..
 * @X: LIST OF ARGUMENTS to be printed.
 * @list: List of ARGUMENTS..
 *
 * RETURN: WIDTH..
 */

int get_width(const char *format, int *X, va_list list)
{
	int curr_X;
	int width = 0;

	for (curr_X = *X + 1; format[curr_X] != '\0'; curr_X++)
	{
		if (is_digit(format[curr_X]))
		{
			width *= 10;
			width += format[curr_X] - '0';
		}
		else if (format[curr_X] == '*')
		{
			curr_X++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*X = curr_X - 1;

	return (width);
}
