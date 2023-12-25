/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:19:03 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:02 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_text(char **text)
{
	int	i;

	i = 0;
	if (text)
	{
		if (text[i])
		{
			while (text[i])
				free(text[i++]);
		}
		free(text);
	}
}

void	free_parses_cmd_text(t_parse *parse)
{
	t_parse	*tmp;

	while (parse)
	{
		tmp = parse;
		parse = parse->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->text)
			free_text(tmp->text);
		free(tmp);
	}
}

void	free_parser(t_mini *m_mini)
{
	t_parse	*parse;

	parse = m_mini->parse;
	if (parse)
		free_parses_cmd_text(parse);
	else if (m_mini->parse)
		free(m_mini->parse);
}

int	*create_pipe(void)
{
	int	index;
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	if (!fd)
		return (NULL);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}
