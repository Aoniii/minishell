/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recreate_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:28:43 by snourry           #+#    #+#             */
/*   Updated: 2022/11/14 23:04:41 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include <stdlib.h>

void	ft_recreate_command(t_cmd *cmd)
{
	t_token	*args;

	if (cmd->command)
		return ;
	args = cmd->args;
	while (args && args->type != T_WORD)
		args = args->next;
	if (!args)
		return ;
	cmd->command = args->word;
	if (args->prev)
		args->prev->next = args->next;
	if (args->next)
		args->next->prev = args->prev;
	free(args);
	args = 0;
}
