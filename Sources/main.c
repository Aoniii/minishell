/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 08:12:36 by snourry           #+#    #+#             */
/*   Updated: 2022/11/10 22:36:06 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_return_value = 0;

int	main(int argc, char **argv, char **env)
{
	t_program	*program;
	char		*str;

	(void) argc;
	(void) argv;
	program = ft_init_program(env);
	ft_init_signal();
	while (1)
	{
		str = readline(ft_get_prompt(program));
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		else if (str[0] && !ft_check_is_space(str))
		{
			add_history(str);
			program->cmd = ft_parsing(program->env, str);
			ft_exec(program);
		}
	}
	ft_free(program);
	return (0);
}
