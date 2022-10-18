#include <unistd.h>
#include <stdarg.h>

/**
* _printf - printf formatted string
* @format: formatted string
* Return: count of chars printed
*/
int _printf(const char *format, ...)
{
	unsigned int count, i, j, k;
	char c, *s;
	va_list ap;

	count = 0;
	va_start(ap, format);
	i = 0;
	while (*(format + i))
	{
		if (*(format + i) == '%')
		{
			j = i + 1;
			while (*(format + j) == ' ')
				++j;
			if (*(format + j) == 's')
			{
				s = va_arg(ap, char *);
				k = 0;
				while (*(s + k))
					++k;
				count += k;
				write(1, s, k);
				i = j;
			}
			else if (*(format + j) == 'c')
			{
				c = va_arg(ap, int);
				write(1, &c, 1);
				++count;
				i = j;
			}
			else if (*(format + j) == '%')
			{
				write(1, (format + j), 1);
				i = j;
				++count;
			}
			else
			{
				write(1, (format + i), 1);
				++count;
			}
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


