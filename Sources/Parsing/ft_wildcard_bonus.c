/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:31:20 by snourry           #+#    #+#             */
/*   Updated: 2022/11/07 20:20:52 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <unistd.h>

static bool	ft_strmatch(char *s1, char *s2, int i1, int i2)
{
	int	i3;

	if (s1[i1] == '*' && s2[i2] == '.' && i2 == 0)
		return (false);
	if ((!s1[i1] || (!s1[i1 + 1] && s1[i1] == '*')) && !s2[i2])
		return (true);
	if (!s2[i2])
		return (false);
	if (s1[i1] == s2[i2])
		return (ft_strmatch(s1, s2, i1 + 1, i2 + 1));
	i3 = i2;
	if (s1[i1] == '*')
		while (s2[i3])
			if (ft_strmatch(s1, s2, i1 + 1, i3++))
				return (true);
	if (s1[i1] == '*' && s1[i1 + 1] == s2[i2 + 1])
		return (ft_strmatch(s1, s2, i1 + 1, i2 + 1));
	if (s1[i1] == '*')
		return (ft_strmatch(s1, s2, i1, i2 + 1));
	return (false);
}

static char	*ft_add_to_str(char *str, char *new)
{
	char	*tmp;
	char	c[2];

	c[0] = -1;
	c[1] = 0;
	if (str)
	{
		tmp = ft_strjoin(str, c);
		free(str);
		str = NULL;
	}
	else
		tmp = ft_strdup("");
	str = ft_strjoin(tmp, new);
	free(tmp);
	tmp = NULL;
	return (str);
}

static DIR	*ft_get_dir(void)
{
	char	*cwd;
	DIR		*dir;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	free(cwd);
	cwd = NULL;
	return (dir);
}

static char	*ft_get_wildcard(char *token)
{
	struct dirent	*rd;
	char			*str;
	DIR				*dir;

	str = NULL;
	dir = ft_get_dir();
	if (dir)
	{
		rd = readdir(dir);
		while (rd)
		{
			if (ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, "..") && \
			ft_strmatch(token, rd->d_name, 0, 0))
				str = ft_add_to_str(str, rd->d_name);
			rd = readdir(dir);
		}
		closedir(dir);
	}
	if (!str)
	{
		if (*token == ' ')
			token++;
		return (ft_strdup(token));
	}
	return (str);
}

void	ft_replace_wildcard(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (ft_strchr(token->word, '*') && token->word[0] != '\'' && \
		token->word[0] != '"')
		{
			tmp = ft_get_wildcard(token->word);
			free(token->word);
			token->word = tmp;
			if (ft_count_word_wildcard(tmp) > 1)
				token = ft_sepfile(token);
		}
		token = token->next;
	}
}
