/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:49:21 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 13:52:29 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **list, t_env *node)
{
	t_env	*cur;

	if (!*list)
	{
		*list = node;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

t_env	*env_init(char **envp)
{
	t_env	*list;
	char	*key;
	char	*eq;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, eq - envp[i]);
		env_add_back(&list, env_new(key, eq + 1));
		free(key);
		i++;
	}
	return (list);
}
