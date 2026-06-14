/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:21:12 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 14:27:17 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_command *cmd, t_shell *sh)
{
	char	*name;

	name = cmd->args[0];
	if (!ft_strcmp(name, "echo"))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(name, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(name, "env"))
		return (builtin_env(sh->env));
	if (!ft_strcmp(name, "cd"))
		return (builtin_cd(cmd->args, sh->env));
	if (!ft_strcmp(name, "export"))
		return (builtin_export(cmd->args, sh->env));
	if (!ft_strcmp(name, "unset"))
		return (builtin_unset(cmd->args, sh));
	return (builtin_exit(cmd->args, sh));
}
