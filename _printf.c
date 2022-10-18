#include <unistd.h>
#include <stdarg.h>

void
fmt_spec(va_list ap, const char *fmt, unsigned int *i, unsigned int *count);


/**
* _printf - printf formatted string
* @format: formatted string
* Return: count of chars printed
*/
int _printf(const char *format, ...)
{
	unsigned int count, i;
	va_list ap;

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
