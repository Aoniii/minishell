/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:07:43 by snourry           #+#    #+#             */
/*   Updated: 2022/11/01 01:07:43 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

static void	ft_up_pipe(t_cmd *cmd, int *in, int *out)
{
	if (cmd->in)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	else if (in[0] != -1)
	{
		dup2(in[0], 0);
		close(in[0]);
	}
	if (cmd->out)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else if (out[0] != -1)
	{
		dup2(out[1], 1);
		close(out[0]);
		close(out[1]);
	}
}

static void	ft_signal_message(void)
{
	if (g_return_value == 2)
		printf("\n");
	if (g_return_value == 131)
		printf("Quit (core dumped)\n");
}

void	ft_fork_cmd(t_program *program, t_cmd *cmd, int *in, int *out)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		ft_change_signal(SIG_DFL);
		ft_up_pipe(cmd, in, out);
		ft_choice_exec(program, cmd, true);
		ft_free_char_env(program);
		ft_free_cmd(program);
		ft_free(program);
		exit(g_return_value);
	}
	if (in[0] != -1)
		close(in[0]);
	if (out[0] != -1)
		close(out[1]);
	in[0] = out[0];
	in[1] = out[1];
}

void	ft_fork_heredoc(t_program *program, t_cmd *cmd, char *word)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		ft_heredoc_signal();
		ft_heredoc(program, cmd, word);
		exit(g_return_value);
	}
	waitpid(cmd->pid, &g_return_value, 0);
	ft_signal_message();
	if (g_return_value == 2)
		g_return_value = 130;
	cmd->pid = 0;
}

void	ft_fork_without_pipe(t_program *program, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		ft_change_signal(SIG_DFL);
		ft_choice_exec(program, cmd, true);
		ft_free_char_env(program);
		ft_free_cmd(program);
		ft_free(program);
		exit(g_return_value);
	}
	waitpid(cmd->pid, &g_return_value, 0);
	ft_change_signal(SIG_IGN);
	if (g_return_value != 2)
		g_return_value = WEXITSTATUS(g_return_value);
	else
		g_return_value = 130;
	cmd->pid = 0;
}
