/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:03:16 by snourry           #+#    #+#             */
/*   Updated: 2022/10/29 19:03:16 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void	ft_print_error_cd(char *str, char *error)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

static void	ft_update_pwd(t_env *env)
{
	if (ft_get_value(env, "PWD", true))
		ft_add_env(env, ft_strdup("OLDPWD"), \
	ft_strdup(ft_get_value(env, "PWD", false)));
	ft_add_env(env, ft_strdup("PWD"), getcwd(NULL, 0));
}

static void	ft_cd(t_env *env, char *str)
{
	if (!str)
	{
		if (chdir(ft_get_value(env, "HOME", false)) < 0)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return ;
		}
	}
	else
	{
		if (chdir(str) < 0)
		{
			ft_print_error_cd(str, strerror(errno));
			return ;
		}
	}
}

void	ft_builtin_cd(t_env *env, t_cmd *cmd)
{
	char	*str;

	str = cmd->exec[1];
	g_return_value = 1;
	if (cmd->exec[1] && cmd->exec[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return ;
	}
	ft_cd(env, str);
	g_return_value = 0;
	ft_update_pwd(env);
}
