/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 22:30:00 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 22:30:00 by rcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_shell *sh, char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
	sh->exit_status = 127;
}

void	exec_error(char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (errno == ENOENT)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	}
	if (errno == EISDIR)
		ft_putstr_fd("Is a directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd("Permission denied\n", 2);
	else
		ft_putstr_fd("command not found\n", 2);
	exit(126);
}

void	wait_child(pid_t pid, t_shell *sh)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sh->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}
