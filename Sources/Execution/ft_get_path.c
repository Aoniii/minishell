/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:07:34 by snourry           #+#    #+#             */
/*   Updated: 2022/11/03 18:22:07 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_get_path2(char **env_path)
{
	int	i;

	i = -1;
	while (env_path[++i])
	{
		free(env_path[i]);
		env_path[i] = NULL;
	}
}

char	*ft_get_path(t_env *env, char *cmd)
{
	char	**env_path;
	char	*str;
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (!ft_get_value(env, "PATH", true))
		return (NULL);
	env_path = ft_split(ft_get_value(env, "PATH", false), ':');
	str = ft_strjoin("/", cmd);
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], str);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	ft_get_path2(env_path);
	free(str);
	free(env_path);
	return (path);
}
