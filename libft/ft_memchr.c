/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:00:04 by rcosta            #+#    #+#             */
/*   Updated: 2025/08/06 15:00:04 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*var_s;
	size_t			i;

	var_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (var_s[i] == (unsigned char) c)
			return (&var_s[i]);
		i++;
	}
	return (NULL);
}
