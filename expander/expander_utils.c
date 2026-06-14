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

/*
** Replaces every maximal run of whitespace in an unquoted expansion
** with a single '\1' marker so the value can be word-split later.
** Frees the input and returns a new string.
*/
char	*mark_whitespace(char *value)
{
	char	*result;
	char	*piece;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == ' ' || value[i] == '\t')
		{
			result = append_str(result, ft_strdup("\1"));
			while (value[i] == ' ' || value[i] == '\t')
				i++;
		}
		else
		{
			piece = ft_substr(value, i, 1);
			result = append_str(result, piece);
			i++;
		}
	}
	free(value);
	return (result);
}
