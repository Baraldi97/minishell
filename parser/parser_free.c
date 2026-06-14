/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:59:48 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 20:30:55 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_commands(t_command *cmds)
{
	t_command	*aux;

	while (cmds)
	{
		aux = cmds->next;
		free_args(cmds->args);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = aux;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*aux;

	while (redirs)
	{
		aux = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = aux;
	}
}
