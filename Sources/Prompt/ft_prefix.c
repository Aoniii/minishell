/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:32:21 by snourry           #+#    #+#             */
/*   Updated: 2022/11/10 18:30:04 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_index(char *pwd)
{
	int	i;

	i = ft_strlen(pwd) - 1;
	while (i && pwd[i] != '/')
		i--;
	return (i);
}

char	*ft_prefix(t_env *env)
{
	char	*user;
	char	*comp;
	char	*tmp;
	char	*final;

	user = ft_strjoin(ft_get_value(env, "USER", false), "@");
	comp = ft_substr(ft_get_value(env, "SESSION_MANAGER", false), 6, 3);
	tmp = ft_strjoin(user, comp);
	free(user);
	user = NULL;
	free(comp);
	comp = NULL;
	final = ft_strjoin(tmp, " \e[36m");
	free(tmp);
	tmp = NULL;
	return (final);
}

char	*ft_pwd(t_program *program)
{
	char	*folder;
	int		i;

	if (program->folder)
	{
		free(program->folder);
		program->folder = NULL;
	}
	folder = ft_get_value(program->env, "PWD", false);
	i = ft_index(folder);
	if (i)
		program->folder = ft_substr(folder, i + 1, ft_strlen(folder) - i - 1);
	else
		program->folder = ft_strdup(folder);
	return (program->folder);
}
