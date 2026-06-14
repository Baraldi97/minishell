/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 22:45:00 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 22:45:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** Returns 1 if the raw argument contains a quote character. Such a word
** must survive even if it expands to nothing (e.g. echo "" keeps "").
*/
int	had_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/*
** Builds a one-element array holding an empty string, used to preserve
** a quoted word that expanded to nothing (e.g. echo "").
*/
char	**empty_word(void)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("");
	arr[1] = NULL;
	return (arr);
}

/*
** Removes split markers in place from a string (used for redirection
** targets and heredoc bodies, which are never word-split).
*/
void	strip_markers(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\1')
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
