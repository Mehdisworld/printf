#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024


#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int prec, int sz);


#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4

#define F_HASH 8
#define F_SPACE 16



int print_int(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_binary(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_octal(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int prec, int sz);
int print_char(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_string(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_percent(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_pointer(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int print_reverse(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int prec, int sz);
int handle_write_char(char c, char buffer[],
	int flags, int width, int prec, int sz);
int write_number(int is_positive, int indx, char buffer[],
	int flags, int width, int prec, int sz);
int write_num(int indx, char bff[], int flags, int width, int prec,
	int lgth, char padd, char ext_c);
int write_pointer(char buffer[], int indx, int lgth,
	int width, int flags, char padd, char ext_c, int padd_start);
int write_unsgnd(int is_negative, int indx,
char buffer[],
	int flags, int width, int prec, int sz);
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int sz);
long int convert_size_unsgnd(unsigned long int num, int sz);

#endif
