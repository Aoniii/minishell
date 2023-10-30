/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:44:41 by snourry           #+#    #+#             */
/*   Updated: 2022/11/14 11:29:17 by cmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	ft_error_bracket(int i)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (i > 0)
		ft_putstr_fd("(", 2);
	else
		ft_putstr_fd(")", 2);
	ft_putstr_fd("'\n", 2);
}

bool	ft_check_bracket(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '(')
			j++;
		else if (str[i] == ')')
			j--;
		if (j < 0)
		{
			ft_error_bracket(0);
			return (false);
		}
		i++;
	}
	if (j == 0)
		return (true);
	ft_error_bracket(j);
	return (false);
}

t_cmd	*ft_parsing(t_env *env, char *str)
{
	t_token	*token;
	t_cmd	*cmd;

	token = ft_split_token(str);
	ft_env_var(env, token);
	ft_replace_wildcard(token);
	token = ft_remove_space(token);
	cmd = ft_token_to_command(token);
	ft_free_token(token);
	return (cmd);
}
