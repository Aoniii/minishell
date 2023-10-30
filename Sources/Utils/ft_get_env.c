/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:46:05 by snourry           #+#    #+#             */
/*   Updated: 2022/11/06 15:45:32 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "libft.h"
#include <stdio.h>

int	ft_env_size(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*ft_get_line(char *key, char *value)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	line = ft_strjoin(tmp, value);
	free(tmp);
	tmp = NULL;
	return (line);
}

char	**ft_get_env(t_env *env)
{
	t_env	*e;
	char	**s;
	int		i;

	i = 1;
	e = env;
	while (e)
	{
		if (e->value)
			i++;
		e = e->next;
	}
	s = malloc(sizeof(char *) * i);
	if (!s)
		return (NULL);
	s[i - 1] = NULL;
	e = env;
	i = 0;
	while (e)
	{
		if (e->value)
			s[i++] = ft_get_line(e->key, e->value);
		e = e->next;
	}
	return (s);
}
