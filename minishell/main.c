/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:21:18 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 17:47:44 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

int		g_heredoc_sig;

void	get_readline(t_mini *mini)
{
	mini->cmd = readline("BBminishell ||--|| = ");
	if (mini->cmd && !is_space(mini->cmd))
	{
		free(mini->cmd);
		get_readline(mini);
	}
	if (!mini->cmd)
	{
		free_loop(0, mini);
		free_(mini);
		free(mini->lex_list);
		free(mini);
		exit(1);
	}
	add_history(mini->cmd);
}

void	go_parser(t_mini *mini, char **env, int control)
{
	control = check(mini);
	if (!control)
	{
		error_free(&(mini->lex_list)->lex);
		return ;
	}
	if (ft_strcmp(mini->cmd, ""))
	{
		if (our_parser(mini))
			exec(env, mini);
	}
	free_loop(control, mini);
}

void	start_minishell(t_mini *mini, char **env, int control)
{
	while (1)
	{
		get_readline(mini);
		if (quote_check(mini->cmd, '\'', '\"'))
		{
			lexer(mini);
			expander(mini);
			go_parser(mini, env, control);
		}
		else
		{
			(free(mini->cmd));
			continue ;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	int		control;

	(void)av;
	control = 0;
	if (ac != 1)
		return (ft_putstr_fd(W_ARGS, 2), 1);
	if (null_init(&mini) == 1)
		return (printf(A_ERR), 1);
	if (mini_init(&mini) == 1)
		return (free_init_check(mini), ft_putstr_fd(A_ERR, 2), 1);
	if (env_get(env, &mini))
		return (free_init_check(mini), ft_putstr_fd(A_ERR, 2), 1);
	signals_control();
	start_minishell(mini, env, control);
}
