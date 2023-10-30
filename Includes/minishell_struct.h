/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:55:18 by snourry           #+#    #+#             */
/*   Updated: 2022/11/05 14:27:05 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <stdbool.h>

typedef enum e_type
{
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_OPEN,
	T_CLOSE,
	T_SPACE,
	T_ERROR,
	T_UNDEFINED,
	T_WORD_HEREDOC,
	T_FILE,
	T_REDIR_HEREDOC,
	T_REDIR_TRUNC,
	T_REDIR_APPEND,
	T_REDIR_IN
}	t_type;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
}					t_env;

typedef struct s_program
{
	struct s_env	*env;
	struct s_cmd	*cmd;
	char			**char_env;
	char			*prefix;
	char			*folder;
	char			*prompt;
	char			*path;
}					t_program;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	struct s_token	*args;
	char			**exec;
	char			*command;
	int				pid;
	int				in;
	int				out;
	bool			parenthese;
	enum e_type		type;
}					t_cmd;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*word;
	t_type			type;
}					t_token;

#endif
