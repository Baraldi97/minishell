/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:45:02 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 14:28:28 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_valid_key(char *key)
{
	int	i;

	if (!key[0] || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static	int	export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static	int	export_one(char *arg, t_env *env)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!is_valid_key(arg))
			return (export_error(arg));
		return (0);
	}
	key = ft_substr(arg, 0, eq - arg);
	if (!is_valid_key(key))
	{
		free(key);
		return (export_error(arg));
	}
	update_env(env, key, eq + 1);
	free(key);
	return (0);
}

int	builtin_export(char **args, t_env *env)
{
	int	i;
	int	status;

	if (!args[1])
		return (export_list(env));
	i = 1;
	status = 0;
	while (args[i])
	{
		if (export_one(args[i], env))
			status = 1;
		i++;
	}
	return (status);
}
