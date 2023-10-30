/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:33:25 by snourry           #+#    #+#             */
/*   Updated: 2022/11/15 18:34:42 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static bool	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

void	ft_choice_exec(t_program *program, t_cmd *cmd, bool fork)
{
	if (!cmd->command)
		return ;
	if (cmd->in == -1 || cmd->out == -1)
		return ;
	ft_create_exec(cmd);
	if (ft_strcmp(cmd->command, "pwd") == 0)
		ft_builtin_pwd();
	else if (ft_strcmp(cmd->command, "echo") == 0)
		ft_builtin_echo(cmd);
	else if (ft_strcmp(cmd->command, "env") == 0)
		ft_builtin_env(program->env);
	else if (ft_strcmp(cmd->command, "cd") == 0)
		ft_builtin_cd(program->env, cmd);
	else if (ft_strcmp(cmd->command, "unset") == 0)
		ft_builtin_unset(program, cmd);
	else if (ft_strcmp(cmd->command, "export") == 0)
		ft_builtin_export(program->env, cmd);
	else if (ft_strcmp(cmd->command, "exit") == 0)
		ft_builtin_exit(program, cmd);
	else if (fork)
		ft_execve(program, cmd);
	else
		ft_fork_without_pipe(program, cmd);
}

static void	ft_exec2(t_program *program, t_cmd *cmd, int *in)
{
	int		out[2];

	out[0] = -1;
	if (cmd->next)
		if (pipe(out) == -1)
			return ;
	ft_init_redirect(program, cmd);
	ft_change_signal(SIG_IGN);
	if (cmd->prev && cmd->prev->type == T_OR && g_return_value == 0)
		return ;
	if (cmd->prev && cmd->prev->type == T_AND && g_return_value != 0)
		return ;
	if (((cmd->command && !cmd->next && !cmd->prev && \
	ft_isbuiltin(cmd->command) && cmd->in == 0 && cmd->out == 0) \
	|| cmd->type == T_AND || cmd->type == T_OR) && !cmd->parenthese)
		ft_choice_exec(program, cmd, false);
	else
	{
		ft_recreate_command(cmd);
		ft_fork_cmd(program, cmd, in, out);
	}
}

static void	ft_wait_pid(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &g_return_value, 0);
			if (g_return_value == 2)
			{
				printf("\n");
				g_return_value = 130;
			}
			else if (g_return_value == 131)
				printf("Quit (core dumped)\n");
			else
				g_return_value = WEXITSTATUS(g_return_value);
		}
		cmd = cmd->next;
	}
}

void	ft_exec(t_program *program)
{
	t_cmd	*cmd;
	int		in[2];

	if (ft_check_cmd(program->cmd))
	{
		program->char_env = ft_get_env(program->env);
		cmd = program->cmd;
		in[0] = -1;
		while (cmd)
		{
			ft_exec2(program, cmd, in);
			cmd = cmd->next;
		}
		ft_wait_pid(program->cmd);
		ft_init_signal();
		ft_free_char_env(program);
	}
	ft_free_cmd(program);
}
