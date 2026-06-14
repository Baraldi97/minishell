/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:58:59 by rcosta            #+#    #+#             */
/*   Updated: 2026/04/09 19:59:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	print_format(char type, va_list args);
int	print_char(int c);
int	print_str(char *s);
int	print_digit(long n, int base, char *base_chars);
int	print_ptr(unsigned long n, char *base_chars);

#endif