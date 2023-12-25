/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:24:01 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:42 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	**get_args(t_parse *parse)
{
	char	**exec;
	int		i;
	int		j;

	j = 0;
	if (parse->text)
		while (parse->text[j])
			j++;
	exec = malloc(sizeof(char *) * (j + 2));
	if (!exec)
		return (NULL);
	i = 0;
	exec[0] = ft_strdup(parse->cmd);
	j = 1;
	if (parse->text)
	{
		while (parse->text[i])
		{
			exec[j] = ft_strdup(parse->text[i++]);
			j++;
		}
	}
	exec[j] = NULL;
	return (exec);
}
