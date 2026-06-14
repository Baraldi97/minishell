/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 19:46:10 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 21:07:43 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_process(t_command *cmd, char *path, t_shell *sh)
{
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_redirections(cmd, sh) == -1)
		exit(1);
	envp = env_to_array(sh->env);
	execve(path, cmd->args, envp);
	exec_error(cmd->args[0]);
}

static	void	exec_external(t_command *cmd, t_shell *sh)
{
	pid_t	pid;
	char	*path;

	path = find_path(cmd->args[0], sh->env);
	if (!path)
		return (cmd_not_found(sh, cmd->args[0]));
	signals_exec_mode();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), setup_signals());
	if (pid == 0)
		child_process(cmd, path, sh);
	free(path);
	wait_child(pid, sh);
}

void	execute_cmd(t_command *cmd, t_shell *sh)
{
	int	saved[2];

	if (!cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
	{
		saved[0] = dup(STDIN_FILENO);
		saved[1] = dup(STDOUT_FILENO);
		if (setup_redirections(cmd, sh) != -1)
			sh->exit_status = run_builtin(cmd, sh);
		else
			sh->exit_status = 1;
		dup2(saved[0], STDIN_FILENO);
		dup2(saved[1], STDOUT_FILENO);
		close(saved[0]);
		close(saved[1]);
		return ;
	}
	exec_external(cmd, sh);
}

void	execute(t_command *cmds, t_shell *sh)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	if (cmds->next)
		exec_pipeline(cmds, sh);
	else
		execute_cmd(cmds, sh);
}
