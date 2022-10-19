#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>


void
fmt_spec(va_list ap, const char *fmt, unsigned int *i, unsigned int *count);

char *itoa(int value);

int digit(int value);

unsigned int len(const char *s);


/**
* _printf - printf formatted string
* @format: formatted string
* Return: count of chars printed
*/

int _printf(const char *format, ...)
{

	unsigned int count, i;
	va_list ap;

	if (format == NULL)
		return (-1);
	if (len(format) == 1 && *(format) == '%')
		return (-1);

	count = 0;
	va_start(ap, format);
	i = 0;
	while (*(format + i))
	{

		if (*(format + i) == '%')
		{

			fmt_spec(ap, format, &i, &count);

			++i;

		}
		else
		{

			count++;

			write(1, (format + i), 1);

			++i;

		}

	}

	va_end(ap);



	return (count);

}



/**
* fmt_spec - print specifier
* @fmt: format string
* @ap: type of va_list
* @i: unsigned int
* @count: unsigned int
*/
void

fmt_spec(va_list ap, const char *fmt, unsigned int *i, unsigned int *count)
{
	char *s, c;
	int j, k;


	j = *i + 1;
	while (*(fmt + j) == ' ')
		++j;

	if (*(fmt + j) == 's')
	{
		s = va_arg(ap, char *);
		if (s != NULL)
		{
			k = 0;

			while (*(s + k))
				++k;
			*count += k;

			write(1, s, k);

		}
		else
		{
			*count += 6;
			write(1, "(null)", 6);
		}

		*i = j;
	}
	else if (*(fmt + j) == 'c')
	{
		c = va_arg(ap, int);

		write(1, &c, 1);

		++*count;

		*i = j;
	}
	else if (*(fmt + j) == 'd' || *(fmt + j) == 'i')
	{
		*count += digit(va_arg(ap, int));

		*i = j;
	}
	else if (*(fmt + j) == '%')
	{
		write(1, (fmt + j), 1);

		*i = j;

		++*count;
	}
	else
	{
		write(1, (fmt + *i), 1);

		++*count;
	}
}



/**
* itoa - convert an int to a string
* @value: integer value
* Return: a string of numbers
*/

char *itoa(int value)
{
	unsigned int count;
	int copy, sign, size, int_min;
	char *str;

	count = 0;
	sign = 0;
	if (value == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else if (value == INT_MIN)
	{
		int_min = 1;
		value += 1;
		value *= -1;
		sign = 1;
	}
	else if (value < 0)
	{
		sign = 1;
		value *= -1;
	}
	copy = value;
	while (copy)
	{
		copy /= 10;
		++count;
	}
	copy = value;
	size = count + sign;
	str = malloc(sizeof(char) * (size + 1));
	if (str != NULL)
	{
		str[size] = '\0';
		while (copy)
		{
			str[--size] = (copy % 10) + '0';
			copy /= 10;
		}
		if (sign)
			str[0] = '-';
		if (int_min)
			str[10] = str[10] + 1;
	}
	return (str);
}



/**
* digit - handle digit spec
* @value: integer value
* Return: the string count, 0 if s is NULL
*/

int digit(int value)
{
	char *s;
	int k;

	k = 0;
	s = itoa(value);
	if (s != NULL)
	{
		while (*(s + k) != '\0')
			++k;

		write(1, s, (value == INT_MAX) ? 10 : k);
		free(s);
		if (value == INT_MAX)
			return (10);
		else
			return (k);
	}
	return (0);
}


/**
* len - count the length of a string
* @s: string to count
* Return: length of string
*/
unsigned int len(const char *s)
{
	unsigned int i;
/* previously made an error here */
	i = 0;
	while (*(s + i))
		++i;
	return (i);
}
