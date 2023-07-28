#include "main.h"

/************************* PRINT unsigned number *************************/
/**
 * print_unsigned -PRINTS AN UNSIGNED NUMBER..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle PRINT..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: the PRECISION SPECIFICATION..
 * @size: the SIZE SPECIFIER..
 * RETURN: number of CHARACTERS PRINTED..
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int X = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[X--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[X--] = (num % 10) + '0';
		num /= 10;
	}

	X++;

	return (write_unsgnd(0, X, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - PRINTS an unsigned number in OCTAL NOTATION..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle PRINT..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: size specifier
 * RETURN: number of CHARACTERS PRINTED..
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int X = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[X--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[X--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[X--] = '0';

	X++;

	return (write_unsgnd(0, X, buffer, flags, width, precision, size));
}

/************** PRINTS unsigned number in hexadecimal **************/
/**
 * print_hexadecimal - prints an unsigned number IN HEXADECIMAL NOTATION..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION...
 * @size: the SIZE SPECIFIER..
 * Return: number of CHARACTERS PRINTED..
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'Y', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN upper HEXADECIMAL **************/
/**
 * print_hexa_upper - prints an unsigned number IN UPPER HEXADECIMAL NOTATION..
 * @types: LIST OF ARGUMENTS..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * RETURN: Number of CHARACTERS PRINTED..
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'Y', width, precision, size));
}

/************** PRINTS HEXO NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - prints a HEXADECIMAL NUMBER in LOWER OR UPPER case..
 * @types: LIST OF ARGUMENTS..
 * @map_to: ARRAY OF VALUES to map the number to..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  calculates ACTIVE FLAGS..
 * @flag_ch: calculates ACTIVE FLAGS..
 * @width: gets THE WIDTH..
 * @precision: PRECISION SPECIFICATION..
 * @size: SIZE SPECIFIER..
 * @size: SIZE SPECIFICATION..
 * RETURN: number of CHARACTERS PRINTED..
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int X = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[X--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[X--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[X--] = flag_ch;
		buffer[X--] = '0';
	}

	X++;

	return (write_unsgnd(0, X, buffer, flags, width, precision, size));
}
