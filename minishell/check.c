/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:16:56 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:22 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	is_valid_other(char *a, char *b)
{
	if ((a[0] == '<' && !a[1]) && !b)
		return (0);
	else if ((a[0] == '>' && !a[1]) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && !a[1])) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '>' && a[1] == '>')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] != '<')) && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] != '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] == '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if ((a[0] == '|' && !a[1] && b[0] == '|' && !b[1]))
		return (0);
	return (1);
}

int	cmd_is_valid(t_lexer *lex_list, char *a, char *b)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lex_list->lex;
	while (tmp)
	{
		a = tmp->content;
		if (tmp->next)
			b = tmp->next->content;
		if (i == 0 && !b && ((a[0] == '<') || (a[0] == '>')))
			return (print_error());
		if ((a[0] == '|' && !a[1]) && i == 0)
			return (print_error());
		else if ((a[0] == '>' && !a[1]) && !b)
			return (print_error());
		else if (!is_valid_other(a, b))
			return (print_error());
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	quote_check(char *data, char a, char b)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == a || data[i] == b)
		{
			j++;
			z = data[i++];
			while (data[i] && data[i] != z)
			{
				i++;
			}
			if (!data[i])
				break ;
			j++;
		}
		i++;
	}
	if (j % 2 != 0)
		return (printf("minishell: quote error\n"), 0);
	return (1);
}

int	check(t_mini *mini)
{
	return (cmd_is_valid(mini->lex_list, NULL, NULL));
}
