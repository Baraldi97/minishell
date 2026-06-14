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

char	*expand_line(char *str, t_shell *sh)
{
	int		i;
	char	quote;
	char	*result;
	char	*piece;

	result = ft_strdup("");
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote != 0 && str[i] == quote)
			quote = (i++, 0);
		else if (str[i] == '$' && quote != '\'')
			result = append_str(result, get_var_value(str, &i, sh));
		else
		{
			piece = ft_substr(str, i, 1);
			result = append_str(result, piece);
			i++;
		}
	}
	return (result);
}

void	expand_redirs(t_redir *redir, t_shell *sh)
{
	char	*clean;

	while (redir)
	{
		clean = expand_line(redir->file, sh);
		free(redir->file);
		redir->file = clean;
		redir = redir->next;
	}
}

void	expand_command(t_command *cmd, t_shell *sh)
{
	int		i;
	char	*clean;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		clean = expand_line(cmd->args[i], sh);
		free(cmd->args[i]);
		cmd->args[i] = clean;
		i++;
	}
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
