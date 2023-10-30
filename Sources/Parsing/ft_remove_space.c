/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:21:17 by snourry           #+#    #+#             */
/*   Updated: 2022/10/23 11:21:17 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "libft.h"

static void	ft_delete_space(t_token *token)
{
	t_token	*tmp;

	token = token->next;
	while (token)
	{
		if ((token->word[0] == ' ' || !token->word[0]) && \
		ft_strlen(token->word) <= 1 && (!token->next || \
		(token->next->word[0] == ' ' || !token->next->word[0])))
		{
			if (token->prev)
				token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			free(token->word);
			token->word = NULL;
			tmp = token;
			token = token->next;
			free(tmp);
			tmp = NULL;
		}
		else
			token = token->next;
	}
}

t_token	*ft_remove_space(t_token *token)
{
	ft_delete_space(token);
	while (token->word[0] == ' ' && ft_strlen(token->word) == 1 && token->next)
	{
		token = token->next;
		free(token->prev->word);
		token->prev->word = NULL;
		free(token->prev);
		token->prev = NULL;
	}
	return (token);
}
