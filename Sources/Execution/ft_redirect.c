/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:55:19 by snourry           #+#    #+#             */
/*   Updated: 2022/11/02 17:55:19 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

int	ft_redir(int last_fd, char *name, int flag)
{
	int	fd;

	if (last_fd)
		close(last_fd);
	fd = open(name, flag, 420);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_return_value = 1;
		return (-1);
	}
	return (fd);
}

void	ft_print_error(int i, char *word)
{
	char	*line;

	line = ft_itoa(i);
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("  delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("')\n", 2);
	free(line);
	line = NULL;
}

static void	ft_init_redirect2(t_program *program, t_cmd *cmd, \
char *word, t_type redir)
{
	if (redir == T_REDIR_IN)
		cmd->in = ft_redir(cmd->in, word, 0);
	else if (redir == T_REDIR_HEREDOC)
	{
		cmd->in = ft_redir(cmd->in, "/tmp/.minishell_heredoc", 578);
		ft_fork_heredoc(program, cmd, word);
		close(cmd->in);
		cmd->in = ft_redir(cmd->in, "/tmp/.minishell_heredoc", 0);
		unlink("/tmp/.minishell_heredoc");
	}
}

void	ft_init_redirect(t_program *program, t_cmd *cmd)
{
	t_token	*args;
	t_type	redir;

	args = cmd->args;
	while (args)
	{
		if (args->type >= T_REDIR_HEREDOC)
			redir = args->type;
		if (args->type == T_FILE || args->type == T_WORD_HEREDOC)
		{
			if (redir == T_REDIR_TRUNC || redir == T_REDIR_APPEND)
			{
				if (redir == T_REDIR_TRUNC)
					cmd->out = ft_redir(cmd->out, args->word, 577);
				else
					cmd->out = ft_redir(cmd->out, args->word, 1089);
			}
			else if (redir == T_REDIR_IN || redir == T_REDIR_HEREDOC)
				ft_init_redirect2(program, cmd, args->word, redir);
		}
		if (cmd->in == -1 || cmd->out == -1)
			break ;
		args = args->next;
	}
}

void	ft_heredoc(t_program *program, t_cmd *cmd, char *word)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (1)
	{
		str = readline("> ");
		i++;
		if (!str)
		{
			if (g_return_value != 130)
				ft_print_error(i, word);
			break ;
		}
		if (ft_strcmp(str, word) == 0)
			break ;
		ft_putstr_fd(str, cmd->in);
		ft_putstr_fd("\n", cmd->in);
	}
	ft_free_char_env(program);
	ft_free_cmd(program);
	ft_free(program);
}
