/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:46:51 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 13:47:35 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *sh)
{
	free_env(sh->env);
	free_commands(sh->cmds);
	free_tokens(sh->tokens);
}
