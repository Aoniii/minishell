/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:44:41 by snourry           #+#    #+#             */
/*   Updated: 2022/11/14 15:42:36 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_cmd	*ft_parsing(t_env *env, char *str)
{
	t_token	*token;
	t_cmd	*cmd;

	token = ft_split_token(str);
	ft_env_var(env, token);
	token = ft_remove_space(token);
	cmd = ft_token_to_command(token);
	ft_free_token(token);
	return (cmd);
}
