/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:23:56 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 19:14:03 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*search_command(char *cmd, char **value)
{
	char	*data;
	size_t	length;
	char	*substring;
	char	*tmp;

	substring = NULL;
	data = NULL;
	tmp = *value;
	while (*tmp && *tmp != ':')
		tmp++;
	length = tmp - *value;
	if (!length)
		return (NULL);
	substring = ft_substr(*value, 0, length);
	data = ft_strjoin(substring, "/");
	free(substring);
	substring = ft_strjoin(data, cmd);
	free(data);
	if (*tmp)
		*value = tmp + 1;
	return (substring);
}

char	*_search_path(t_mini *m_mini)
{
	t_env	*env;
	t_list	*tmp;
	char	*value;

	value = NULL;
	tmp = m_mini->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	search_path(t_parse *data, int i, t_mini *m_mini)
{
	char	*value;
	char	*str;
	int		x;

	x = -1;
	str = NULL;
	value = _search_path(m_mini);
	while (x != 0 && value && ++i < 10)
	{
		if (str)
			free(str);
		str = search_command(data->cmd, &value);
		if (str)
			x = access(str, F_OK);
		if (str && x == 0)
		{
			free(data->cmd);
			data->cmd = ft_strdup(str);
		}
	}
	free(str);
}

void	run_execve(t_parse *parse, char **env, int *fd, t_mini *m_mini)
{
	char	**full_cmd;

	search_path(parse, -1, m_mini);
	parse->pid = fork();
	full_cmd = NULL;
	if (!parse->pid)
	{
		full_cmd = get_args(parse);
		create_dup(m_mini, parse);
		if (!full_cmd || !parse->cmd || (execve(parse->cmd, full_cmd, env)
				== -1))
		{
			if (parse->cmd && ft_strcmp(parse->cmd, "<<"))
				write (2, "minishell: command not found\n", 29);
			execve_child_free(full_cmd, m_mini);
			exit(127);
		}
	}
	if (fd && parse->pid)
		clear_pipe(fd);
	waitpid(parse->pid, &m_mini->exec_status, 0);
	m_mini->exec_status = WEXITSTATUS(m_mini->exec_status);
}

void	exec_others(t_parse *parse, char **env, int *fd, t_mini *m_mini)
{
	run_execve(parse, env, fd, m_mini);
}
