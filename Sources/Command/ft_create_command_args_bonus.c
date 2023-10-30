/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command_args_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:08:42 by snourry           #+#    #+#             */
/*   Updated: 2022/11/07 20:33:47 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

typedef t_token	t_args;

static t_type	ft_redirection_type(char *str)
{
	if (ft_strlen(str) > 2)
		return (T_ERROR);
	if (ft_strcmp(str, ">") == 0)
		return (T_REDIR_TRUNC);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_REDIR_APPEND);
	else if (ft_strcmp(str, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_REDIR_HEREDOC);
	return (T_ERROR);
}

static t_type	ft_word_type(t_token *token)
{
	if (token->type == T_REDIR_HEREDOC)
		return (T_WORD_HEREDOC);
	return (T_FILE);
}

static t_type	ft_define_type(char *str, t_args *prev)
{
	if (str[0] == '|' && str[1] == '|')
		return (T_OR);
	else if (str[0] == '|')
		return (T_PIPE);
	else if (str[0] == '&' && str[1] == '&')
		return (T_AND);
	else if (str[0] == ' ')
		return (T_SPACE);
	else if (prev && prev->type >= T_REDIR_HEREDOC && \
	str[0] != '<' && str[0] != '>')
		return (ft_word_type(prev));
	else if (prev && prev->prev && prev->prev->type >= T_REDIR_HEREDOC \
	&& (prev->type != T_FILE && prev->type != T_WORD_HEREDOC) \
	&& str[0] != '<' && str[0] != '>')
		return (ft_word_type(prev));
	else if (prev && prev->type >= T_REDIR_HEREDOC)
		return (T_ERROR);
	else if (str[0] == '<' || str[0] == '>')
		return (ft_redirection_type(str));
	else if (str[0] == '(')
		return (T_OPEN);
	else if (str[0] == ')')
		return (T_CLOSE);
	else
		return (T_WORD);
}

static t_args	*ft_create_args(t_token *token, t_args *prev)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->prev = prev;
	args->type = ft_define_type(token->word, prev);
	if (token->word[0] == '"' || token->word[0] == '\'')
		args->word = ft_get_token_word(token);
	else
		args->word = ft_strdup(token->word);
	if (args->type == T_PIPE || args->type == T_OR || args->type == T_AND)
		args->next = NULL;
	else if (token->next)
		args->next = ft_create_args(token->next, args);
	else
		args->next = NULL;
	return (args);
}

t_token	*ft_get_args(t_cmd *cmd, t_token *token)
{
	cmd->args = ft_create_args(token, NULL);
	while (1)
	{
		if (!token)
			break ;
		if (token->word[0] == '|' || \
		(token->word[0] == '&' && token->word[1] == '&'))
			return (token->next);
		token = token->next;
	}
	return (token);
}
