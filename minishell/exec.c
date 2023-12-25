/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:19:12 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:53 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_parse *tmp, int *fd, t_mini *m_mini)
{
	int	control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(tmp, m_mini);
	else
		exec_others(tmp, env, fd, m_mini);
	free_(m_mini);
	free_loop(1, m_mini);
	free(m_mini->lex_list);
	free(m_mini);
	exit(0);
}

void	only_single_command(char **env, t_parse *parse, t_mini *m_mini)
{
	int	control;

	control = 0;
	if (parse->type != HEREDOC)
		control = is_builtin(parse);
	if (control)
		execute_builtin_command(m_mini->parse, m_mini);
	else
		exec_others(m_mini->parse, env, NULL, m_mini);
}

void	multi_command_(t_parse *parse, char **env, t_mini *m_mini, int *fd)
{
	t_parse	*nparse;

	while (parse)
	{
		if (parse->next)
			pipe(fd);
		nparse = _next_command(&parse);
		parse->pid = fork();
		if (parse->pid == 0)
		{
			create_dup_one(parse, fd);
			run_command(env, parse, fd, m_mini);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		parse = nparse;
	}
}

void	multi_command(char **env, int x, t_parse *parse, t_mini *m_mini)
{
	int	*fd;

	(void)x;
	m_mini->parse->std_in = dup(0);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return ;
	multi_command_(parse, env, m_mini, fd);
	dup2(m_mini->parse->std_in, 0);
	clear_pipe(fd);
	wait_all(m_mini);
}

void	exec(char **env, t_mini *m_mini)
{
	int	x;

	if (g_heredoc_sig != 0)
		loop_heredoc(m_mini);
	if (m_mini->parse->cmd && !ft_strcmp(m_mini->parse->cmd, "exit")
		&& g_heredoc_sig != -10 && _next_command(&m_mini->parse) == NULL)
	{
		builtin_exit(&m_mini);
		return ;
	}
	x = single_or_multi_command(m_mini);
	if (!x && g_heredoc_sig != -10)
		only_single_command(env, m_mini->parse, m_mini);
	else if (g_heredoc_sig != -10)
		multi_command(env, 0, m_mini->parse, m_mini);
	g_heredoc_sig = 0;
}
