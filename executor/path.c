/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 21:01:06 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 14:25:56 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*build_candidate(char *dir, char *cmd)
{
	char	*with_slash;
	char	*full;

	with_slash = ft_strjoin(dir, "/");
	if (!with_slash)
		return (NULL);
	full = ft_strjoin(with_slash, cmd);
	free(with_slash);
	return (full);
}

static	char	*search_dirs(char **dirs, char *cmd)
{
	char	*candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = build_candidate(dirs[i], cmd);
		if (candidate && access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	**dirs;
	char	*path_value;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_value = get_env_value(env, "PATH");
	if (!path_value)
		return (NULL);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (NULL);
	result = search_dirs(dirs, cmd);
	free_split(dirs);
	return (result);
}
