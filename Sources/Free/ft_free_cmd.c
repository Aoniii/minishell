/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:11:01 by snourry           #+#    #+#             */
/*   Updated: 2022/11/14 15:59:35 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include <stdlib.h>

void	ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->word);
		tmp->word = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_one_cmd(t_cmd *cmd)
{
	if (cmd->args)
		ft_free_token(cmd->args);
	if (cmd->command)
		free(cmd->command);
	cmd->command = NULL;
	if (cmd->exec)
		free(cmd->exec);
	cmd->exec = NULL;
	free(cmd);
	cmd = NULL;
}

void	ft_free_cmd(t_program *program)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;

	tmp = program->cmd;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		ft_free_one_cmd(tmp1);
	}
}
