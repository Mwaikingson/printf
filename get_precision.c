#include "main.h"

/**
 * get_precision - calculates the PRECISION FORPRINTING..
 * @format: formatted string in which to PRINT THE ARGUMENTS..
 * @j: list of ARGUMENTS to be PRINTED.
 * @list: List of ARGUMENTS.
 *
 * Return: PRECISION.
 */

int get_precision(const char *format, int *X, va_list list)
{
	int curr_X = *X + 1;
	int precision = -1;

	if (format[curr_X] != '.')
		return (precision);

	precision = 0;

	for (curr_X += 1; format[curr_X] != '\0'; curr_X++)
	{
		if (is_digit(format[curr_X]))
		{
			precision *= 10;
			precision += format[curr_X] - '0';
		}
		else if (format[curr_X] == '*')
		{
			curr_X++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*X = curr_X - 1;

	return (precision);
}
