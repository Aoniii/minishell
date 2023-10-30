/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:20:32 by snourry           #+#    #+#             */
/*   Updated: 2022/10/29 00:20:32 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_builtin_env(t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (e->value)
			printf("%s=%s\n", e->key, e->value);
		e = e->next;
	}
	g_return_value = 0;
}
