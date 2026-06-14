/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:07:54 by baraldi           #+#    #+#             */
/*   Updated: 2026/06/13 20:30:58 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->args = NULL;
	new->redirs = NULL;
	return (new);
}

void	add_command(t_command **list, t_command *new)
{
	t_command	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_redir	*new_redir(t_token_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	if (file)
		new->file = ft_strdup(file);
	else
		new->file = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_redir(t_redir **list, t_redir *new)
{
	t_redir	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	else
		current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
	return ;
}
