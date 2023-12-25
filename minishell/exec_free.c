/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:18:59 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:06 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	_free_env(t_list *tmp2, t_mini *m_mini)
{
	t_env	*tmp;

	while (tmp2)
	{
		tmp = tmp2->content;
		if (tmp2->content)
		{
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
	while (m_mini->env)
	{
		tmp2 = m_mini->env;
		m_mini->env = m_mini->env->next;
		if (tmp2)
			free(tmp2);
	}
}

void	free_env(t_mini *m_mini)
{
	t_list	*tmp2;

	tmp2 = m_mini->env;
	if (tmp2 && tmp2->content)
		_free_env(tmp2, m_mini);
	else if (m_mini->env && !m_mini->env->content)
		free(m_mini->env);
}

void	free_(t_mini *m_mini)
{
	free_env(m_mini);
	clear_history();
}

void	free_loop(int control, t_mini *m_mini)
{
	if (m_mini->cmd)
		free(m_mini->cmd);
	if (control)
	{
		if (m_mini->parse)
			free_parser(m_mini);
	}
	if (m_mini->heredoc)
	{
		free(m_mini->heredoc);
		m_mini->heredoc = NULL;
	}
}

void	execve_child_free(char **str, t_mini *m_mini)
{
	free_(m_mini);
	free_loop(1, m_mini);
	free_text(str);
	free(m_mini->lex_list);
	free(m_mini);
}
