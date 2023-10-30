/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:24:18 by snourry           #+#    #+#             */
/*   Updated: 2022/10/21 19:24:18 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_before_var(char *s)
{
	char	*str;

	str = NULL;
	if (s[0] != '$')
		str = ft_substr(s, 0, ft_strindex(s, '$'));
	return (str);
}

static void	ft_new_value(t_token *token, char *value, int index)
{
	char	*str;
	char	*tmp;
	char	*tmp1;

	tmp = ft_before_var(token->word);
	if (tmp)
	{
		str = ft_strjoin(tmp, value);
		free(tmp);
		tmp = NULL;
		free(value);
	}
	else
		str = value;
	if (token->word[index - 1] && token->word[index])
		tmp = ft_substr(token->word, index, ft_strlen(token->word) - index);
	if (tmp)
	{
		tmp1 = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
		str = tmp1;
	}
	free(token->word);
	token->word = str;
}

static void	ft_replace_var(t_env *env, t_token *token)
{
	char	*str;
	char	*key;
	int		i;

	str = NULL;
	key = NULL;
	i = ft_strindex(token->word, '$') + 1;
	if (token->word[i] == '?')
		str = ft_itoa(g_return_value);
	else
	{
		while (token->word[i] && ft_isalnum(token->word[i]))
			i++;
		if (token->word[i])
			i--;
		key = ft_substr(token->word, ft_strindex(token->word, '$') + 1, \
		i - ft_strindex(token->word, '$'));
		str = ft_strdup(ft_get_value(env, key, false));
	}
	if (key)
		free(key);
	ft_new_value(token, str, i + 1);
}

void	ft_env_var(t_env *env, t_token *token)
{
	while (token)
	{
		if (ft_strchr(token->word, '$') && token->word[0] != '\'' \
		&& ft_strlen(token->word) > 1 \
		&& token->word[ft_strindex(token->word, '$') + 1] \
		&& token->word[ft_strindex(token->word, '$') + 1] != '"')
			ft_replace_var(env, token);
		token = token->next;
	}
}
