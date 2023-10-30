/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:39:57 by snourry           #+#    #+#             */
/*   Updated: 2022/10/27 15:39:57 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void	ft_print_error_execve(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static void	ft_free_exec(t_program *program)
{
	ft_free_char_env(program);
	ft_free_cmd(program);
	ft_free(program);
}

void	ft_execve(t_program *program, t_cmd *cmd)
{
	if (program->path)
		free(program->path);
	program->path = ft_get_path(program->env, cmd->command);
	if ((ft_strlen(cmd->command) <= 2 && cmd->command[0] == '.' && \
	(cmd->command[1] == '.' || cmd->command[1] == '/' || !cmd->command[1])) \
	|| !program->path)
	{
		ft_print_error_execve(cmd->command);
		ft_free_exec(program);
		exit(127);
	}
	g_return_value = 0;
	execve(program->path, cmd->exec, program->char_env);
	ft_free_exec(program);
	exit(EXIT_FAILURE);
}
