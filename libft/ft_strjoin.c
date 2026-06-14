/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:36:12 by rcosta            #+#    #+#             */
/*   Updated: 2025/08/21 15:54:17 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			size_s1;
	size_t			size_s2;
	size_t			i;
	size_t			j;
	char			*conct;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	conct = malloc(size_s1 + size_s2 + 1);
	if (conct == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		conct[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		conct[i + j] = s2[j];
		j++;
	}
	conct[i + j] = '\0';
	return (conct);
}
