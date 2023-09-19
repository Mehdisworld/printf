#include "main.h"

/**
 * handle_write_char - write a string
 * @c: char
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width.
 * @prec: precesion
 * @sz: Size
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int prec, int sz)
{
	int i = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(sz);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}


/**
 * write_number - Prints a string
 * @is_negative: Arguments
 * @indx: index
 * @buffer: Buffer
 * @flags:  Flags
 * @width: width
 * @prec: precesion
 * @sz: Size
 *
 * Return: Number of chars writted.
 */
int write_number(int is_negative, int indx, char buffer[],
	int flags, int width, int prec, int sz)
{
	int lgth = BUFF_SIZE - indx - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(sz);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(indx, buffer, flags, width, prec,
		lgth, padd, extra_ch));
}

/**
 * write_num - Print a number
 * @indx: Index
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision
 * @lgth: Length
 * @padd: Pading
 * @ext_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int indx, char buffer[],
	int flags, int width, int prec,
	int lgth, char padd, char ext_c)
{
	int i, padd_start = 1;

	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0' && width == 0)
		return (0);
	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		buffer[indx] = padd = ' ';
	if (prec > 0 && prec < lgth)
		padd = ' ';
	while (prec > lgth)
		buffer[--indx] = '0', lgth++;
	if (ext_c != 0)
		lgth++;
	if (width > lgth)
	{
		for (i = 1; i < width - lgth + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (ext_c)
				buffer[--indx] = ext_c;
			return (write(1, &buffer[indx], lgth) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (ext_c)
				buffer[--indx] = ext_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[indx], lgth));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (ext_c)
				buffer[--padd_start] = ext_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[indx], lgth - (1 - padd_start)));
		}
	}
	if (ext_c)
		buffer[--indx] = ext_c;
	return (write(1, &buffer[indx], lgth));
}


/**
 * write_unsgnd - Function to write unsigned number
 * @is_negative: is num negative
 * @indx: Index starting the buffer
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @prec: Precision
 * @sz: Size
 * Return: Number of characters
 */
int write_unsgnd(int is_negative, int indx,
	char buffer[],
	int flags, int width, int prec, int sz)
{
	int lgth = BUFF_SIZE - indx - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(sz);

	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		return (0);

	if (prec > 0 && prec < lgth)
		padd = ' ';

	while (prec > lgth)
	{
		buffer[--indx] = '0';
		lgth++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > lgth)
	{
		for (i = 0; i < width - lgth; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[indx], lgth) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[indx], lgth));
		}
	}

	return (write(1, &buffer[indx], lgth));
}

/**
 * write_pointer - Function to write memory address
 * @buffer: Chars array
 * @indx: Index starting the buffer
 * @lgth: Length
 * @width: Width
 * @flags: Flags
 * @padd: Padding char
 * @ext_c: Extra char
 * @padd_start: Padding index
 * Return: Number of written chars
 */
int write_pointer(char buffer[], int indx, int lgth,
	int width, int flags, char padd, char ext_c, int padd_start)
{
	int i;

	if (width > lgth)
	{
		for (i = 3; i < width - lgth + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (ext_c)
				buffer[--indx] = ext_c;
			return (write(1, &buffer[indx], lgth) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (ext_c)
				buffer[--indx] = ext_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[indx], lgth));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (ext_c)
				buffer[--padd_start] = ext_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[indx], lgth - (1 - padd_start) - 2));
		}
	}
	buffer[--indx] = 'x';
	buffer[--indx] = '0';
	if (ext_c)
		buffer[--indx] = ext_c;
	return (write(1, &buffer[indx], BUFF_SIZE - indx - 1));
}


