/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:42:18 by snourry           #+#    #+#             */
/*   Updated: 2022/11/10 14:42:22 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "libft.h"

static void	ft_print(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

bool	ft_check_cmd(t_cmd *cmd)
{
	t_token	*token;

	while (cmd)
	{
		token = cmd->args;
		while (token)
		{
			if (token->type == T_ERROR)
			{
				ft_print(token->word);
				return (false);
			}
			token = token->next;
		}
		cmd = cmd->next;
	}
	return (true);
}
