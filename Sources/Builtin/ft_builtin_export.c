/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:01:30 by snourry           #+#    #+#             */
/*   Updated: 2022/11/01 18:01:30 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void	ft_sort(char **export)
{
	char	*tmp;
	int		i;

	i = 0;
	while (export[i + 1])
	{
		if (ft_strcmp(export[i], export[i + 1]) > 0)
		{
			tmp = export[i];
			export[i] = export[i + 1];
			export[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void	ft_show3(char *value)
{
	printf("=\"");
	while (*value)
	{
		if (*value == '$')
			printf("\\%c", *value);
		else
			printf("%c", *value);
		value++;
	}
	printf("\"");
}

static void	ft_show2(t_env *env, char **export)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (export[i])
	{
		value = ft_get_value(env, export[i], true);
		if (ft_strcmp(export[i], "_") != 0)
		{
			printf("declare -x %s", export[i]);
			if (value)
				ft_show3(value);
			printf("\n");
		}
		i++;
	}
}

static void	ft_show(t_env *env)
{
	t_env	*env1;
	char	**export;
	int		i;

	i = 0;
	env1 = env;
	export = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!export)
		return ;
	while (env)
	{
		export[i] = env->key;
		env = env->next;
		i++;
	}
	export[i] = NULL;
	ft_sort(export);
	ft_show2(env1, export);
	free(export);
	g_return_value = 0;
}

void	ft_builtin_export(t_env *env, t_cmd *cmd)
{
	if (cmd->exec[1])
		ft_add(env, cmd);
	else
		ft_show(env);
}
