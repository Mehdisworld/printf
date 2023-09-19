#include "main.h"

/**
 * print_pointer - Function to Print value of pointer variable
 * @types: List of arguments
 * @sz: Size specifier
 * @width: get width
 * @buffer: Buffer array to handle print
 * @prec: Precision specifier
 * @flags:  Calculates active flags
 * Return: Number of chars printed
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	char ext_c = 0, padd = ' ';
	int indx = BUFF_SIZE - 2, lgth = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(sz);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(prec);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[indx--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		lgth++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ext_c = '+', lgth++;
	else if (flags & F_SPACE)
		ext_c = ' ', lgth++;

	indx++;

	return (write_pointer(buffer, indx, lgth,
		width, flags, padd, ext_c, padd_start));
}

/**
 * print_non_printable - Function to print ascii hexa of non printable chars
 * @types: Lista of arguments
 * @flags:  Calculates active flags
 * @prec: Precision specification
 * @sz: Size specifier
 * @buffer: Buffer array to handle print
 * @width: Get width
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(sz);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - Function to print reverse string
 * @types: List of arguments
 * @flags: Calculates active flags
 * @width: get width
 * @prec: Precision specification
 * @sz: Size specifier
 * @buffer: Buffer array to handle print
 * Return: Numbers of chars printed
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(sz);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(prec);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Function to print a string in rot13
 * @types: List of arguments
 * @prec: Precision specification
 * @flags: Calculates active flags
 * @width: get width
 * @sz: Size specifier
 * @buffer: Buffer array to handle print
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(sz);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
