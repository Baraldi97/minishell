/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 21:39:43 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 20:52:51 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(int write_fd, t_redir *redir, t_shell *sh)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		if (redir->expand)
		{
			tmp = expand_line(line, sh);
			strip_markers(tmp);
			free(line);
			line = tmp;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	create_heredoc(t_redir *redir, t_shell *sh)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	heredoc_loop(pipefd[1], redir, sh);
	close(pipefd[1]);
	return (pipefd[0]);
}
