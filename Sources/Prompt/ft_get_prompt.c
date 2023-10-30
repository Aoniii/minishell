/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:27:36 by snourry           #+#    #+#             */
/*   Updated: 2022/10/04 18:27:36 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_get_prompt(t_program *program)
{
	char	*tmp;

	if (program->prompt)
	{
		free(program->prompt);
		program->prompt = NULL;
	}
	program->folder = ft_pwd(program);
	tmp = ft_strjoin(program->prefix, program->folder);
	program->prompt = ft_strjoin(tmp, "\e[33m ➤ \e[21m\e[0m");
	free(tmp);
	tmp = program->prompt;
	if (g_return_value == 0)
		program->prompt = ft_strjoin("\e[1m\e[32m➜  \e[94m", tmp);
	else
		program->prompt = ft_strjoin("\e[1m\e[31m➜  \e[94m", tmp);
	free(tmp);
	tmp = NULL;
	return (program->prompt);
}
