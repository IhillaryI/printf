#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int chspe(const char *fmt);

int _printf(const char *format, ...)
{
	unsigned int count, i, j;
	char c, *s;
	va_list ap;

	count = 0;
	if (!(chspe(format) == -1))
	{
		count = chspe(format);
		write(1, format, count);
		return (count);
	}
	else
	{
		va_start(ap, format);
		i = 0;
		while (*(format + i))
		{
			if (*(format + i) == '%')
			{ 
				/*++i;*/
				if (*(format + i + 1) == 'c')
				{
					++i;
					++count;
					c = va_arg(ap, int);
					write(1, &c, 1);
				}
				else if (*(format + i + 1) == 's')
				{
					++i;
					j = 0;
					s = va_arg(ap, char *);
					while (*(s + j))
						++j;
					count += j;
					write(1, s, j);
				}
				else
					write(1, (format + i), 1);
				++i;
			}
			else
			{
				write(1, (format + i), 1);
				++i;
				count++;
			}
		}
		va_end(ap);
	}

	return (count);
}

/**
* chspe - checks if specifier in fmt
* @fmt: formatted string
* Return: number of characters if no (%), else return -1;
*/
int chspe(const char *fmt)
{
	unsigned int i;

	i = 0;
	while (*(fmt + i))
	{
		if (*(fmt + i) == '%')
		{
			i = -1;
			return (i);
		}
		++i;
	}

	return (i);
}
