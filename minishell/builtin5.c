/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:23:23 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:29 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	run_echo(t_parse *data, int *i)
{
	int	x;

	x = *i;
	while (data->text[x])
	{
		write(data->outfile, data->text[x], ft_strlen(data->text[x]));
		if (data->text[x + 1] != NULL)
			write(data->outfile, " ", 1);
		x++;
		*i += 1;
	}
}

static int	all_n_chars(const char *str)
{
	while (*str != '\0')
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	exec_echo(t_parse *data, t_mini *m_mini)
{
	int	i;

	i = 0;
	if (!data->text)
		write(data->outfile, "\n", 1);
	else if (!data->text || data->text[0] == NULL || data->text[0][0] == '\0')
		write(data->outfile, "", 1);
	else
	{
		if (data->text[0][0] == '-' && data->text[0][1] == 'n'
			&& all_n_chars(data->text[0] + 2))
		{
			i = 1;
			if (data->text[1])
				run_echo(data, &i);
		}
		else
		{
			run_echo(data, &i);
			if (!data->text[i])
				write(data->outfile, "\n", 1);
		}
	}
	m_mini->exec_status = 0;
}

void	print_list(void *data, t_mini *m_mini)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = m_mini->parse;
	new = (t_env *)data;
	if (!new->value)
		return ;
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value && new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_env(t_mini *m_mini)
{
	ft_newlstiter(m_mini->env, print_list, m_mini);
	m_mini->exec_status = 0;
}
