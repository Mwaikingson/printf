#include "main.h"

/************************* PRINT CHARACTER *************************/

/**
 * print_char - PRINTS a CHARACTER..
 * @types: LIST of ARGUMENTS..
 * @buffer:BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * RETURN: NUMBER OF CHARACTERS PRINTED..
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char Z = va_arg(types, int);

	return (handle_write_char(Z, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - PRINTS A STRING..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: GET WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * RETURN: Number of CHARACTERS printed..
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, X;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (X = width - length; X > 0; X--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (X = width - length; X > 0; X--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINTS PERCENTAGE SIGN *************************/
/**
 * print_percent - PRINTS a PERCENTAGE SIGN..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle the PRINT..
 * @flags:  Calculates ACTIVE FLAGS..
 * @width: Gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * RETURN: number of CHARACTERS printed..
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INTEGER *************************/
/**
 * print_int - PRINTS int..
 * @types: LIST of ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle PRINT..
 * @flags:  calculates the ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * Return: NUMBER OF CHARACTERS PRINTED..
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int X = BUFF_SIZE - 2;
	int is_negative = 0;
	long int B = va_arg(types, long int);
	unsigned long int num;

	B = convert_size_number(B, size);

	if (B == 0)
		buffer[X--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)B;

	if (B < 0)
	{
		num = (unsigned long int)((-1) * B);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[X--] = (num % 10) + '0';
		num /= 10;
	}

	X++;

	return (write_number(is_negative, X, buffer, flags, width, precision, size));
}

/************************* print BINARY *************************/
/**
 * print_binary - PRINTS an unsigned number..
 * @types: list of ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle PRINT..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * Return: number of CHARACTERS PRINTED..
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int m, p, X, sum;
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	m = va_arg(types, unsigned int);
	p = 2147483648; /* (2 ^ 31) */

	for (X = 0, sum = 0, count = 0; X < 32; X++)
	{
		sum += (m / p) % 2;
		if (sum || X == 31)
		{
			char z = '0' + (m / p) % 2;
			write(1, &z, 1);
			count++;
		}
		p /= 2;
	}
	return count;
}
