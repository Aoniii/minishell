/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:02 by snourry           #+#    #+#             */
/*   Updated: 2022/11/13 17:24:02 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_get_token_word(t_token *token)
{
	char	*str;
	char	*tmp;
	int		i[2];

	tmp = ft_strdup(token->word);
	i[0] = 0;
	i[1] = 0;
	if (tmp[0] == '\'' || tmp[0] == '"')
	{
		i[0]++;
		if (tmp[ft_strlen(tmp) - 1] == tmp[0] \
		|| tmp[ft_strlen(tmp) - 1] == tmp[0])
			i[1]++;
	}
	if (i[0] || i[1])
	{
		str = ft_substr(tmp, 1, ft_strlen(tmp) - 1 - i[1]);
		free(tmp);
		tmp = NULL;
	}
	else
		str = tmp;
	return (str);
}

static t_token	*ft_set_cmd(t_cmd *cmd, t_token *token)
{
	char	*tmp;
	char	*tmp1;

	if (token->word[0] == ' ')
		token = token->next;
	if (token->word[0] == '<' || token->word[0] == '>' \
	|| token->word[0] == '(' || token->word[0] == ')')
	{
		cmd->command = NULL;
		return (token);
	}
	cmd->command = ft_strdup("");
	while (token && token->word[0] != ' ')
	{
		tmp = ft_get_token_word(token);
		tmp1 = ft_strjoin(cmd->command, tmp);
		free(tmp);
		tmp = NULL;
		free(cmd->command);
		cmd->command = tmp1;
		token = token->next;
	}
	if (token && token->word[0] == ' ')
		return (token->next);
	return (token);
}

static t_token	*ft_tokenjoin(t_token *token)
{
	t_token	*first;
	char	*tmp;
	t_token	*tmp1;

	first = token;
	while (token)
	{
		if (token->type == T_WORD && token->next && \
		token->next->type == T_WORD)
		{
			tmp = ft_strjoin(token->word, token->next->word);
			tmp1 = token->next;
			free(token->word);
			token->word = tmp;
			free(token->next->word);
			token->next = token->next->next;
			if (token->next)
				token->next->prev = token;
			free(tmp1);
		}
		else
			token = token->next;
	}
	return (first);
}

static t_cmd	*ft_create_cmd(t_token *token, t_cmd *prev)
{
	t_cmd	*cmd;

	if (!token)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	cmd->prev = prev;
	cmd->exec = NULL;
	cmd->pid = -1;
	cmd->in = 0;
	cmd->out = 0;
	cmd->parenthese = false;
	cmd->type = T_UNDEFINED;
	token = ft_set_cmd(cmd, token);
	if (token)
	{
		token = ft_get_args(cmd, token);
		cmd->args = ft_tokenjoin(cmd->args);
	}
	else
		cmd->args = NULL;
	cmd->next = ft_create_cmd(token, cmd);
	return (cmd);
}

t_cmd	*ft_token_to_command(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_create_cmd(token, NULL);
	ft_command_type(cmd);
	return (cmd);
}
