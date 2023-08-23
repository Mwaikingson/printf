#include "main.h"

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - PERFORMS CLEANUP OPERATIONS for _printf..
 * @args: A va_list of arguments provided to _printf..
 * @output: A BUFFER_t struct.
 */

void cleanup(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - READS TROUGH the format string for _printf..
 * @format: CHAR STRING to print - may contain directives..
 * @output: A buffer_t STRUCT containing a BUFFER..
 * @args: A va_list of ARGUMENTS..
 *
 * RETURN: The NUM of characters stored to OUTPUT..
 */

int run_printf(const char *format, va_list args, buffer_t *output)
{
	int Z, wid, prec, ret = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (Z = 0; *(format + Z); Z++)
	{
		len = 0;
		if (*(format + Z) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + Z + 1, &tmp);
			wid = handle_width(args, format + Z + tmp + 1, &tmp);
			prec = handle_precision(args, format + Z + tmp + 1,
					&tmp);
			len = handle_length(format + Z + tmp + 1, &tmp);

			f = handle_specifiers(format + Z + tmp + 1);
			if (f != NULL)
			{
				Z += tmp + 1;
				ret += f(args, output, flags, wid, prec, len);
				continue;
			}
			else if (*(format + Z + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + Z), 1);
		Z += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (ret);
}

/**
 * _printf - OUTPUTS a formatted string..
 * @format: CHARACTER string to print - may contain directives.
 *
 * RETURN: The number of CHARACTERS printed..
 */

int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	ret = run_printf(format, args, output);

	return (ret);
}
