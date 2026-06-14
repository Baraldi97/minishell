/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 21:38:40 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 20:55:11 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	open_redir(t_redir *redir, t_shell *sh)
{
	if (redir->type == TOKEN_REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == TOKEN_REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == TOKEN_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == TOKEN_HEREDOC)
		return (create_heredoc(redir, sh));
	return (-1);
}

static	int	apply_redir(t_redir *redir, t_shell *sh)
{
	int	fd;

	fd = open_redir(redir, sh);
	if (fd == -1)
		return (perror(redir->file), -1);
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirections(t_command *cmd, t_shell *sh)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (apply_redir(redir, sh) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
