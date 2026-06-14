/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:58:37 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 13:48:22 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_shell *sh)
{
	unsigned char	code;

	ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		code = sh->exit_status;
		free_all(sh);
		exit(code);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(sh);
		exit(2);
	}
	if (args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	code = (unsigned char)ft_atoi(args[1]);
	free_all(sh);
	exit(code);
}
