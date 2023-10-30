/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:50:04 by snourry           #+#    #+#             */
/*   Updated: 2022/10/12 17:50:04 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_env	*ft_get_last(t_env *env)
{
	t_env	*env1;

	env1 = env;
	while (env1->next)
		env1 = env1->next;
	return (env1);
}

t_env	*ft_get(t_env *env, char *key)
{
	t_env	*env1;

	env1 = env;
	while (env1 && ft_strcmp(env1->key, key) != 0)
		env1 = env1->next;
	return (env1);
}

static bool	ft_have_key(t_env *env, char *key)
{
	t_env	*env1;

	env1 = env;
	while (env1)
	{
		if (ft_strcmp(env1->key, key) == 0)
			return (true);
		env1 = env1->next;
	}
	return (false);
}

void	ft_add_env(t_env *e, char *key, char *value)
{
	t_env	*env;
	t_env	*last;

	if (!ft_have_key(e, key))
	{
		env = malloc(sizeof(t_env));
		if (!env)
			return ;
		env->key = key;
		env->next = NULL;
		env->value = value;
		last = ft_get_last(e);
		last->next = env;
		env->prev = last;
	}
	else
	{
		env = ft_get(e, key);
		if (env->value)
			free(env->value);
		env->value = value;
		free(key);
	}
}
