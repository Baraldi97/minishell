/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:57:29 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 21:30:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_char(char *str, int *i, char *quote, t_shell *sh)
{
	char	*piece;

	if (*quote == 0 && (str[*i] == '\'' || str[*i] == '"'))
		return (*quote = str[(*i)++], ft_strdup(""));
	if (*quote != 0 && str[*i] == *quote)
		return (*quote = 0, (*i)++, ft_strdup(""));
	if (str[*i] == '$' && *quote == '"')
		return (get_var_value(str, i, sh));
	if (str[*i] == '$' && *quote == 0)
		return (mark_whitespace(get_var_value(str, i, sh)));
	piece = ft_substr(str, *i, 1);
	(*i)++;
	return (piece);
}

char	*expand_line(char *str, t_shell *sh)
{
	int		i;
	char	quote;
	char	*result;

	result = ft_strdup("");
	i = 0;
	quote = 0;
	while (str[i])
		result = append_str(result, expand_char(str, &i, &quote, sh));
	return (result);
}

void	expand_redirs(t_redir *redir, t_shell *sh)
{
	char	*clean;

	while (redir)
	{
		clean = expand_line(redir->file, sh);
		strip_markers(clean);
		free(redir->file);
		redir->file = clean;
		redir = redir->next;
	}
}

void	expand_command(t_command *cmd, t_shell *sh)
{
	char	**result;
	char	**words;
	char	*clean;
	int		i;

	result = NULL;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		clean = expand_line(cmd->args[i], sh);
		words = split_expanded(clean);
		if (!words && had_quotes(cmd->args[i]))
			words = empty_word();
		free(clean);
		result = append_words(result, words);
		i++;
	}
	free_args_array(cmd->args);
	cmd->args = result;
	expand_redirs(cmd->redirs, sh);
}

void	expand(t_command *cmds, t_shell *sh)
{
	while (cmds)
	{
		expand_command(cmds, sh);
		cmds = cmds->next;
	}
}
