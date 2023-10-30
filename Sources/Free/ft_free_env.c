/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:55:40 by snourry           #+#    #+#             */
/*   Updated: 2022/11/01 17:16:38 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	ft_free_str(t_env *env)
{
	free(env->key);
	env->key = NULL;
	if (env->value)
		free(env->value);
	env->value = NULL;
}

void	ft_free_env(t_program *program)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = program->env;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		ft_free_str(tmp1);
		free(tmp1);
		tmp1 = NULL;
	}
}

void	ft_free_char_env(t_program *program)
{
	char	**env;
	int		i;

	env = program->char_env;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}
