/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:45:15 by snourry           #+#    #+#             */
/*   Updated: 2022/10/29 19:45:15 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void	ft_free_unset(t_env *env)
{
	free(env->key);
	env->key = NULL;
	if (env->value)
		free(env->value);
	env->value = NULL;
	free(env);
	env = NULL;
}

void	ft_builtin_unset(t_program *program, t_cmd *cmd)
{
	t_env	*env;
	int		i;

	i = 1;
	while (cmd->exec[i])
	{
		env = ft_get(program->env, cmd->exec[i]);
		if (env && ft_strcmp(cmd->exec[i], "_") != 0)
		{
			if (env->next)
				env->next->prev = env->prev;
			if (env->prev)
				env->prev->next = env->next;
			else
				program->env = env->next;
			ft_free_unset(env);
		}
		i++;
	}
	g_return_value = 0;
}
