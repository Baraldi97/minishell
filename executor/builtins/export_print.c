/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 16:00:00 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/14 16:00:00 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_array(t_env **arr, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = -1;
	while (++i < count - 1)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

static t_env	**env_sorted_array(t_env *env)
{
	t_env	**arr;
	int		count;
	int		i;

	count = env_size(env);
	arr = malloc(sizeof(t_env *) * (count + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		arr[i] = env;
		env = env->next;
	}
	arr[count] = NULL;
	sort_env_array(arr, count);
	return (arr);
}

static void	print_declare(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}

int	export_list(t_env *env)
{
	t_env	**arr;
	int		i;

	arr = env_sorted_array(env);
	if (!arr)
		return (1);
	i = -1;
	while (arr[++i])
		print_declare(arr[i]);
	free(arr);
	return (0);
}
