/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:27:01 by snourry           #+#    #+#             */
/*   Updated: 2022/10/28 05:27:01 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include <stdlib.h>

static char	**ft_args(t_cmd *cmd, int i)
{
	t_token	*tmp;
	char	**args;

	tmp = cmd->args;
	while (tmp)
	{
		if (tmp->type == T_WORD)
			i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * i);
	if (!args)
		return (NULL);
	tmp = cmd->args;
	args[0] = cmd->command;
	i = 1;
	while (tmp)
	{
		if (tmp->type == T_WORD)
			args[i++] = tmp->word;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void	ft_create_exec(t_cmd *cmd)
{
	cmd->exec = ft_args(cmd, 2);
}
