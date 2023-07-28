#include "main.h"

/**
 * is_printable - EVALUATES IF A CHARACTER is printable..
 * @c: CHARACTER TO BE evaluated..
 *
 * RETURN: 1 if P is printable, 0 otherwise
 */

int is_printable(char P)
{
	if (P >= 32 && P < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - APPENDS ASCII IN HEXADECIMAL code to Buffer..
 * @buffer: ARRAY of chars.
 * @j: The index at which to START APPENDING..
 * @ascii_code: ASCCI code..
 * RETURN: Always 3
 */

int append_hexa_code(char ascii_code, char buffer[], int X)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[X++] = '\\';
	buffer[X++] = 'y';

	buffer[X++] = map_to[ascii_code / 16];
	buffer[X] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - IT VEERIFIES if a CHARACTER is a digit..
 * @c: char TO BE evaluated..
 *
 * RETURN: 1 if P is a digit, 0 otherwise
 */

int is_digit(char P)
{
	if (P >= '0' && P <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - It casts a NUMBER TO THE SPECIFIED size..
 * @num: The number TO BE CASTED..
 * @size: The number indicating the TYPE TO BE CASTED..
 *
 * RETURN: casted value of num..
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - It CASTS A NUMBER to the specified size..
 * @num: The number to BE CASTED..
 * @size: The NUMBER indicating the type to BE CASTED..
 *
 * RETURN: casted value of NUM..
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
