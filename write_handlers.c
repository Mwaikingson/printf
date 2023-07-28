#include "main.h"

/*********************** WRITE HANDLE ***********************/
/**
 * handle_write_char - It PRINTS A STRING..
 * @b: CHARACTER types.
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  It calculates ACTIVE FLAGS..
 * @width: Get WIDTH..
 * @precision: PRECISION SPECIFIER..
 * @size: SIZE SPECIFIER..
 *
 * RETURN: The number of CHARACTERS PRINTED..
 */

int handle_write_char(char b, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int X = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[X++] = b;
	buffer[X] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (X = 0; X < width - 1; X++)
			buffer[BUFF_SIZE - X - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - X - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - X - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/*********************** WRITES A NUMBER ***********************/
/**
 * write_number - It PRINTS A STRING..
 * @is_negative: LIST OF ARGUMENTS..
 * @ind: CHARACTER types..
 * @buffer: BUFFER ARRAY to handle print..
 * @flags:  It calculates ACTIVE FLAGS..
 * @width: Get WIDTH.
 * @precision: PRECISION specifier
 * @size: SIZE SPECIFIER..
 *
 * RETURN: The number of CHARACTERS printed.
 */

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - write a number using a BUFFFFER..
 * @ind: The INDEX at which the number starts on the BUFFER..
 * @buffer: BUFFFER..
 * @flags: FLAGS..
 * @width: WIDTH..
 * @prec: PRECISION specifier..
 * @length: number LENGTH..
 * @padd: Padding CHARACTER..
 * @extra_c: extra CHARACTER..
 *
 * RETURN: number of printed CHARACTERS..
 */

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int X, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (X = 1; X < width - length + 1; X++)
			buffer[X] = padd;
		buffer[X] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], X - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], X - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], X - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - It WRITES AN UNSIGNED number
 * @is_negative: The NUM indicating if the num is NEGATIVE..
 * @ind: The index at which the number starts in the buffer
 * @buffer: The ARRAY OF CHARACTERS..
 * @flags: FLAGS SPECIFIERS..
 * @width: WIDTH specifier..
 * @precision: PRECISION specifier..
 * @size: SIZE specifier
 *
 * RETURN: The number of written chars.
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position X */
	int length = BUFF_SIZE - ind - 1, X = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no charACTER is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (X = 0; X < width - length; X++)
			buffer[X] = padd;

		buffer[X] = '\0';

		if (flags & F_MINUS) /* Assign EXTRA char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], X));
		}
		else /* Assign EXTRA char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], X) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - write a MEMORY ADDRESS..
 * @buffer: ARRAYS of chars..
 * @ind: The INDEX at which the number starts in the BUFFER..
 * @length: LENGTH of number..
 * @width: WIDTH SPECIFIER..
 * @flags: flags SPECIFIER..
 * @padd: char representing THE PADDING..
 * @extra_c: char representing extra CHARACTER..
 * @padd_start: The INDEX at which PADDING should start..
 *
 * RETURN: The number of written chars.
 */

int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int X;

	if (width > length)
	{
		for (X = 3; X < width - length + 3; X++)
			buffer[X] = padd;
		buffer[X] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of BUFFER */
		{
			buffer[--ind] = 'X';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], X - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'X';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], X - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of PADD */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'y';
			return (write(1, &buffer[padd_start], X - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'y';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
