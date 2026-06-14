/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:18:20 by baraldi           #+#    #+#             */
/*   Updated: 2026/06/13 20:31:02 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == TOKEN_PIPE)
		return (ft_printf ("syntax error near unexpected token '|'\n"), -1);
	while (current)
	{
		if (current->type == TOKEN_PIPE && current->next
			&& (current->next->type == TOKEN_PIPE
				|| current->next->type == TOKEN_EOF))
			return (ft_printf ("syntax error near unexpected token '|'\n"),
				-1);
		if ((current->type == TOKEN_REDIR_IN
				|| current->type == TOKEN_REDIR_OUT
				|| current->type == TOKEN_HEREDOC
				|| current->type == TOKEN_APPEND) && current->next
			&& current->next->type != TOKEN_WORD)
			return (ft_printf
				("syntax error near unexpected token 'newline'\n"),
				-1);
		current = current->next;
	}
	return (0);
}

t_command	*parse(t_token *tokens)
{
	t_command	*cmds;
	t_command	*cmd;

	cmds = NULL;
	while (tokens && tokens->type != TOKEN_EOF)
	{
		cmd = parse_command(&tokens);
		if (!cmd)
		{
			free_commands(cmds);
			return (NULL);
		}
		add_command(&cmds, cmd);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}

t_command	*parse_command(t_token **tokens)
{
	t_command	*cmd;

	cmd = new_command();
	if (!cmd)
		return (NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_EOF)
	{
		if ((*tokens)->type == TOKEN_WORD)
			parse_args(tokens, cmd);
		else
			parse_redir(tokens, cmd);
	}
	return (cmd);
}

void	parse_args(t_token **tokens, t_command *cmd)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup((*tokens)->value);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	*tokens = (*tokens)->next;
}

void	parse_redir(t_token **tokens, t_command *cmd)
{
	t_redir	*redir;

	redir = new_redir((*tokens)->type, NULL);
	if (!redir)
		return ;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		redir->file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	add_redir(&cmd->redirs, redir);
}
