/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:23:51 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:34 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

bool	is_numeric(char *s)
{
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (false);
	return (true);
}

void	builtin_exit(t_mini **m_mini)
{
	bool	status;
	int		exit_value;

	exit_value = 0;
	printf("exit\n");
	if (!(*m_mini)->parse->text || (*m_mini)->parse->type != '\0')
		exit(EXIT_SUCCESS);
	status = is_numeric((*m_mini)->parse->text[0]);
	if (status == false)
	{
		printf("bash: exit: %s: numeric argument required\n",
			(*m_mini)->parse->text[0]);
		exit_value = 255;
	}
	else if (status == true && !(*m_mini)->parse->text[1])
		exit_value = ft_atoi((*m_mini)->parse->text[0]);
	else
	{
		printf("bash: exit: too many arguments\n");
		(*m_mini)->exec_status = 1;
		return ;
	}
	(free_loop(1, *m_mini), free_(*m_mini));
	(free((*m_mini)->lex_list), free(*m_mini));
	exit(exit_value);
}
