/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:18:52 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 21:08:02 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	run_in_child(t_command *cmd, t_shell *sh)
{
	char	*path;

	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, sh));
	path = find_path(cmd->args[0], sh->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->args, env_to_array(sh->env));
	exec_error(cmd->args[0]);
}

static	void	child_in_pipe(t_command *cmd, t_shell *sh, int prev, int *pp)
{
	if (prev != -1)
	{
		dup2(prev, STDIN_FILENO);
		close(prev);
	}
	if (cmd->next)
	{
		dup2(pp[1], STDOUT_FILENO);
		close(pp[0]);
		close(pp[1]);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_redirections(cmd, sh) == -1)
		exit(1);
	run_in_child(cmd, sh);
}

static	int	wait_all(pid_t last_pid)
{
	int		status;
	int		code;
	pid_t	wpid;

	code = 0;
	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			code = WEXITSTATUS(status);
		else if (wpid == last_pid && WIFSIGNALED(status))
			code = 128 + WTERMSIG(status);
		wpid = waitpid(-1, &status, 0);
	}
	return (code);
}

static	void	pipe_iteration(t_command *cur, t_shell *sh, t_pipe *p)
{
	pid_t	pid;

	if (cur->next)
		pipe(p->pp);
	pid = fork();
	if (pid == 0)
		child_in_pipe(cur, sh, p->prev, p->pp);
	p->last = pid;
	if (p->prev != -1)
		close(p->prev);
	if (cur->next)
	{
		close(p->pp[1]);
		p->prev = p->pp[0];
	}
}

void	exec_pipeline(t_command *cmds, t_shell *sh)
{
	t_command	*cur;
	t_pipe		p;

	p.prev = -1;
	p.last = -1;
	cur = cmds;
	signals_exec_mode();
	while (cur)
	{
		pipe_iteration(cur, sh, &p);
		cur = cur->next;
	}
	sh->exit_status = wait_all(p.last);
	setup_signals();
}
