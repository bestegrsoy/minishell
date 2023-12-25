/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:16:01 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:16 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

char	*add_char(char *str, char a)
{
	char	*tmp;
	int		i;
	int		len;

	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	tmp = ft_calloc(sizeof(char) * (len + 2), 1);
	if (!tmp)
		return (NULL);
	i = 0;
	if (!a)
	{
		free(tmp);
		return (NULL);
	}
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = a;
	free(str);
	return (tmp);
}

void	get_var(int *fd, t_mini *m_mini)
{
	char	*a;

	a = malloc(sizeof(char));
	if (!a)
	{
		m_mini->heredoc = NULL;
		return ;
	}
	while (read(fd[0], a, 1))
	{
		m_mini->heredoc = add_char(m_mini->heredoc, *a);
		free(a);
		a = malloc(sizeof(char));
		if (!a)
			return ;
	}
	if (a)
		free(a);
	close(fd[0]);
}

void	get_input(t_parse *parse, int *fd)
{
	char	*delimiter;
	char	*buffer;

	delimiter = parse->next->text[0];
	while (1 && g_heredoc_sig != -3)
	{
		buffer = readline("> ");
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			if (buffer)
				free(buffer);
			break ;
		}
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		if (buffer)
			free(buffer);
	}
}

void	heredoc(t_parse *parse, t_mini *m_mini)
{
	int	fd[2];
	int	id;

	pipe(fd);
	signal(SIGINT, set_heredoc);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, killer);
		close(fd[0]);
		get_input(parse, fd);
		close(fd[1]);
		free_(m_mini);
		free_loop(1, m_mini);
		free(m_mini->lex_list);
		free(m_mini);
		exit(1);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, signals);
	close(fd[1]);
	get_var(fd, m_mini);
}

void	loop_heredoc(t_mini *m_mini)
{
	t_parse	*parse;

	parse = m_mini->parse;
	while (parse)
	{
		if (parse->type == HEREDOC)
		{
			heredoc(parse, m_mini);
		}
		parse = parse->next;
	}
}
