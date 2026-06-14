/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:53:55 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 14:28:12 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (env->value)
			arr[i] = ft_strjoin(tmp, env->value);
		else
			arr[i] = ft_strdup(tmp);
		free(tmp);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	update_env(t_env *env, char *key, char *value)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
	env_add_back(&env, env_new(key, value));
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
