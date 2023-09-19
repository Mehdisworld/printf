#include "main.h"

/**
 * print_unsigned - Function to print an unsigned number
 * @flags:  Calculate active flags
 * @types: List a of arguments
 * @width: Fet width
 * @prec: Precision specification
 * @sz: Size specifier
 * @buffer: Buffer array to handle print
 * Return: Number of chars printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int sz)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, sz));
}

/**
 * print_octal - Function to print unsigned number in octal notation
 * @width: get width
 * @sz: Size specifier
 * @prec: Precision specification
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculate active flags
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int sz)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, sz));
}

/**
 * print_hexadecimal - Function to print unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @prec: Precision specification
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @sz: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int sz)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, sz));
}

/**
 * print_hexa_upper - Function to print unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @sz: Size specifier
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: Precision specification
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int sz)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, sz));
}

/**
 * print_hexa - Function to print a hexadecimal number upper or lower
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @width: Get width
 * @prec: Precision specification
 * @sz: Size specifier
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int sz)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, sz));
}
