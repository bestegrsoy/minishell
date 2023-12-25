/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:20:13 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:47:42 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	null_init(t_mini **mini)
{
	*mini = malloc(sizeof(t_mini));
	if (!(*mini))
		return (1);
	(*mini)->lex_list = malloc(sizeof(t_lexer));
	if (!(*mini)->lex_list)
		return (free(*mini), 1);
	(*mini)->lex_list->lex = NULL;
	(*mini)->env = NULL;
	(*mini)->cmd = NULL;
	(*mini)->heredoc = NULL;
	g_heredoc_sig = 0;
	return (0);
}

int	mini_init(t_mini **mini)
{
	(*mini)->env = malloc(sizeof(t_env));
	if (!(*mini)->env)
		return (1);
	(*mini)->env->content = NULL;
	(*mini)->env->next = NULL;
	(*mini)->exec_status = 0;
	return (0);
}

void	error_free(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_node((*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	single_or_multi_command(t_mini *m_mini)
{
	t_parse	*parse;
	int		i;

	i = 0;
	parse = m_mini->parse;
	while (parse)
	{
		if (parse->type == 2)
			i++;
		parse = parse->next;
	}
	return (i);
}
