#include "main.h"

/**
 * print_char - Function to print a character
 * @types: List arguments
 * @buffer: Buffer array to handle printing
 * @flags:  Calculate active flags
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, prec, sz));
}

/**
 * print_string - Function that prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	int lgth = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(sz);
	if (str == NULL)
	{
		str = "(null)";
		if (prec >= 6)
			str = "      ";
	}

	while (str[lgth] != '\0')
		lgth++;

	if (prec >= 0 && prec < lgth)
		lgth = prec;

	if (width > lgth)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lgth);
			for (i = width - lgth; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - lgth; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], lgth);
			return (width);
		}
	}

	return (write(1, str, lgth));
}

/**
 * print_percent - Function that prints a percent sign
 * @types: The list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(sz);
	return (write(1, "%%", 1));
}

/**
 * print_int - Function that prints int
 * @types: The list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, sz);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, prec, sz));
}


/**
 * print_binary - Function that prints an unsigned number
 * @types: The list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Numbers of characters printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int prec, int sz)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(sz);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
