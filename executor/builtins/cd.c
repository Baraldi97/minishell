/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:28:30 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 11:29:20 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_target(char **args, t_env *env)
{
	char	*home;

	if (!args[1])
	{
		home = get_env_value(env, "HOME");
		if (!home)
			ft_putstr_fd("cd: HOME not set\n", 2);
		return (home);
	}
	return (args[1]);
}

int	builtin_cd(char **args, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target;

	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	target = cd_target(args, env);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_env(env, "OLDPWD", oldpwd);
	update_env(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
