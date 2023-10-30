/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 08:12:44 by snourry           #+#    #+#             */
/*   Updated: 2022/11/15 18:32:22 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_struct.h"
# include <signal.h>

extern int	g_return_value;

/**
 * Builtin
 */

void		ft_builtin_pwd(void);
void		ft_builtin_echo(t_cmd *cmd);
void		ft_builtin_env(t_env *env);
void		ft_builtin_cd(t_env *env, t_cmd *cmd);
void		ft_builtin_unset(t_program *program, t_cmd *cmd);
void		ft_builtin_export(t_env *env, t_cmd *cmd);
void		ft_add(t_env *env, t_cmd *cmd);
void		ft_builtin_exit(t_program *program, t_cmd *cmd);

/**
 * Command
 */

t_cmd		*ft_token_to_command(t_token *token);
char		*ft_get_token_word(t_token *token);
t_token		*ft_get_args(t_cmd *cmd, t_token *token);
void		ft_recreate_command(t_cmd *cmd);
void		ft_command_type(t_cmd *cmd);
bool		ft_check_cmd(t_cmd *cmd);

/**
 * Execution
 */

void		ft_exec(t_program *program);
char		*ft_get_path(t_env *env, char *cmd);
void		ft_execve(t_program *program, t_cmd *cmd);
void		ft_create_exec(t_cmd *cmd);
void		ft_fork_cmd(t_program *program, t_cmd *cmd, int *in, int *out);
void		ft_choice_exec(t_program *program, t_cmd *cmd, bool fork);
void		ft_init_redirect(t_program *program, t_cmd *cmd);
void		ft_fork_without_pipe(t_program *program, t_cmd *cmd);
void		ft_fork_heredoc(t_program *program, t_cmd *cmd, char *word);
void		ft_print_error(int i, char *word);
int			ft_redir(int last_fd, char *name, int flag);
void		ft_heredoc(t_program *program, t_cmd *cmd, char *word);

/**
 * Free
 */

void		ft_free_env(t_program *program);
void		ft_free_char_env(t_program *program);
void		ft_free(t_program *program);
void		ft_free_one_cmd(t_cmd *cmd);
void		ft_free_cmd(t_program *program);
void		ft_free_token(t_token *token);

/**
 * Parsing
 */

t_cmd		*ft_parsing(t_env *env, char *str);
t_token		*ft_split_token(char *str);
void		ft_env_var(t_env *env, t_token *token);
t_token		*ft_remove_space(t_token *token);
void		ft_replace_wildcard(t_token *token);
t_token		*ft_sepfile(t_token *token);
bool		ft_check_bracket(char *str);
int			ft_count_word_wildcard(char *str);

/**
 * Prompt
 */

char		*ft_get_prompt(t_program *program);
char		*ft_prefix(t_env *env);
char		*ft_pwd(t_program *program);

/**
 * Signal
 */

void		ft_init_signal(void);
void		ft_heredoc_signal(void);
void		ft_change_signal(__sighandler_t sig);

/**
 * Utils
 */

t_env		*ft_create_env(char **env);
char		*ft_get_value(t_env *env, char *key, bool nullValue);
char		**ft_get_env(t_env *env);
t_program	*ft_init_program(char **env);
void		ft_add_env(t_env *e, char *key, char *value);
t_env		*ft_get(t_env *env, char *key);
int			ft_env_size(t_env *env);
bool		ft_check_is_space(char *str);

#endif
