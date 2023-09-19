#include "main.h"

/**
 * handle_print - Prints a given argument while considering its data type
 * @fmt: Format of a string
 * @list: The arguments list
 * @indx: index
 * @buffer: Buffer array
 * @flags: get flags
 * @width: get width.
 * @prec: Precision
 * @sz: Size
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *indx, va_list list, char buffer[],
	int flags, int width, int prec, int sz)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*indx] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, prec, sz));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*indx] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*indx - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*indx);
			while (fmt[*indx] != ' ' && fmt[*indx] != '%')
				--(*indx);
			if (fmt[*indx] == ' ')
				--(*indx);
			return (1);
		}
		unknow_len += write(1, &fmt[*indx], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

