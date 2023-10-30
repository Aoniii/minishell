/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:06:37 by snourry           #+#    #+#             */
/*   Updated: 2022/10/28 06:09:03 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_free(t_program *program)
{
	ft_free_env(program);
	free(program->prefix);
	program->prefix = NULL;
	free(program->folder);
	program->folder = NULL;
	free(program->prompt);
	program->prompt = NULL;
	if (program->path)
		free(program->path);
	program->path = NULL;
	free(program);
	program = NULL;
}
