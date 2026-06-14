/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:58:42 by rcosta            #+#    #+#             */
/*   Updated: 2026/04/09 19:58:44 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i] != '\0')
		i += print_char(s[i]);
	return (i);
}

int	print_digit(long n, int base, char *base_chars)
{
	int				count;
	unsigned long	un;

	count = 0;
	if (n < 0 && base == 10)
	{
		count += print_char('-');
		un = (unsigned long)(-n);
	}
	else
		un = (unsigned long)n;
	if (un >= (unsigned long)base)
		count += print_digit(un / base, base, base_chars);
	count += print_char(base_chars[un % base]);
	return (count);
}

int	print_ptr(unsigned long n, char *base_chars)
{
	int	count;

	count = 0;
	if (!n)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += print_digit(n, 16, base_chars);
	return (count);
}

int	print_format(char type, va_list args)
{
	int		count;
	char	*hex_lower;
	char	*hex_upper;

	hex_lower = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	count = 0;
	if (type == 'c')
		count += print_char(va_arg(args, int));
	else if (type == 's')
		count += print_str(va_arg(args, char *));
	else if (type == 'p')
		count += print_ptr(va_arg(args, unsigned long), hex_lower);
	else if (type == 'd' || type == 'i')
		count += print_digit(va_arg(args, int), 10, "0123456789");
	else if (type == 'u')
		count += print_digit(va_arg(args, unsigned int), 10, "0123456789");
	else if (type == 'x')
		count += print_digit(va_arg(args, unsigned int), 16, hex_lower);
	else if (type == 'X')
		count += print_digit(va_arg(args, unsigned int), 16, hex_upper);
	else if (type == '%')
		count += print_char('%');
	return (count);
}
