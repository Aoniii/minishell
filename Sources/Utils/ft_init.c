/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:28:56 by snourry           #+#    #+#             */
/*   Updated: 2022/11/03 17:27:58 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_program	*ft_init_program(char **env)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->env = ft_create_env(env);
	program->cmd = NULL;
	program->char_env = NULL;
	program->prefix = ft_prefix(program->env);
	program->folder = NULL;
	program->folder = ft_pwd(program);
	program->prompt = NULL;
	program->path = NULL;
	return (program);
}
