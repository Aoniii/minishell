/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:00:14 by snourry           #+#    #+#             */
/*   Updated: 2022/11/09 23:11:41 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"

void	ft_command_type(t_cmd *cmd)
{
	t_token	*token;
	int		open;

	open = 0;
	while (cmd)
	{
		token = cmd->args;
		while (token)
		{
			if (token->type == T_OPEN)
				open++;
			else if (token->type == T_CLOSE)
				open--;
			if (token->type == T_AND || token->type == T_PIPE || \
				token->type == T_OR)
				cmd->type = token->type;
			token = token->next;
		}
		if (open > 0)
			cmd->parenthese = true;
		cmd = cmd->next;
	}
}
