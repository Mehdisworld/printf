#include "main.h"

/**
 * get_precision - Function to calculate prec for print
 * @i: List of arguments to be printed
 * @list: list of arguments
 * @format: Formatted string to print the arguments
 * Return: Precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int cu_i = *i + 1;
	int prec = -1;

	if (format[cu_i] != '.')
		return (prec);

	prec = 0;

	for (cu_i += 1; format[cu_i] != '\0'; cu_i++)
	{
		if (is_digit(format[cu_i]))
		{
			prec *= 10;
			prec += format[cu_i] - '0';
		}
		else if (format[cu_i] == '*')
		{
			cu_i++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = cu_i - 1;

	return (prec);
}
