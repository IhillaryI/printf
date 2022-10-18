#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void
fmt_spec(va_list ap, const char *fmt, unsigned int *i, unsigned int *count);
char *itoa(int value);
int digit(int value);

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
		return (0);
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
		k = 0;
		while (*(s + k))
			++k;
		*count += k;
		write(1, s, k);
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
	int copy;
	char *str;

	count = 0;
	copy = value;
	while (copy)
	{
		copy /= 10;
		++count;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (str != NULL)
	{
		str[count] = '\0';
		while (value)
		{
			str[--count] = (value % 10) + '0';
			value /= 10;
		}
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
		while (*(s + k))
			++k;
		write(1, s, k);
		free(s);
		return (k);
	}
	return (0);
}
