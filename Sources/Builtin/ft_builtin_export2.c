/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:49:06 by snourry           #+#    #+#             */
/*   Updated: 2022/11/01 19:49:06 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_print_export(char *str);

static int	ft_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static void	ft_add3(t_env *env, char *str)
{
	int		i;

	i = 0;
	if (ft_get_value(env, str, true))
		return ;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_') || \
		(str[0] == '_' && ft_strlen(str) == 1))
		{
			ft_print_export(str);
			return ;
		}
		i++;
	}
	ft_add_env(env, ft_strdup(str), NULL);
}

static void	ft_add2(t_env *env, char *str, int i)
{
	char	*key;
	char	*value;

	key = ft_substr(str, 0, i);
	i++;
	value = ft_substr(str, i, ft_strlen(str) - i);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_') || \
		(key[0] == '_' && ft_strlen(key) == 1))
		{
			free(key);
			free(value);
			ft_print_export(str);
			return ;
		}
		i++;
	}
	ft_add_env(env, key, value);
}

static void	ft_add4(t_env *env, char *str, int i)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_substr(str, 0, i - 2);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (ft_get_value(env, key, true))
		value = ft_strjoin(ft_get_value(env, key, false), tmp);
	else
		value = ft_strdup(tmp);
	free(tmp);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_') || \
		(key[0] == '_' && ft_strlen(key) == 1))
		{
			free(key);
			free(value);
			ft_print_export(str);
			return ;
		}
		i++;
	}
	ft_add_env(env, key, value);
}

void	ft_add(t_env *env, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->exec[i])
	{
		j = ft_index(cmd->exec[i]);
		if (j && cmd->exec[i][j - 1] == '+')
			ft_add4(env, cmd->exec[i], j + 1);
		else if (j)
			ft_add2(env, cmd->exec[i], j);
		else
			ft_add3(env, cmd->exec[i]);
		i++;
	}
}
