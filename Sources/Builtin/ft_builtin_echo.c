/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:37:59 by snourry           #+#    #+#             */
/*   Updated: 2022/10/28 23:37:59 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	ft_builtin_echo(t_cmd *cmd)
{
	char	**str;
	int		i;
	int		nl;

	str = cmd->exec;
	nl = 1;
	i = 1;
	if (str[i])
	{
		if (ft_strcmp(str[i], "-n") == 0)
		{
			i++;
			nl = 0;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			i++;
			if (str[i])
				printf(" ");
		}
	}
	if (nl)
		printf("\n");
	g_return_value = 0;
}
