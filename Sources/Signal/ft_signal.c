/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:26:14 by snourry           #+#    #+#             */
/*   Updated: 2022/11/15 18:57:31 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

static void	ft_ctrl_c(int signal)
{
	(void) signal;
	g_return_value = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ft_ctrl_c_heredoc(int signal)
{
	(void) signal;
	g_return_value = 130;
	close(0);
}

void	ft_init_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_heredoc_signal(void)
{
	signal(SIGINT, ft_ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_change_signal(__sighandler_t sig)
{
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
}
