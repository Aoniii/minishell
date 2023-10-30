/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:02:58 by snourry           #+#    #+#             */
/*   Updated: 2022/11/10 18:11:25 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "libft.h"

static size_t	ft_index(char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '=')
		i++;
	return (i);
}

static t_env	*ft_create(char **env, int i, t_env *prev)
{
	t_env	*e;
	int		index;

	if (!env[i])
		return (NULL);
	e = malloc(sizeof(t_env));
	if (!e)
		return (NULL);
	index = ft_index(env[i]);
	e->prev = prev;
	e->key = ft_substr(env[i], 0, index);
	e->value = ft_substr(env[i], index + 1, ft_strlen(env[i]) - index - 1);
	e->next = ft_create(env, i + 1, e);
	return (e);
}

t_env	*ft_create_env(char **env)
{
	t_env	*e;

	e = ft_create(env, 0, NULL);
	return (e);
}

char	*ft_get_value(t_env *env, char *key, bool nullValue)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	if (nullValue)
		return (NULL);
	return ("");
}
