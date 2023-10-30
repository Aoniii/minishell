/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:04:18 by snourry           #+#    #+#             */
/*   Updated: 2022/10/20 22:04:18 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "libft.h"

static int	ft_add_token3(t_token *token, char *str);

static t_token	*ft_create_token(t_token *prev)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (prev)
		prev->next = token;
	token->prev = prev;
	token->next = NULL;
	token->type = T_UNDEFINED;
	token->word = NULL;
	return (token);
}

static int	ft_add_token(t_token *token, char *str, char *end)
{
	int		index;
	char	c[1];

	index = -1;
	c[0] = str[0];
	if (!end)
		end = c;
	if (ft_strlen(str) == 1)
	{
		token->word = ft_substr(str, 0, 1);
		return (1);
	}
	if (c[0] == '$')
		return (ft_add_token3(token, str));
	if (ft_strlen(str) > 1 || str[0] == ' ')
		index++;
	while (str[++index])
		if (ft_strchr(end, str[index]))
			break ;
	if ((str[0] == '\'' || str[0] == '\"') && str[index])
		index++;
	token->word = ft_substr(str, 0, index);
	return (index);
}

static int	ft_add_token2(t_token *token, char *str)
{
	int	index;

	index = -1;
	if (ft_strlen(str) >= 1)
		index++;
	while (str[++index])
		if (str[index] != str[0])
			break ;
	token->word = ft_substr(str, 0, index);
	return (index);
}

static int	ft_add_token3(t_token *token, char *str)
{
	int		index;

	index = 0;
	while (str[++index])
		if (!ft_isalnum(str[index]) && !(str[index] == '?' && index == 1))
			break ;
	token->word = ft_substr(str, 0, index);
	return (index);
}

t_token	*ft_split_token(char *str)
{
	t_token	*token;
	int		index;

	index = 0;
	token = NULL;
	while (str[index])
	{
		token = ft_create_token(token);
		if (str[index] == '\"' || str[index] == '\'' || str[index] == '$')
			index += ft_add_token(token, &str[index], NULL);
		else if (str[index] == '<' || str[index] == '>')
			index += ft_add_token2(token, &str[index]);
		else if (str[index] == ' ' || str[index] == '|')
			token->word = ft_substr(&str[index++], 0, 1);
		else
			index += ft_add_token(token, &str[index], "\'\" <>|");
	}
	while (token->prev)
		token = token->prev;
	return (token);
}
