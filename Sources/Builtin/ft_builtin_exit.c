/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:58:54 by snourry           #+#    #+#             */
/*   Updated: 2022/11/03 09:26:46 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static bool	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || ((str[i] == '+' || str[i] == '-') && !i)))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static unsigned char	ft_get_exit(char *str)
{
	unsigned char	c;
	int				i;

	c = 0;
	i = 0;
	if (!ft_isdigit(str[0]))
		i++;
	while (str[i])
	{
		c *= 10;
		c += str[i] - '0';
		i++;
	}
	if (str[0] == '-')
		c = 256 - c;
	return (c);
}

void	ft_builtin_exit(t_program *program, t_cmd *cmd)
{
	unsigned char	out;

	if (!cmd->exec[1])
		out = 0;
	else if (ft_is_valid(cmd->exec[1]))
	{
		if (cmd->exec[2])
		{
			printf("exit\n");
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return ;
		}
		out = ft_get_exit(cmd->exec[1]);
	}
	else
		out = 2;
	printf("exit\n");
	ft_free_char_env(program);
	ft_free_cmd(program);
	ft_free(program);
	exit(out);
}
