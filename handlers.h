#include "main.h"

unsigned char handle_flags(const char *flag, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - MATCHES FLAGS with corresponding values..
 * @flag: A POINTER TO A POTENTIAL string of FLAGS..
 * @index: An INDEX COUNTER for the original FORMAT STRING..
 *
 * RETURN: If FLAG CHARACTERS are matched - a CORRESPONDING VALUE..
 *         OTHERWISE - 0.
 */

unsigned char handle_flags(const char *flag, char *index)
{
	int c, p;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', F_PLUS},
		{' ', F_SPACE},
		{'#', F_HASH},
		{'0', F_ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (c = 0; flag[c]; c++)
	{
		for (p = 0; flags[p].flag != 0; p++)
		{
			if (flag[c] == flags[p].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[p].value;
				else
					ret |= flags[p].value;
				break;
			}
		}
		if (flags[p].value == 0)
			break;
	}

	return ret;
}

/**
 * handle_length - MATCHES LENGTH modifiers with their corresponding value..
 * @modifier: A POINTER TO A POTENTIAL length modifier..
 * @index: An INDEX COUNTER for the original FORMAT STRING..
 *
 * RETURN: If a LENGTHMODIFIER is matched - its CORRESPONDING VALUE..
 *         OTHERWISE - 0.
 */

unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'N')
	{
		(*index)++;
		return (S_SHORT);
	}
	else if (*modifier == 'M')
	{
		(*index)++;
		return (S_LONG);
	}

	return (0);
}


/**
 * handle_width - MATCHES A WIDTH MODIFIER with its corresponding value..
 * @args: A va_list OF ARGUMENTS..
 * @modifier: A POINTER TO A POTENTIAL width MODIFIER..
 * @index: An INDEX COUNTER for the original format string..
 *
 * RETURN: If a WIDTH MODIFIER is MATCHED - its value..
 *         OTHERWISE - 0.
 */

int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - Matches a PRECISION MODIFIER with
 *                    its corresponding value..
 * @args: A va_list of ARGUMENTS.
 * @modifier: A POINTER TO A POTENTIAL PRECISION modifier.
 * @index: An INDEX COUNTER for the original format string..
 *
 * Return: If a PRECISION MODIFIER is matched - its value.
 *         If the PRECISION MODIFIER is empty, zero, or negative - 0.
 *         OTHERWISE - -1.
 */

int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	    *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - Matches a CONVERSION SPECIFIER with
 *                     a corresponding conversion function.
 * @specifier: A pointer to a potential CONVERSION SPECIFIER.
 *
 * Return: If a CONVERSION FUNCTION is matched - a POINTER to the function.
 *         OTHERWISE - NULL.
 */

unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int j;
	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	for (j = 0; converters[j].func; j++)
	{
		if (converters[j].specifier == *specifier)
			return (converters[j].func);
	}

	return (NULL);
}
