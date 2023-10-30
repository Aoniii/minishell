/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:18:00 by snourry           #+#    #+#             */
/*   Updated: 2022/11/07 20:45:08 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_token	*ft_space(t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->word = ft_strdup(" ");
	new->type = T_UNDEFINED;
	new->next = NULL;
	return (new);
}

static t_token	*ft_next(char **word, int i, t_token *next, t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->word = word[i];
	new->type = T_UNDEFINED;
	if (word[i + 1])
	{
		new->next = ft_space(new);
		new->next->next = ft_next(word, i + 1, next, new->next);
	}
	else
	{
		new->next = next;
		if (next)
			next->prev = new;
	}
	return (new);
}

int	ft_count_word_wildcard(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == -1)
			j++;
		i++;
	}
	return (j);
}

t_token	*ft_sepfile(t_token *token)
{
	t_token	*next;
	char	**word;

	next = token->next;
	word = ft_split(token->word, -1);
	free(token->word);
	token->word = word[0];
	token->next = ft_space(token);
	token->next->next = ft_next(word, 1, next, token->next);
	free(word);
	if (next)
		return (next->prev);
	else
		while (token->next)
			token = token->next;
	return (token);
}
