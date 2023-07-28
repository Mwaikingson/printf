#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - PRINTS THE VALUE of a pointer VARIABLE..
 * @types: LIST of ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle PRINT..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: THE SIZE SPECIFIER..
 * RETURN: number of CHARS PRINTED..
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_b = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_b = '+', length++;
	else if (flags & F_SPACE)
		extra_b = ' ', length++;

	ind++;

	/*return (write(1, &buffer[j], BUFF_SIZE - j - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_b, padd_start));
}

/************************* PRINT non printable *************************/
/**
 * print_non_printable - PRINTS THE ASCII CODES IN HEXADECIMAL of non printable characters..
 * @types: LIST of ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * Return: number of CHARACTERS PRINTED..
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int X = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[X] != '\0')
	{
		if (is_printable(str[X]))
			buffer[X + offset] = str[X];
		else
			offset += append_hexa_code(str[X], buffer, X + offset);

		X++;
	}

	buffer[X + offset] = '\0';

	return (write(1, buffer, X + offset));
}

/************************* PRINTS THE REVERSE *************************/
/**
 * print_reverse - PRINTS THE REVERSE string..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * Return: numbers of CHARACTERS printed..
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int X, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (X = 0; str[X]; X++)
		;

	for (X = X - 1; X >= 0; X--)
	{
		char z = str[X];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - PRINTS A STRING in rot13.
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * Return: numbers of CHARACTERS printed..
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char Y;
	char *str;
	unsigned int X, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (X = 0; str[X]; X++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[X])
			{
				Y = out[k];
				write(1, &X, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			Y = str[X];
			write(1, &Y, 1);
			count++;
		}
	}
	return (count);
}
