/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:30:00 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 21:30:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

static char	*get_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*get_var_value(char *str, int *i, t_shell *sh)
{
	char	*name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->exit_status));
	}
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	name = get_var_name(str, i);
	value = get_env_value(sh->env, name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*append_str(char *result, char *piece)
{
	char	*joined;

	joined = ft_strjoin(result, piece);
	free(result);
	free(piece);
	return (joined);
}
