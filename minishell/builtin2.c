/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:23:32 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:41 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	change_old(char *str, t_mini *m_mini)
{
	t_list	*node;
	t_env	*env;
	char	*targetkey;

	targetkey = "OLDPWD";
	node = m_mini->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strcmp(env->key, targetkey))
		{
			free(env->value);
			env->value = ft_strdup(str);
			return ;
		}
		node = node->next;
	}
}

void	change_pwd(t_parse *data, t_mini *m_mini)
{
	char	*targetkey;
	t_list	*node;
	t_env	*env;

	targetkey = "PWD";
	node = m_mini->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strcmp(env->key, targetkey))
		{
			if (env->value)
				free(env->value);
			if (data->text && !ft_strcmp(data->text[0], "~"))
				env->value = get_home(m_mini);
			else
				env->value = getcwd(NULL, 0);
			return ;
		}
		node = node->next;
	}
}

void	exec_cd1(char *str, t_parse *data, t_mini *m_mini)
{
	change_old(str, m_mini);
	chdir(get_home(m_mini));
	change_pwd(data, m_mini);
	m_mini->exec_status = 0;
}

void	exec_cd(t_parse *data, t_mini *m_mini)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (data->text && data->text[0])
	{
		if (chdir(data->text[0]) == 0)
		{
			change_old(str, m_mini);
			change_pwd(data, m_mini);
			m_mini->exec_status = 0;
		}
		else
		{
			if (str)
				free(str);
			m_mini->exec_status = 1;
			perror("cd");
		}
	}
	else
		exec_cd1(str, data, m_mini);
}
