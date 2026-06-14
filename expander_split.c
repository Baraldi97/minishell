/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 22:40:00 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 22:40:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts how many non-empty words a marked string splits into.
** The marker '\x01' separates words produced by unquoted $VAR expansion.
*/
static int	count_words(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == '\1')
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != '\1')
				i++;
		}
	}
	return (count);
}

/*
** Extracts the next word from a marked string starting at *i,
** skipping leading markers. Returns a freshly allocated word.
*/
static char	*next_word(char *s, int *i)
{
	int	start;

	while (s[*i] == '\1')
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\1')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

/*
** Splits a marked expanded string into an array of words.
** If the string is empty after splitting (e.g. an unset var alone),
** returns NULL so the caller drops the argument entirely.
*/
char	**split_expanded(char *marked)
{
	char	**words;
	int		count;
	int		i;
	int		w;

	count = count_words(marked);
	if (count == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	w = 0;
	while (w < count)
		words[w++] = next_word(marked, &i);
	words[w] = NULL;
	return (words);
}

static int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

/*
** Appends the NULL-terminated list 'words' onto 'dst', freeing both
** outer arrays (the strings are moved, not copied). Returns the merged
** array. 'words' may be NULL (nothing to append).
*/
char	**append_words(char **dst, char **words)
{
	char	**merged;
	int		n;
	int		m;
	int		i;

	n = array_len(dst);
	m = array_len(words);
	merged = malloc(sizeof(char *) * (n + m + 1));
	if (!merged)
		return (dst);
	i = -1;
	while (++i < n)
		merged[i] = dst[i];
	i = -1;
	while (++i < m)
		merged[n + i] = words[i];
	merged[n + m] = NULL;
	free(dst);
	free(words);
	return (merged);
}
