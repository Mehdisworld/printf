#include "main.h"

/**
 * get_size - Function to calculate the size to cast argument
 * @i: List of arguments to print
 * @format: Formatted string in which to print the arguments
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int cu_i = *i + 1;
	int sz = 0;

	if (format[cu_i] == 'l')
		sz = S_LONG;
	else if (format[cu_i] == 'h')
		sz = S_SHORT;

	if (sz == 0)
		*i = cu_i - 1;
	else
		*i = cu_i;

	return (sz);
}
